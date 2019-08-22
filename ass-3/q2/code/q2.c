#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct QNode{
    int i,j,k;
    struct QNode* link;
};
struct QNode *Qfirst = NULL,*Qlast=NULL;

/**
* This method will be used to store the i ,j ,k values in the linked list.
* @param ii  integer i for (i , j , k)
* @param jj  integer i for (i , j , k)
* @param kk  integer i for (i , j , k)
* @author Kavya Barnwal
* @date 20/08/2019
*/
void store(int ii,int jj,int kk){
    struct QNode* nd=malloc(sizeof(struct QNode));
    nd->i=ii+1;
    nd->j=jj+1;
    nd->k=kk+1;
    
    if(Qlast==NULL){
        Qfirst=Qlast=nd;
        Qlast->link=NULL;
    }
    else{
        Qlast->link=nd;
        Qlast=nd;
        nd->link=NULL;
    }
}

struct Node{
    int data;
    struct Node* next,* prev;
};
struct Node *first = NULL,*last=NULL;
int length=0;

/**
* This method will be used to store the the given value d into a new node which will bw inserted in the linked list.
* @param d integer data provided to insert in the linked list.
* @author Kavya Barnwal
* @date 20/08/2019
*/
void insert(int d){
    struct Node* nd=malloc(sizeof(struct Node));
    nd->data=d;
    if(last==NULL){
        first=last=nd;
        first->prev=NULL;
        last->next=NULL;
    }
    else{
        last->next=nd;
        nd->prev=last;
        last=nd;
        nd->next=NULL;
    }
    length++;
}

/**
* This method generates a lookup table for XOR outputs from ith entry of linked list to jth entry ,and stores and return
*  a 2-d array whose i,j entry denotes the XOR of ith input to jth input.
* @param l integer length , of the given linked list.
* @author Kavya Barnwal
* @date 20/08/2019
*/
int** XORi2l(int l){
    int **XOR;
    XOR = malloc(sizeof(int*) * l);
     
    for(int i = 0; i < l; i++) {
        XOR[i] = malloc(sizeof(int*) * l);
    }

    struct Node* hd=first;
    XOR[0][0]=hd->data;
    hd=hd->next;
    for(int i=1;i<l;i++){
        XOR[0][i]=XOR[0][i-1]^hd->data;
        hd=hd->next;
    }
    for(int i=1;i<l;i++){
        for(int j=0;j<i;j++){
            XOR[i][j]=-1;
        }
        for(int j=i;j<l;j++){
            XOR[i][j]=XOR[0][i-1]^XOR[0][j];
        }
    }
    return XOR;
}

/**
* Helper method for countTriplets ,which counts triplets using the 2-d array XOR(lookup table)
* @param XOR 2-d integer array , whose i,j entry denotes the XOR of ith input to jth input.
* @param i  integer i for (i , j , k)
* @param k  integer i for (i , j , k)
* @param l integer length , of the given linked list.
* @author Kavya Barnwal
* @date 20/08/2019
*/
int count(int **XOR,int i,int k,int l){
    int c=0;
    for(int j=i+1;j<=k;j++){
        if(XOR[i][j-1]==XOR[j][k]){
            store(i,j,k);
            c++;
        }
    }
    return c;
}

/**
* This method will be used to count all the possibles triplets i ,j ,k .
* @param l integer length , of the given linked list.
* @author Kavya Barnwal
* @date 20/08/2019
*/
int countTriplets(int l){
    int counter=0;
    int **XOR=XORi2l(l);
    for(int i=0;i<l;i++){
        for(int k=i+1;k<l;k++){
            if(XOR[i][k]==0){
                counter+=count(XOR,i,k,l);
            }
        }
    }
    return counter;
}

/**
* This method will be used to print all the possibles triplets i ,j ,k .
* @author Kavya Barnwal
* @date 20/08/2019
*/

void showTriplets(){
    struct QNode* hd=Qfirst;
    while(hd!=NULL){
        printf("( %d , %d , %d )\n",hd->i,hd->j,hd->k);
        hd=hd->link;
    }
}

int main()
{   ///initializing the clock
    double time=0.0;
    clock_t starting=clock();

    int a[]={5,2,7};
    insert(5);
    insert(2);
    insert(7);
    
    int c=countTriplets(length);
    printf("%d\n",c);
    showTriplets();
    

    clock_t ending=clock();
    time+=(double)(ending-starting)/CLOCKS_PER_SEC;
    printf("\nTotal Execution time is : %f (sec)\n",time);
    return 0;
}
