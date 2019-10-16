package asn7;

        /**
         * @file KDTree.java
         * @author Ritik Jain
         * @date 10/10/2019
        
        package asn7;
        
        /**
         * @author Ritik Jain
         * @date 10/10/2019
         * @param <T>  The type of Euclidean Space
         * @brief Implements K-Dimensional Tree
         */
        public class KDTree <T extends Comparable<T>> {
            
            protected int K = 0; //The dimensionality of the tree
            protected int[] aligned_points; //Dynamic Aligned list of points
            protected Point<T> [] points; //The points
            protected Node<T> root; //The K-Dimensional Tree
            
            protected class Node <T>
            {
                public Node parent = null;
                public Node left_child = null;
                public Node right_child = null;
                public int value = -1;
                public int alignment = 0; //The alignment of this plane (normal)
            }
            
            /**
             * @author Ritik Jain
             * @date 10/10/2019
             * @brief Initializes the tree
             * @param points  An array of all K-Dimensional Points
             */
            public KDTree(Point<T> points[])
            {
                K = points[0].K;
                aligned_points = new int[points.length];
                
                for(int i=0; i<points.length; i++)
                    aligned_points[i] = i;
                
                this.points = points;
                construct(0, points.length-1, null, false);
            }
            
            /**
             * @author Ritik Jain
             * @date 11/10/2019
             * @brief Swaps two points in aligned points array
             * @param i Index 1
             * @param j Index 2
             */
            void swap(int i, int j)
            {
                int tmp = aligned_points[i];
                aligned_points[i] = aligned_points[j];
                aligned_points[j] = tmp;
            }
            
            /**
             * @author Ritik Jain
             * @date 11/10/2019
             * @brief Partitioning Function for Quick Sort [O(high-low)]
             * @param low  The lower bound
             * @param high  The higher bound
             * @param k  The dimension to be sorted
             * @return The partitioning index
             */
            protected int partition(int k, int low, int high)
            {
                T pivot = points[aligned_points[high]].point[k]; //Taking the last element as the pivot
                int i = low-1;
                int tmp;
                for(int j=low; j < high; j++)
                {
                    if(points[aligned_points[j]].point[k].compareTo(pivot) < 0)
                    {
                        i++;
                        swap(i,j);
                    }
                }
                
                i++;
                swap(i,high);
                
                return i;
            }
            
            /**
             * @author Ritik Jain
             * @date 11/10/2019
             * @brief Implements Quick-sort Algorithm For K-DTree [W((high-low)log(high-low)) to O((high-low)^2)]
             * @param low  The lower bound
             * @param high  The upper bound
             * @param k  The dimension to be sorted
             */
            protected void quicksort(int k, int low, int high)
            {
                if(low < high)
                {
                    //partitioning index
                    int pi = partition(k, low, high);
                 
                    quicksort(k, low,pi-1);
                    quicksort(k, pi+1, high);
                }
            }
            
            /**
             * @author Ritik Jain
             * @date 11/10/2019
             * @brief Finds the median in the given dimension in the aligned array in the given range [a,b] : [W((a-b)log(a-b)) to O((a-b)^2)]
             * @param a  The lower bound
             * @param b  The upper bound
             * @param k  The dimension
             * @return  The index of the median in kth dimension in range [a,b]
             */
            protected int median(int k, int a, int b)
            {
                quicksort(k,a,b);
                int split = (int) Math.ceil((a+b+1)/2.0)-1;
                return aligned_points[split];
            }
            
            /**
             * @author Ritik Jain
             * @date 10/10/2019
             * @brief Constructs the K-Dimensional Tree recursively in the bounds [a,b] : [O((a-b)^2)]
             * @param a  The lower bound of [a,b]
             * @param b  The upper bound of [a,b]
             * @param isLeft Whether the child is the left-child of the parent or not
             * @param parent  The parent of the parent node
             */
            public void construct(int a, int b, Node parent, boolean isLeft)
            {
                int split = (int)Math.ceil((a+b+1)/2.0);
                int align;
                
                Node<T> node = new Node<T>();
                
                if(parent!=null)
                {
                    align = (parent.alignment+1) % K;
                    node.parent = parent;
                    
                    if(isLeft)
                        parent.left_child = node;
                    else
                        parent.right_child = node;
                    
                    node.alignment = align;
                }
                else
                {
                    node.alignment = 0;
                    align = 0;
                    root = node;
                }
                
                if(a!=b)
                {
                    node.value = median(align,a,b);
                    construct(a, split-1, node, true);
                    construct(split, b, node, false);
                }
                else
                    node.value = aligned_points[a];
            }
            
            /* Debug */
            protected void print(Node<T> node,String path)
            {
                
                
                if(node.right_child == null && node.left_child == null)
                {
                   path += (node.value+1);
                   System.out.println(path);
                }
                else
                {
                    path += (node.value+1) + " --> ";
                    if(node.left_child != null)
                    print(node.left_child, path);
                    if(node.right_child != null)
                    print(node.right_child, path);
                }
            }
    
    public void print()
    {
        print(root,"");
    }
}
