/**
 * @file Point.java
 * @date 11/10/2019
 * @author Ritik Jain
 * @brief Implements a K-Dimensional Point
*/
 
package asn7;

public class Point<T> {
    
    public T[] point;
    public int K;
    
    /**
     * @author Ritik Jain
     * @date 11/10/2019
     * @brief Initializes the tree
     * @param point  The point
     */
    public Point(T[] point)
    {
        this.point = point;
        K = point.length;
    }
}
