/**
* @file stdio.h
* @breif this header file will contain the input/output function like scanf and printf.
* 
* @author Kavya Barnwal
* 
* @date 31/07/2019
*/
#include<stdio.h>
/**
* @file stdlib.h
* @breif this header file will contain the funtions involving memory allocation, process control, 
* conversions and others.
* 
* @author Kavya Barnwal
* 
* @date 31/07/2019
*/
#include<stdlib.h>
/**
* @file stdio.h
* @breif this header file contains time and date functions declarations to provide standdardized access
* to time/date manipulation and formatting
*
* @author Kavya Barnwal
* 
* @date 31/07/2019
*/
#include<time.h>

int MAX=10;///<MAX is the maximum size of array used by the DEQUEUE
int CURRENTSIZE=0;///<CURRENTSIZE represents the currentsize of DEQUEUE at any time

int* deque;///<deque is the array used for DEQUEUE
int front=-1, rear=-1;///<front and rear are the pointers to the FRONT and REAR points respectively.


void insert_rear(int);
void insert_front(int);
void delete_rear(void);
void delete_front(void);
void display(void);
void double_size(void);
void half_size(void);
void print(void);

int main()
{
    double time=0.0;
    clock_t starting=clock();

    //Initializing the memory to deque 
    deque=(int*)malloc(MAX*sizeof(int));

    insert_rear(10);
    insert_front(8);
    insert_front(6);
    insert_front(4);
    insert_front(2);
    insert_rear(12);
    display();
    print();
    delete_rear();
    print();
    insert_rear(11);
    print();
    display();

    clock_t ending=clock();
    time+=(double)(ending-starting)/CLOCKS_PER_SEC;
    printf("\nTotal Execution time is : %f (sec)\n",time);     
    
    return 0;
}


//!-------INSERT AT rear -------
/**
* This method will be used to insert at the rear end of the deque 
* @author Kavya Barnwal
* @param value   Value to be inserted
* @date 31/07/2019
*/
void insert_rear(int val){
 //Check if DEQUEUE is full
 if( (front==0 && rear==MAX-1) || (front==rear+1) )
 {
  printf("\nOVERFLOW\nDoubling the capacity of DEQUEUE");
  //Use double_size() method to double the size of array if it overflows
  double_size();
  rear++;
 }
 else{
    //Check if dequeue is initially empty
     if(front==-1)        
     {
      front=0;
      rear=0;
     }
     else
     {//Check if rear is pointing to the last index
      if(rear==MAX-1)
       rear=0;
      else
       rear=rear+1;
     }
 }
 deque[rear]=val;
 CURRENTSIZE++;
}
//!-------INSERT AT front -------
/**
* This method will be used to insert at the front end of the deque 
* @author Kavya Barnwal
* @param value   Value to be inserted
* @date 31/07/2019
*/
void insert_front(int val){
  //Check if DEQUEUE is full
 if( (front==0 && rear==MAX-1) || (front==rear+1) )
 {
  printf("\nOVERFLOW\nDoubling the capacity of DEQUEUE");
  //Use double_size() method to double the size of array if it overflows
  double_size();
  front=MAX-1;
  deque[front]=val;
 }
 else{
  //Check if dequeue is initially empty
     if(front==-1)        
     {
      front=0;
      rear=0;
     }
     else
     {//Check if front is pointing to the 0th index
      if(front==0){
       front=(MAX-1);
      }
      else{
       front--;
      }
     }
     deque[front]=val;
     CURRENTSIZE++;
 }

}
//!-------DELETE FROM rear-------
/**
* This method will be used to delete rear end of the deque 
* @author Kavya Barnwal
* 
* @date 31/07/2019
*/
void delete_rear(){
 if(front==-1)
 {
  printf("\nUNDERFLOW");
  return;
 }
 printf("\nThe deleted element is %d\n", deque[rear]);
 CURRENTSIZE--;
 if(front==rear)//Check if dequeue has only one element
 {
  front=-1;
  rear=-1;
 }
 else
 {
  if(rear==0)//Check if rear pointing to 0th index
   rear=MAX-1;
  else
   rear=rear-1;
 }
 if(CURRENTSIZE==(MAX/2)){
  // Use half_size() method if the size of deque gets halved after deletion 
     half_size();
 }
}
//!-------DELETE FROM front-------
/**
* This method will be used to delete front end of the deque 
* @author Kavya Barnwal
*
* @date 31/07/2019
*/
void delete_front(){
  //Check if DEQUEUE is initially empty
 if(front==-1)
 {
  printf("\nUNDERFLOW");
  return;
 }
 printf("\nThe deleted element is %d\n", deque[front]);
 CURRENTSIZE--;
 if(front==rear)          //Check if dequeue has only one element
 {
  front=-1;
  rear=-1;
 }
 else
 {
  if(front==MAX-1)//Check if front is pointing to last index
   front=0;
  else
   front=front+1;
 }
 if(CURRENTSIZE==(MAX/2)){
  // Use half_size() method if the size of deque gets halved after deletion 
     half_size();
 }
}
//!-------display() DISPLAYS the all elements in the DEQUEUE-------

void display(){
 int l=front, r=rear;
 if(l==-1)
 {
  printf("\nQueue is Empty\n");
  return;
 }
 printf("\nThe elements in the queue are: ");
 if(l<=r)
 {
  while(l<=r)
  {
   printf("%d\t",deque[l]);
   l++;
  }
 }
 else
 {
  while(l<=MAX-1)
  {
   printf("%d\t",deque[l]);
   l++;
  }
  l=0;
  while(l<=r)
  {
   printf("%d\t",deque[l]);
   l++;
  }
 }
 printf("\n");
}

//!method used to double the size of array
/**
* This method will double the capacity of the  deque
* @author Kavya Barnwal
* 
* @date 31/07/2019
*/
void double_size(){
    int *b=(int*)malloc(2*MAX*sizeof(int));
    int l=front, r=rear;
    int i=0;
    if(l<=r){
        while(l<=r){
            b[i]=deque[l];
            l++;
            i++;
        }
    }
    else {
    while(l<=MAX-1)
    {
        b[i]=deque[l];
        i++;
        l++;
    }
    l=0;
    while(l<=r)
    {
        b[i]=deque[l];
        i++;
        l++;
    }
    }
    free(deque);
    deque=b;
    front=0;
    rear=i-1;
    MAX*=2;
}


//!method used to half the size of array
/**
* This method will half the capacity of the dequeue
* @author Kavya Barnwal
* 
* @date 31/07/2019
*/
void half_size(){
    int *b=(int*)malloc((MAX/2)*sizeof(int));
    int l=front, r=rear;
    int i=0;
    if(l<=r){
        while(l<=r){
            b[i]=deque[l];
            l++;
            i++;
        }
    }
    else {
    while(l<=MAX-1)
    {
        b[i]=deque[l];
        i++;
        l++;
    }
    l=0;
    while(l<=r)
    {
        b[i]=deque[l];
        i++;
        l++;
    }
    }
    free(deque);
    deque=b;
    front=0;
    rear=i-1;
    MAX/=2;
}

//!Prints the capacity of DEQUEUE
/**
* This method will print the capacity of the dequeue in terms of bytes.
* @author Kavya Barnwal
* 
* @date 31/07/2019
*/
void print(){
  int cap=MAX*4;
  printf("\nThe current capacity of DEQUEUE is %d ",cap);
}