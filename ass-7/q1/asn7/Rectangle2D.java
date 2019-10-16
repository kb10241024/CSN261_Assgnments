package asn7;

public class Rectangle2D
{
    public static TwoDOrthogonalPolygon getRectangle2D(float bl_x, float bl_y, float tr_x, float tr_y)
    {
        Point<?> points[] = new Point<?>[4];
        points[0] = new Point<Float>(new Float[]{bl_x,bl_y});
        points[1] = new Point<Float>(new Float[]{tr_x,bl_y});
        points[2] = new Point<Float>(new Float[]{tr_x,tr_y});
        points[3] = new Point<Float>(new Float[]{bl_x,tr_y});
        
        return new TwoDOrthogonalPolygon(points);
    }
}
