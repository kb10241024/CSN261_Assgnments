#include "mainwindow.h"
#include "ui_mainwindow.h"

//start

struct Point
{
    char letter;
    double x, y;
    Point & operator = (Point const & b) { letter = b.letter;  x = b.x; y = b.y; return *this; }
    Point(const Point & b) : letter(b.letter), x(b.x), y(b.y) {}
    Point(char _letter, double _x, double _y) : letter(_letter), x(_x), y(_y) {}
    bool operator <(const Point & b) const
    {
        if (y < b.y - 1.0e-9) return true;
        else if (y > b.y + 1.0e-9) return false;
        else if (x < b.x - 1.0e-9) return true;
        else return false;
    }
    bool operator ==(const Point & b) const
    {
        return fabs(y - b.y) < 1.0e-9 && fabs(x - b.x) < 1.0e-9;
    }
    bool operator !=(const Point & b) const
    {
        return fabs(y - b.y) > 1.0e-9 || fabs(x - b.x) > 1.0e-9;
    }
};

struct Segment
{
    Point beg, end;
    Segment & operator = (Segment const & b) { beg = b.beg; end = b.end; return *this; }
    Segment(const Segment & b) : beg(b.beg), end(b.end) {}
    Segment(const Point & _beg, const Point & _end) : beg(_beg), end(_end) {}
};

#define SEG_START 0
#define SEG_END 1

class event_less
{
public:
    bool operator()(const std::pair<double, int> & a, const std::pair<double, int> & b) const
    {
        if (a.first < b.first - 1.0e-9)
            return true;
        else if (a.first > b.first + 1.0e-9)
            return false;
        else if (a.second < b.second)
            return true;
        return false;
    }
};

std::pair<bool, Point> intersect(const Segment & a, const Segment & b, bool print)
{
    Point ret('a', 0, 0);
    double div = (a.beg.x - a.end.x)*(b.beg.y - b.end.y) - (a.beg.y - a.end.y)*(b.beg.x - b.end.x), t;
    if (fabs(div) < 1.0e-13)
    {
        if (print) std::cout << "divisor is zero" << std::endl;
        return std::make_pair(false, ret);
    }
    ret.x = ((a.beg.x*a.end.y - a.beg.y*a.end.x)*(b.beg.x - b.end.x) - (a.beg.x - a.end.x)*(b.beg.x*b.end.y - b.beg.y*b.end.x)) / div;
    ret.y = ((a.beg.x*a.end.y - a.beg.y*a.end.x)*(b.beg.y - b.end.y) - (a.beg.y - a.end.y)*(b.beg.x*b.end.y - b.beg.y*b.end.x)) / div;
    if (print) std::cout << "found (" << ret.x << "," << ret.y << ")" << std::endl;
    //probably some of these tests are redundant
    if (fabs(a.end.x - a.beg.x) > 1.0e-9)
    {
        t = (ret.x - a.beg.x) / (a.end.x - a.beg.x);
        if (t < 1.0e-9 || t > 1.0 - 1.0e-9)  { if (print) std::cout << "out of bound: " << t << std::endl; return std::make_pair(false, ret); }
    }
    if (fabs(a.end.y - a.beg.y) > 1.0e-9)
    {
        t = (ret.y - a.beg.y) / (a.end.y - a.beg.y);
        if (t < 1.0e-9 || t > 1.0 - 1.0e-9)  { if (print) std::cout << "out of bound: " << t << std::endl; return std::make_pair(false, ret); }
    }
    if (fabs(b.end.x - b.beg.x) > 1.0e-9)
    {
        t = (ret.x - b.beg.x) / (b.end.x - b.beg.x);
        if (t < 1.0e-9 || t > 1.0 - 1.0e-9)  { if (print) std::cout << "out of bound: " << t << std::endl; return std::make_pair(false, ret); }
    }
    if (fabs(b.end.y - b.beg.y) > 1.0e-9)
    {
        t = (ret.y - b.beg.y) / (b.end.y - b.beg.y);
        if (t < 1.0e-9 || t > 1.0 - 1.0e-9)  { if (print) std::cout << "out of bound: " << t << std::endl; return std::make_pair(false, ret); }
    }
    if (print) std::cout << "intersection accepted" << std::endl;
    return std::make_pair(true, ret);
}

void intersect(int a, int b, const Point & I, std::vector<Segment> & segments, std::multimap<Point, int> & sweep, std::multimap<std::pair<double,int>, int,event_less> & events, bool print)
{
    //remove event of ending of old segment
    {
        int rem_end_events[2];
        rem_end_events[0] = a;
        rem_end_events[1] = b;
        for (int k = 0; k < 2; ++k)
        {
            std::pair< std::multimap<std::pair<double,int>, int,event_less>::iterator, std::multimap<std::pair<double,int>,int,event_less>::iterator > del = events.equal_range(std::make_pair(segments[rem_end_events[k]].end.x,SEG_END)); //get all events at position of the end
            bool flag = false;
            for (std::multimap<std::pair<double,int>, int,event_less>::iterator it = del.first; it != del.second; ++it) //search over all events
            {
                if (it->first.second == SEG_END && it->second == rem_end_events[k]) //event is end of segment and segment matches current
                {
                    events.erase(it); //remove that segment
                    flag = true;
                    break; //do not expect any more
                }
            }
            if (!flag) std::cout << "Cannot find proper ending event for segment" << std::endl;
        }
    }
    //add new segment with intersection point up to end
    segments.push_back(Segment(I, segments[a].end));
    //add event of starting of new segment
    events.insert(std::make_pair(std::make_pair(I.x,SEG_START), (int)segments.size() - 1));
    //add event of ending of new segment
    events.insert(std::make_pair(std::make_pair(segments.back().end.x,SEG_END),(int)segments.size() - 1));
    //change ending point for current segment
    segments[a].end = I;
    //add event of ending of old segment
    events.insert(std::make_pair(std::make_pair(I.x,SEG_END), a));
    //add new segment with intersection point up to end
    segments.push_back(Segment(I, segments[b].end));
    //add event of starting of new segment
    events.insert(std::make_pair(std::make_pair(I.x,SEG_START), (int)segments.size() - 1));
    //add event of ending of new segment
    events.insert(std::make_pair(std::make_pair(segments.back().end.x,SEG_END), (int)segments.size() - 1));
    //change ending point for current segment
    segments[b].end = I;
    //add event of ending of old segment
    events.insert(std::make_pair(std::make_pair(I.x,SEG_END), b));
    if (print)
    {
        std::cout << "Number of events: " << events.size() << std::endl;
        for (std::multimap<std::pair<double, int>, int,event_less>::iterator it = events.begin(); it != events.end(); ++it)
            std::cout << "x: " << it->first.first << " type " << (it->first.second == SEG_START ? "start" : "end") << " segment " << it->second << std::endl;
    }
}

//find all intersection points
void intersect(std::vector<Segment> & segments, std::vector<Point> & intersections, bool print)
{
    std::multimap<std::pair<double,int>,int,event_less> events;
    std::multimap<Point,int> sweep;

    if( print )
    {
        std::cout << "Input segments[" << segments.size() << "]: " << std::endl;
        for (std::vector<Segment>::iterator it = segments.begin(); it != segments.end(); ++it)
            std::cout << "[ " << it->beg.letter << "(" << it->beg.x << "," << it->beg.y << "), " << it->end.letter << "(" << it->end.x << "," << it->end.y << ") ] " << std::endl;
        std::cout << "Create events based on segments." << std::endl;
    }

    for (int k = 0; k < (int)segments.size(); ++k)
    {
        if (segments[k].beg.x > segments[k].end.x)
            std::swap(segments[k].beg, segments[k].end);
        events.insert(std::make_pair(std::make_pair(segments[k].beg.x,SEG_START),k));
        events.insert(std::make_pair(std::make_pair(segments[k].end.x,SEG_END), k));
    }


    if (print)
    {
        std::cout << "Number of events: " << events.size() << std::endl;
        for (std::multimap<std::pair<double, int>, int,event_less>::iterator it = events.begin(); it != events.end(); ++it)
            std::cout << "x: " << it->first.first << " type " << (it->first.second == SEG_START ? "start" : "end") << " segment " << it->second << std::endl;

        std::cout << " Start parsing events" << std::endl;
    }

    while (!events.empty())
    {
        std::multimap<std::pair<double,int>,int,event_less>::iterator first = events.begin();
        int t = first->first.second;
        int s = first->second;
        events.erase(first);
        if (t == SEG_START)
        {
            if( print ) std::cout << "Segment " << s << " start" << std::endl;
            //check if there is a line with same position
            std::multimap<Point, int>::iterator ins = sweep.insert(std::make_pair(segments[s].beg, s));
            if (print)
            {
                std::cout << "Inserted into sweep" << std::endl;
                for (std::multimap<Point, int>::iterator it = sweep.begin(); it != sweep.end(); ++it)
                    std::cout << it->first.letter << "(" << it->first.x << "," << it->first.y << ")" << " segment " << it->second << std::endl;
            }
            //check line (or lines above current)
            for (int dir = 0; dir <= 1; ++dir) // look up or down
            {
                if( print ) std::cout << "Looking " << (dir ? "up" : "down") << std::endl;
                std::multimap<Point, int>::iterator iter = ins;
                while ((dir ? ++iter : iter--) != (dir ? sweep.end() : sweep.begin())) //y is greater for next
                {
                    if (print) std::cout << "test " << s << " with " << iter->second << std::endl;
                    if (segments[s].beg != segments[iter->second].beg) //ignore same starting position
                    {
                        if (print) std::cout << "checking intersection" << std::endl;
                        std::pair<bool, Point> I = intersect(segments[s], segments[iter->second],print);
                        if (I.first)
                        {
                            I.second.letter += (char)intersections.size();
                            if( print ) std::cout << "Intersection of " << s << " and " << iter->second << " at " << I.second.letter << "(" << I.second.x << "," << I.second.y << ")" << std::endl;
                            intersections.push_back(I.second);
                            intersect(s, iter->second, I.second, segments, sweep, events,print);
                        }
                    }
                    else if (print) std::cout << "skipping segments with same starting point" << std::endl;
                    if ((2*dir-1)*(iter->first.y - ins->first.y) > 0) //visited line is above (below) current
                        break; //stop search
                }
            }
        }
        else if (t == SEG_END)
        {
            if( print ) std::cout << "Segment " << s << " end" << std::endl;
            //remove segment from sweep
            std::pair< std::multimap<Point, int>::iterator, std::multimap<Point, int>::iterator > range = sweep.equal_range(segments[s].beg);
            if( print ) std::cout << "Range distance " << std::distance(range.first,range.second) << " sweep size " << sweep.size() << std::endl;
            std::multimap<Point, int>::iterator above = range.second, below = range.first;
            bool flag = false, test = true;
            if( below-- == sweep.begin() ) test = false;
            if( above == sweep.end() ) test = false;
            if( test && print ) std::cout << "Test will be performed" << std::endl;
            for (std::multimap<Point, int>::iterator it = range.first; it != range.second; ++it) //search over all events
            {
                if( it->second == s) //found necessery segment
                {
                    if (print)
                    {
                        std::cout << "Erase segment " << s << " from sweep: " << std::endl;
                        for (std::multimap<Point, int>::iterator it = sweep.begin(); it != sweep.end(); ++it)
                            std::cout << it->first.letter << "(" << it->first.x << "," << it->first.y << ")" << " segment " << it->second << std::endl;
                    }
                    sweep.erase(it);
                    flag = true;
                    break; //do not expect any more
                }
            }
            if (!flag) std::cout << __FILE__ << ":" << __LINE__ <<  " Error: cannot find segment " << s << " in sweep" << std::endl;
            if (test)
            {
                if (print) std::cout << "test " << below->second << " with " << above->second << std::endl;
                if (segments[above->second].beg != segments[below->second].beg)
                {
                    if (print) std::cout << "checking intersection" << std::endl;
                    std::pair<bool, Point> I = intersect(segments[below->second], segments[above->second],print);
                    if (I.first)
                    {
                        I.second.letter += (char)intersections.size();
                        if( print ) std::cout << "Intersection of " << below->second << " and " << above->second << " at " << I.second.letter << "(" << I.second.x << "," << I.second.y << ")" << std::endl;
                        intersections.push_back(I.second);
                        intersect(below->second, above->second, I.second, segments, sweep, events,print);
                    }
                }
                else if (print) std::cout << "skipping segments with same starting point" << std::endl;
            }
        }
    }

}

//end

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::vector<Segment> segments;
QString seglist="";

double xmax=5;
double ymax=5;

std::vector<Point> intersections;

void MainWindow::plotData(double x1,double y1,double x2,double y2)
{
    QCPItemLine *newline = new QCPItemLine(ui->customPlot);
    newline->start->setCoords(x1,y1);
    newline->end->setCoords(x2,y2);
    ui->customPlot->replot();

}
void MainWindow::addSegment(double x1,double y1,double x2,double y2)
{
    segments.push_back(Segment(Point('A',x1,y1), Point('C',x2,y2)));
    seglist=seglist+QString::number(segments.size())+":- ("+QString::number(x1)+","+QString::number(y1)+") to ("+QString::number(x2)+","+QString::number(y2)+")\n";
    ui->textBrowser_1->setText(seglist);
}
void MainWindow::printIntersection(){
    QString interlist="";
    ui->textBrowser_2->clear();
    int i=1;
    for (std::vector<Point>::iterator it = intersections.begin(); it != intersections.end(); ++it){
        interlist=interlist+QString::number(i)+":- ("+QString::number(it->x)+","+QString::number(it->y)+")\n";
        i++;
    }
    ui->textBrowser_2->setText(interlist);
}
void MainWindow::linearFit(){
    int n=intersections.size();
        double a,b;
        double xsum=0,x2sum=0,ysum=0,xysum=0;                //variables for sums/sigma of xi,yi,xi^2,xiyi etc
        for (std::vector<Point>::iterator it = intersections.begin(); it != intersections.end(); ++it)
        {
            xsum=xsum+it->x;                        //calculate sigma(xi)
            ysum=ysum+it->y;                        //calculate sigma(yi)
            x2sum=x2sum+pow(it->x,2);                //calculate sigma(x^2i)
            xysum=xysum+it->x*it->y;                    //calculate sigma(xi*yi)
        }
        a=(n*xysum-xsum*ysum)/(n*x2sum-xsum*xsum);            //calculate slope
        b=(x2sum*ysum-xsum*xysum)/(x2sum*n-xsum*xsum);            //calculate intercept
        double x1=0;
        double y1=b;
        double x2=xmax;
        double y2=a*x2+b;
        QCPItemLine *newline = new QCPItemLine(ui->customPlot);
        newline->start->setCoords(x1,y1);
        newline->end->setCoords(x2,y2);
        newline->setPen(QPen(Qt::red));
        ui->customPlot->replot();
}

void MainWindow::on_pushButton_clicked()
{
    double x1=ui->lineEdit_x1->text().toDouble();
    double y1=ui->lineEdit_y1->text().toDouble();
    double x2=ui->lineEdit_x2->text().toDouble();
    double y2=ui->lineEdit_y2->text().toDouble();
    MainWindow::plotData(x1,y1,x2,y2);
    addSegment(x1,y1,x2,y2);
    std::vector<Segment> temp;
    //std::vector<Point> intersectionsHistory;
    //intersectionsHistory=intersections;
    intersections.clear();
    temp=segments;
    if(segments.size()>=2){
        intersect(segments, intersections,false);
//        std::vector<Point>::iterator itt =intersectionsHistory.begin();
//        for(std::vector<Point>::iterator it =intersectionsHistory.begin(); it != intersectionsHistory.end(); ++it)
//        {
//            if(std::binary_search(intersections.begin(),intersections.end(),*it)){ }
//            else{
//                intersections.push_back(*it);
//            }
//        }

        segments=temp;
        printIntersection();
    }
    if(xmax<std::max(x1,x2)) xmax=std::max(x1,x2);
    if(ymax<std::max(y1,y2)) ymax=std::max(y1,y2);
    ui->customPlot->xAxis->setRange(0,xmax);
    ui->customPlot->yAxis->setRange(0,ymax);
    ui->lineEdit_x1->clear();
    ui->lineEdit_x2->clear();
    ui->lineEdit_y1->clear();
    ui->lineEdit_y2->clear();
    ui->customPlot->replot();
}


void MainWindow::on_pushButton_2_clicked()
{
    //linearFit();
    int n=intersections.size();
    double a,b;
    double xsum=0,x2sum=0,ysum=0,xysum=0;                //variables for sums/sigma of xi,yi,xi^2,xiyi etc
    for (std::vector<Point>::iterator it = intersections.begin(); it != intersections.end(); ++it)
    {
        xsum=xsum+it->x;                        //calculate sigma(xi)
        ysum=ysum+it->y;                        //calculate sigma(yi)
        x2sum=x2sum+pow(it->x,2);                //calculate sigma(x^2i)
        xysum=xysum+it->x*it->y;                    //calculate sigma(xi*yi)
    }
    a=(n*xysum-xsum*ysum)/(n*x2sum-xsum*xsum);            //calculate slope
    b=(x2sum*ysum-xsum*xysum)/(x2sum*n-xsum*xsum);            //calculate intercept
    double x1=0;
    double y1=b;
    double x2=100;
    double y2=a*x2+b;
    QCPItemLine *newline = new QCPItemLine(ui->customPlot);
    newline->start->setCoords(x1,y1);
    newline->end->setCoords(x2,y2);
    newline->setPen(QPen(Qt::red));

    ui->textBrowser_3->clear();
    QString line = "y="+QString::number(a)+"x+"+QString::number(b);
    ui->textBrowser_3->setText(line);

    ui->customPlot->replot();
}
