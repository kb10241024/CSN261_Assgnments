package asn7;
import java.util.Vector;

public class Algorithms
{
    private static boolean equal(Point<Float> p1, Point<Float> p2)
    {
        if(p1.point[0] == p2.point[0] && p1.point[1] == p2.point[1]) return true;
        return false;
    }
    
    public static Point<Float>[] intersection2D(Point<Float> set1[], Point<Float> set2[])
    {
        Vector<Point<Float>> vector = new Vector();
        
        for(Point<Float> point1 : set1)
        {
            for(Point<Float> point2 : set2)
            {
                if(equal(point1,point2))
                {
                    vector.add(point1);
                    break;
                }
            }
        }
        
        Point<?>[] intersect = new Point<?> [vector.size()];
        for(int i=0; i<vector.size(); i++)
            intersect[i] = vector.get(i);
        
            return (Point<Float>[]) intersect;
    }
}