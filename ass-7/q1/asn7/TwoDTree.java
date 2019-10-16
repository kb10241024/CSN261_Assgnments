package asn7;

import java.util.Vector;

public class TwoDTree<T extends Comparable<Float>> extends KDTree<Float> {
    public TwoDTree(Point<Float> points[]) {
        super(points);
    }

    private void rangeSearch(TwoDOrthogonalPolygon<Float> poly, Node node, Vector<Integer> set) {
        if (node.left_child == null && node.right_child == null) {
            if (poly.doesLie(points[node.value]))
                set.add(node.value);

            return;
        }
        switch (poly.relativeLocation(points[node.value], node.alignment)) {
        case -2:
        case -1:
            rangeSearch(poly, node.left_child, set);
            break;

        case 0:
        case 1:
            rangeSearch(poly, node.left_child, set);
            rangeSearch(poly, node.right_child, set);
            break;

        default: // case w
            rangeSearch(poly, node.right_child, set);
        }
    }

    public Point<Float>[] rangeSearch(TwoDOrthogonalPolygon<Float> poly) {
        Vector<Integer> set = new Vector<Integer>();
        rangeSearch(poly, root, set);

        Point<?> _points[] = new Point<?>[set.size()];

        for (int j = 0; j < set.size(); j++)
            _points[j] = points[set.get(j)];

        return (Point<Float>[]) _points;
    }
}