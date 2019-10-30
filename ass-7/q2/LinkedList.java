/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

 //java.lang.System.nanoTime() ;


// Java program to implement 
// a Singly Linked List 
import java.util.*;

 public class LinkedList { 

	Node head; // head of list 
	static class Node { 

		int start;
                int last;
                int maximum;
                int minimum;
                int sum;
		Node left;
                Node right;

		Node(int st,int en,int max,int min,int summa) 
		{ 
			start=st;
                        last=en;
                        maximum=max;
                        minimum=min;
                        sum=summa;
			left = null; 
                        right = null;
		} 
	} 

	// Method to insert a new node 
	public static void storeinfo(LinkedList list,int arr[],int starting,int ending){
            int mid2=0;
            int max =findMax(arr,starting,ending);
            int min=findMin(arr,starting,ending);
            int summation = findSum(arr,starting,ending);
            int mid = starting +(ending-starting)/2;
            Node lead = new Node(starting,ending,max,min,summation);
            lead.right=null;
            lead.left=null;
            if(list.head==null){
                list.head=lead;
            }
            else{
                Node temp = list.head;
                Node temp2 = list.head;
                while(temp!=null){
                    mid2 = temp.start + (temp.last-temp.start)/2;
                    if(starting>mid2){
                        temp2 = temp;
                        temp = temp.right;
                    }
                    else{
                        temp2 = temp;
                        temp = temp.left;
                    }
                }
                if(starting>mid2){
                    temp2.right = lead;
                }
                else{
                    temp2.left = lead;
                }
            }
            if(ending!=starting){
                storeinfo(list,arr,starting,mid);
                storeinfo(list,arr,mid+1,ending);
            }
            /*if(list.head!=null){
            System.out.println(max+min+summation);
            }*/
        }
         
        public static  void findBetweenIndex(LinkedList list,int starting,int ending,int arr[]){
            long startTime = System.nanoTime();
            //int size = arr.length;
            //int mid = (size-1)/2;
            int tempArr[]={0,1000,0};
            findByFirst(list,starting,ending,tempArr,list.head);
            long endTime   = System.nanoTime();
            long totalTime = endTime - startTime;
            System.out.println("Time - " + totalTime);
            System.out.println("Max- "+tempArr[0]+"\n"+"Min "+tempArr[1]+"\n"+"Sum "+tempArr[2]);
        }
        
        public static void update(LinkedList list,int starting,int ending,int arr[]){
            int mid = starting +(ending-starting)/2;
            for(int i=starting;i<=ending;i++)
                arr[i]+=4;
            updateNode(list.head,arr);
            //print(list.head);
        }
        
        public static void updateNode(Node temp,int arr[]){
            temp.maximum = findMax(arr,temp.start,temp.last);
            temp.minimum = findMin(arr,temp.start,temp.last);
            temp.sum = findSum(arr,temp.start,temp.last);
            if(temp.right!=null)
                updateNode(temp.right,arr);
            if(temp.left!=null)
                updateNode(temp.left,arr);
        }
        
        public static void print(Node temp){
            System.out.println(temp.start+"-"+temp.last+" min- "+temp.minimum+" max- "+temp.maximum+"  sum- "+temp.sum);
            if(temp.right!=null)
                print(temp.right);
            if(temp.left!=null)
                print(temp.left);
        }
        
        public static void findByFirst(LinkedList list,int starting,int ending,int tempArr[],Node temp){
            int count=0;
            int mid = temp.start + (temp.last-temp.start)/2;
            if((temp.start==starting)&&(temp.last==ending)){
                if(tempArr[0]<temp.maximum)
                    tempArr[0] = temp.maximum;
                if(tempArr[1]>temp.minimum)
                    tempArr[1] = temp.minimum;
                tempArr[2] += temp.sum;
            }
            else if(starting>mid)
                findByFirst(list,starting,ending,tempArr,temp.right);
            else if(ending<=mid)
                findByFirst(list,starting,ending,tempArr,temp.left);
            else{
                findByFirst(list,starting,mid,tempArr,temp.left);
                findByFirst(list,mid+1,ending,tempArr,temp.right);
            }
        }
        
        public static int findMax(int arr[],int starting,int ending){
            int m = 0;
            for(int i=starting;i<=ending;i++){
            if(arr[i]>m)
            m=arr[i];
            }
            return m;
        }
        public static int findMin(int arr[],int starting,int ending){
            int m = arr[starting];
            for(int i=starting;i<=ending;i++){
            if(arr[i]<m)
            m=arr[i];
            }
            return m;
        }
        public static int findSum(int arr[],int starting,int ending){
            int m = 0;
            for(int i=starting;i<=ending;i++){
            m+=arr[i];
            }
            return m;
        }
	
        public static void bruteforce(int arr[],int starting,int ending){
            long startTime = System.nanoTime();
            int max=arr[starting];
            int min=arr[starting];
            int sum=arr[starting];
            for(int i=(starting+1);i<=ending;i++){
                if(arr[i]>max)
                    max=arr[i];
                if(arr[i]<min)
                    min=arr[i];
                sum+=arr[i];
            }
            long endTime   = System.nanoTime();
            long totalTime = endTime - startTime;
            System.out.println("Time - "+totalTime);
            System.out.println("Min- "+min+"\nMax- "+max+"\nSum- "+sum);
        }
        
	public static void main(String[] args) 
	{ 
		/* Start with the empty list. */
		LinkedList list = new LinkedList();
                Scanner in=new Scanner(System.in);
                System.out.println("Give the no. of elements in array");
                int x = in.nextInt();
                System.out.println("Enter array elements");
                int arr[]=new int[x];
                for(int i=0;i<x;i++){
                arr[i]=in.nextInt();
                }
                System.out.println("Give the starting and end index");
                int i1=in.nextInt();
                int i2=in.nextInt();
                
                storeinfo(list,arr,0,x-1);
                //print(list.head);
                
                int z=0;
                System.out.println("Enter 1 to compute by segment tree\nEnter 2 to compute by brute force\nEnter 3 to update value\nEnter 4 to exit");
                while(z!=4){
                z=in.nextInt();
                if(z==1) findBetweenIndex(list,i1,i2,arr);
                else if(z==2) bruteforce(arr,i1,i2);
                else if(z==3) update(list,i1,i2,arr);
                }
		
                //System.out.println(x);
                //update(list,2,4,arr);
	} 
} 
