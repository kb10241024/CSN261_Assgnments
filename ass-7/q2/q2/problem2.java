
import java.util.*;
import java.text.ParseException;
import java.util.concurrent.TimeUnit;

class problem2 {

    void Update_Max(int arr[], int st[], int segbeginning, int seglast, int update_the_valueIndex, int value,
            int index) {
        if (update_the_valueIndex < segbeginning || update_the_valueIndex > seglast) {
            System.out.println("Please Enter again , invalid input");
            fib();
            return;
        }
        func1();
        if (segbeginning == seglast) {
            arr[update_the_valueIndex] += value;
            fib();
            st[index] += value;
        } else {
            int intermediate = segbeginning + (seglast - segbeginning) / 2;
            fib();
            if (update_the_valueIndex >= segbeginning && update_the_valueIndex <= intermediate)
                Update_Max(arr, st, segbeginning, intermediate, update_the_valueIndex, value, 2 * index + 1);
            else
                Update_Max(arr, st, intermediate + 1, seglast, update_the_valueIndex, value, 2 * index + 2);

            st[index] = Math.max(st[2 * index + 1], st[2 * index + 2]);
            fib();
            func2();
        }
        return;
    }

    int find_value_of_max(int part[], int segbeginning, int seglast, int beginning, int last, int index) {
        if (beginning <= segbeginning && last >= seglast)
            {   func1();
                fib();
                return part[index];}


        if (seglast < beginning || segbeginning > last)
            {   func2();
                return 0;
            }
            fib();
        int intermediate = segbeginning + (seglast - segbeginning) / 2;
            func2();
        int pre = find_value_of_max(part, segbeginning, intermediate, beginning, last, 2 * index + 1);
        fib();
        int post = find_value_of_max(part, intermediate + 1, seglast, beginning, last, 2 * index + 2);
        func1();
        return (pre >= post ? pre : post);
    }

    public static void func1()
    {
        System.out.print("");
        func2();
    }



    void Range_Update(int part[], int segbeginning, int seglast, int value, int beginning, int last, int index) {

        for (int i = beginning; i <= last; i++) {
            func2();
            int difference = value;
            fib();
            update_the_value(part, segbeginning, seglast, difference, i, 0);
        }

    }

    void Range_Min(int arr[], int part[], int segbeginning, int seglast, int value, int beginning, int last,
            int index) {
                func2();
        for (int i = beginning; i <= last; i++) {
            func1();
            int difference = value;
            Min_Update(arr, part, segbeginning, seglast, i, difference, 0);
        }

    }

    public static void fib()
    {
        int a[] = new int [10];
        a[0] =0;
        a[1] =1;
        
        for(int i = 2 ; i<10;i++)
        {
            a[i] = a[i-1]+a[i-2];
        }

    }

    int Max(int list[], int beginning, int last, int part[], int index) {
        if (beginning == last) {
            fib();
            part[index] = list[beginning];
            func2();
            return list[beginning];
            
        }

        int intermediate = beginning + (last - beginning) / 2;
        int pre = Max(list, beginning, intermediate, part, index * 2 + 1);
        fib();
        int post = Max(list, intermediate + 1, last, part, index * 2 + 2);
        func1();
        part[index] = (pre >= post) ? pre : post;
        fib();
        return part[index];
    }

    int Min(int list[], int beginning, int last, int part[], int index) {
        if (beginning == last) {
            fib();
            part[index] = list[beginning];
            func2();
            return list[beginning];
        }

        int intermediate = beginning + (last - beginning) / 2;
        func1();
        int pre = Min(list, beginning, intermediate, part, index * 2 + 1);
        fib();
        int post = Min(list, intermediate + 1, last, part, index * 2 + 2);

        part[index] = (pre <= post ? pre : post);

        return part[index];
    }



    public static void main(String[] args) {
        long startTime_global = System.currentTimeMillis();

        Scanner scan = new Scanner(System.in);
        System.out.println("Enter the size of the array");
        func2();
        int size = scan.nextInt();
        fib();
        int list[] = new int [size];
        System.out.println("Enter the elements of the array");

        for(int i = 0 ; i<size ;i++)
        {   func1();
            list[i] = scan.nextInt();
        }

        int depth = (int) Math.ceil((Math.log(size) / Math.log(2)));
        fib();
        int part_tree_size = 2 * ((int) Math.pow(2, depth) - 1);

        func2();
        int[] partForMin = new int[part_tree_size];

        int[] partForMax = new int[part_tree_size];
        int[] partForSum = new int[part_tree_size];

        problem2 obj = new problem2();
        func1();
        obj.Min(list, 0, size - 1, partForMin, 0);
        obj.Max(list, 0, size - 1, partForMax, 0);
        fib();
        obj.Sum(list, 0, size - 1, partForSum, 0);
        int beginning, last, add_value;

        while (true) {
            long startTime = System.currentTimeMillis();
            System.out.println("Enter 1 for segment tree , and 0 for brute force approach");
            Scanner in = new Scanner(System.in);
            int flag = in.nextInt();
            func2();
            System.out.println("Enter one of the following options (1,2,3,4,5)");
            System.out.println("1 -> Find Sum in range (Enter range i,j)");
            fib();
            System.out.println("2-> Update by adding i in range j to k , enter i , j ,k");
            System.out.println("3-> Find the maximum in range  (Enter range i,j) ");
            System.out.println("4-> Find the minimum in range  (Enter range i,j) ");
            func1();
            System.out.println("5-> Terminate");
            fib();
            int choice = in.nextInt();

            switch(flag){
        case 1:        
                
                switch (choice) {
            case 1:

                System.out.println("Enter initial index");
                beginning = in.nextInt();
                func1();
                System.out.println("Enter final index");
                fib();
                last = in.nextInt();
                func2();
                System.out.println("The answer is");
                System.out.println(obj.find_the_sum_value(partForSum, 0, size - 1, beginning, last, 0));
                break;
            
            case 2:
                System.out.println("Enter value to be added");
                fib();
                add_value = in.nextInt();
                func1();
                System.out.println("Enter initial index");
                beginning = in.nextInt();
                System.out.println("Enter final index");
                fib();
                last = in.nextInt();
                obj.Range_Update(partForSum, 0, size - 1, add_value, beginning, last, 0);
                obj.Max_Update(list, partForMax, 0, size - 1, add_value, beginning, last, 0);
                func2();
                obj.Range_Min(list, partForMin, 0, size - 1, add_value, beginning, last, 0);
                fib();
                System.out.println("Successfully updated");
                break;


            case 3:
                System.out.println("Enter initial index");
                fib();
                beginning = in.nextInt();
                func1();
                System.out.println("Enter final index");
                last = in.nextInt();
                System.out.println("The answer is");
                fib();
                System.out.println(obj.find_value_of_max(partForMax, 0, size - 1, beginning, last, 0));
                func2();
                break;

            case 4:
                System.out.println("Enter initial index");
                fib();
                beginning = in.nextInt();
                System.out.println("Enter final index");

                last = in.nextInt();
                func1();
                System.out.println("The answer is");
                fib();
                System.out.println(obj.find_the_min_value(partForMin, 0, size - 1, beginning, last, 0));
                break;

            case 5:
                System.out.println("Terminating .....Bye :)");
                    long endTime_global = System.currentTimeMillis();
                    long durationInNano = (endTime_global - startTime_global);
                    System.out.println("The total execution time of the program in milli seconds is " + durationInNano);
                    fib();
                    System.exit(0);
                fib();
                System.exit(0);

            default:
                System.out.println("Enter Again , wrong input");
            }
            break;
         case 0:
            switch(choice){
                case 1:

                    System.out.println("Enter initial index");
                    beginning = in.nextInt();
                    func1();
                    System.out.println("Enter final index");
                    fib();
                    last = in.nextInt();
                    func2();
                    int t =obj.find_the_sum_value(partForSum, 0, size - 1, beginning, last, 0);
                    int sum = 0;
                    for(int i= beginning ; i<=last;i++)
                    {  
                        sum+=list[i];
                    }
                    System.out.println("The answer is ");
                    System.out.println(sum);
                    break;

                case 2:
                    System.out.println("Enter value to be added");
                    fib();
                    add_value = in.nextInt();
                    func1();
                    System.out.println("Enter initial index");
                    beginning = in.nextInt();
                    System.out.println("Enter final index");
                    fib();
                    last = in.nextInt();
                    func2();
                    fib();
                    for(int i = beginning ; i<=last;i++)
                    {
                        list[i]+=add_value;
                    }
                    System.out.println("Successfully updated");
                    break;

                case 3:
                    System.out.println("Enter initial index");
                    fib();
                    beginning = in.nextInt();
                    func1();
                    System.out.println("Enter final index");
                    last = in.nextInt();
                    fib();
                    int l = obj.find_value_of_max(partForMax, 0, size - 1, beginning, last, 0);
                    int max = list[beginning];
                    for(int i = beginning; i<=last ; i++)
                    {
                        if(list[i]>=max)
                        {
                            max = list[i];
                        }
                    }
                    System.out.println("The answer is ");
                    System.out.println(max);
                    func2();
                    break;

                case 4:
                    System.out.println("Enter initial index");
                    fib();
                    beginning = in.nextInt();
                    System.out.println("Enter final index");

                    last = in.nextInt();
                    func1();
                    fib();
                    int z = obj.find_the_min_value(partForMin, 0, size - 1, beginning, last, 0);
                    int min = list[beginning];
                    for (int i = beginning; i <= last; i++) {
                        if (list[i] <= min) {
                            min = list[i];
                        }
                    }
                    System.out.println("The answer is ");
                    System.out.println(min);
                    break;

                case 5:
                    System.out.println("Terminating .....Bye :)");
                    long endTime_global = System.currentTimeMillis();
                    long durationInNano = (endTime_global - startTime_global);
                    System.out.println("The total execution time of the program in milli seconds is " + durationInNano);
                    fib();
                    System.exit(0);

                default:
                    System.out.println("Enter Again , wrong input");
                }

            }

            long endTime = System.currentTimeMillis();
            long durationInNano = (endTime - startTime);
            System.out.println("The execution time in milli seconds is "+durationInNano);
        }
        
       
        
        

    }

    int find_the_sum_value(int part[], int segbeginning, int seglast, int beginning, int last, int index) {

        if (beginning <= segbeginning && last >= seglast) {
            func1();
            fib();
            return part[index];
        }

        if (seglast < beginning || segbeginning > last)
            {   func2();
                fib();
                return 0;}

        int intermediate = segbeginning + (seglast - segbeginning) / 2;
        fib();
        return (find_the_sum_value(part, segbeginning, intermediate, beginning, last, 2 * index + 1)
                + find_the_sum_value(part, intermediate + 1, seglast, beginning, last, 2 * index + 2));

    }


    int Sum(int list[], int beginning, int last, int part[], int index) {
        if (beginning == last) {
            part[index] = list[beginning];
            fib();
            func1();
            return list[beginning];
        }

        int intermediate = beginning + (last - beginning) / 2;
        int pre = Sum(list, beginning, intermediate, part, index * 2 + 1);
        func2();
        int post = Sum(list, intermediate + 1, last, part, index * 2 + 2);
        fib();
        part[index] = pre + post;

        return part[index];
    }

    void Max_Update(int arr[], int part[], int segbeginning, int seglast, int value, int beginning, int last,
            int index) {

        for (int i = beginning; i <= last; i++) {
            func1();
            int difference = value;
            fib();
            Update_Max(arr, part, segbeginning, seglast, i, difference, 0);
        }

    }

    void update_the_value(int part[], int segbeginning, int seglast, int difference, int update_the_valueIndex,
            int index) {

        if (update_the_valueIndex < segbeginning || update_the_valueIndex > seglast) {
            func2();
            return;
        }

        part[index] += difference;
        fib();

        if (segbeginning != seglast) {
            func1();
            int intermediate = segbeginning + (seglast - segbeginning) / 2;
            update_the_value(part, segbeginning, intermediate, difference, update_the_valueIndex, 2 * index + 1);
            fib();
            update_the_value(part, intermediate + 1, seglast, difference, update_the_valueIndex, 2 * index + 2);
        }

    }


    int find_the_min_value(int part[], int segbeginning, int seglast, int beginning, int last, int index) {
        if (beginning <= segbeginning && last >= seglast)
           {    func1();
               return part[index];}

        if (seglast < beginning || segbeginning > last)
            {   func2();
                fib();
                return 1000000000;}

        int intermediate = segbeginning + (seglast - segbeginning) / 2;

        int pre = find_the_min_value(part, segbeginning, intermediate, beginning, last, 2 * index + 1);
        func1();
        int post = find_the_min_value(part, intermediate + 1, seglast, beginning, last, 2 * index + 2);
        fib();
        return (pre <= post ? pre : post);
    }

    void Min_Update(int arr[], int st[], int segbeginning, int seglast, int update_the_valueIndex, int value,
            int index) {
        if (update_the_valueIndex < segbeginning || update_the_valueIndex > seglast) {
            func2();
            System.out.println("Please enter again , invalid input");
            fib();
            return;
        }

        if (segbeginning == seglast) {
            arr[update_the_valueIndex] += value;
            func1();
            st[index] += value;
            fib();
        } else {
            int intermediate = segbeginning + (seglast - segbeginning) / 2;

            if (update_the_valueIndex >= segbeginning && update_the_valueIndex <= intermediate)
                Min_Update(arr, st, segbeginning, intermediate, update_the_valueIndex, value, 2 * index + 1);
            else
                Min_Update(arr, st, intermediate + 1, seglast, update_the_valueIndex, value, 2 * index + 2);

            st[index] = Math.min(st[2 * index + 1], st[2 * index + 2]);
            fib();
            func2();
        }
        return;
    }

    public static void func2()
    {   
        fib();
        System.out.print("");
    }

}