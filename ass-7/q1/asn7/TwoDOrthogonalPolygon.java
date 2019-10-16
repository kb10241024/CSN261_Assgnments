package asn7;

public class TwoDOrthogonalPolygon<Float>
{
    public Point<Float> points[]; //Verticees
    int V; //The number of vertices
    float min[], max[]; // Bounds
    
    public TwoDOrthogonalPolygon(Point<Float> points[])
    {
        max = new float[2];
        min = new float[2];
       
        this.points = points;
        V = points.length;
        max[0] = (float)points[0].point[0];
        min[0] = (float)points[0].point[0];
        max[1] = (float)points[0].point[1];
        min[1] = (float)points[0].point[1];
        
        //O(V)
        for(Point<Float> p : points)
        {
            if((float)p.point[0] < min[0])
                min[0] = (float)p.point[0];
            if((float)p.point[0] > max[0])
                max[0] = (float)p.point[0];
            if((float)p.point[1] < min[1])
                min[1] = (float)p.point[1];
            if((float)p.point[1] > max[1])
                max[1] = (float)p.point[1];
        }
    }
    
    // true if inside [O(V)]
    boolean doesLie(Point<Float> point)
    {
        int count = 0;
        
        for(int i=0; i < V; i++)
        {
            Point<Float> a = points[i];
            Point<Float> b = points[(i+1)%V];
            //Vertical Line
            if((float)a.point[0] == (float)b.point[0])
            {
                float d = ((float)point.point[1]-(float)a.point[1])*((float)point.point[1]-(float)b.point[1]);
                float e = (float)a.point[0] - (float)point.point[0];
                if(point.point[0] == a.point[0]){
                    if(d<=0)
                        return true;}
                   else if(d<0 && e>0)
                        count++;
            }
            else //Horizontal
            {
                if(point.point[1] == a.point[1])
                {
                    if(((float)point.point[0]-(float)a.point[0])*((float)point.point[0]-(float)b.point[0])<=0)
                        return true;
                }
            }
        }
        
        return (count%2==0) ? false : true;
    }
    
    int relativeLocation(Point<Float> line, int align)
    {
        float x = (float)line.point[align];
        if(max[align] < x) return -2;
        if(max[align] == x) return -1;
        if(min[align] < x) return 0;
        if(min[align] == x) return 1;
        
        return 2;
    }
}