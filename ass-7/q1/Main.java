/* Test */
import asn7.*;
import java.util.Scanner;
import java.util.Vector;

public class Main
{
    public static TwoDOrthogonalPolygon getPoly()
    {
        Scanner s = new Scanner(System.in);
        System.out.println("Enter the number of points in the polygon :");
        int V = s.nextInt();
        System.out.println("Enter the points :");
        System.out.println("Format XY XY XY ... :");
        Point<?> polyver[] = new Point<?>[V];
        for(int i=0; i < V; i++)
            polyver[i] = new Point<Float>(new Float[]{s.nextFloat(), s.nextFloat()});
        
        TwoDOrthogonalPolygon<Float> poly;
        
        
        if(V==2) poly = Rectangle2D.getRectangle2D((float)polyver[0].point[0], (float)polyver[0].point[1], (float)polyver[1].point[0], (float)polyver[1].point[1]);
        else
           poly = new TwoDOrthogonalPolygon(polyver);
        System.out.println();
        return poly;
    }
    
    public static Point<Float>[] getPoints()
    {
        Scanner s = new Scanner(System.in);
        
        System.out.println("Enter the number of 2-D points in the plane :");
        int N = s.nextInt();
        System.out.println("Enter the points :");
        System.out.println("Format XY XY XY ... :");
        Point<?> points[] = new Point<?>[N];
        for(int i=0; i < N; i++)
            points[i] = new Point<Float>(new Float[]{s.nextFloat(), s.nextFloat()});
        System.out.println();
        return (Point<Float>[]) points;
    }
    
    public static void main( String[] args)
    {
        Point<Float> [] points = getPoints();
        TwoDOrthogonalPolygon poly1 = getPoly();
        TwoDOrthogonalPolygon poly2 = getPoly();
        
        
        TwoDTree<Float> tree = new TwoDTree(points);
        Point<Float> set1[] = tree.rangeSearch(poly1);
        Point<Float> set2[] = tree.rangeSearch(poly2);
        Point<Float> set[] = Algorithms.intersection2D(set1, set2);
        
        System.out.println("Points lying within Polygon/ Rectangle 1 : [Total = "+set1.length+"]");
        for( Point<Float> x : set1)
            System.out.println("("+x.point[0]+","+x.point[1]+")");
        System.out.println();
        System.out.println("Points lying within Polygon/ Rectangle 2 : [Total = "+set2.length+"]");
        for( Point<Float> x : set2)
            System.out.println("("+x.point[0]+","+x.point[1]+")");
        System.out.println();
        System.out.println("Points lying within the common region (within polygon 1 and polygon 2) : [Total = "+set.length+"]");
        for(Point<Float> x : set)
            System.out.println("("+x.point[0]+","+x.point[1]+")");
        System.out.println();
    }
}