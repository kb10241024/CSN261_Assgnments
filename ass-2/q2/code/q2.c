#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
/**
 * This Node is used to build quad tree having the 
 * index as index of that node
 * bitValue as bit value for that node
 * level as level of that node
 */
struct Node { 
    int index;
    int bitValue;
    int level;
    struct Node *prev,*next; 
};
///first and last Nodes pointing to front and rear of doubly-linked-list
struct Node *first = NULL,*last=NULL;
/**
* This method will be used to check whether the quadrant with size rounds,of image-array which starts from beginRow and beginCol.
* @param arr  input Image-Array  .
* @param beginRow Index of beginning row of that quadrant.
* @param beginCol Index of beginning column of that quadrant.
* @param round size of the quandrant to be checked.
* @author Kavya Barnwal
* @date 31/07/2019
*/
bool check(int **arr,int beginRow,int beginCol,int rounds){
    bool flag=true;
    for(int i=0;flag && i<rounds;i++){
        for(int j=0;flag && j<rounds;j++){
            if(arr[beginRow+i][beginCol+j]!=arr[beginRow][beginCol]){
                flag=false;
            }
        }
    }
    return flag;
};
/**
* This method will be used to get the just next coming exponent of 2.
* @param n  Integer after which exponent of 2 is req. 
* @author Kavya Barnwal
* @date 31/07/2019
*/
int nearest2Exponent(int n){
    int e=n;
    while((e & (e-1))!=0){
        e++;
    }
    return e;
};
/**
* This method will be used to add the node to the quad-tree.
* @param l  level of the new node.
* @param v  bit-value of that node 
* @author Kavya Barnwal
* @date 31/07/2019
*/
void addNode(int l,int v){
    if(first==NULL){
        first=(struct Node*)malloc(sizeof(struct Node));
        first->bitValue=v;
        first->index=1;
        first->level=l;
        last=first;
        first->prev=NULL;
        last->next=NULL;
    }
    else{
        struct Node* nd=(struct Node*)malloc(sizeof(struct Node));
        nd->bitValue=v;
        nd->level=l;
        nd->index=last->index+1;
        last->next=nd;
        nd->prev=last;
        last=nd;
        last->next=NULL;
    }
};
/**
* This method will be used to fill Maximal Square Array.
* @param maximalSquareArray  Maximal-square-Array.
* @param br Index of beginning row of that quadrant.
* @param bc Index of beginning column of that quadrant.
* @param n size of the quandrant to be checked.
* @author Kavya Barnwal
* @date 31/07/2019
*/
void fillMaximalSquareArray(int **maximalSquareArray,int br,int bc,int n){
    int index=1;
    if(first!=NULL){
        index=(last->index)+1;
    }
    for(int i=br;i<(br+n);i++){
        for(int j=bc;j<(bc+n);j++){
            maximalSquareArray[i][j]=index;
        }
    }
};
/**
* This method will be used to partition the Image-Array into its further quadrants.
* @param maximalSquareArray  Maximal-square-Array.
* @param arr  Image-Array.
* @param beginRow Index of beginning row of that quadrant.
* @param beginCol Index of beginning column of that quadrant.
* @param n size of the quandrant to be checked.
* @param level level of that node.
* @author Kavya Barnwal
* @date 31/07/2019
*/
void partition(int **maximalSquareArray,int **arr,int beginRow,int beginCol,int n,int level){
    int rounds=n/2;
    
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            int br=beginRow+i*rounds;
            int bc=beginCol+j*rounds;
            if(check(arr,br,bc,rounds)){
                fillMaximalSquareArray(maximalSquareArray,br,bc,rounds);
                addNode(level,arr[br][bc]);
            }else{
                partition(maximalSquareArray,arr,br,bc,rounds,level+1);
            }
            
        }
    }
};
/**
* This method will be used to print the quad-tree.
* @author Kavya Barnwal
* @date 31/07/2019
*/
void printQuadTree(){
    printf("Quad-tree for the given input is :\n");
    struct Node* hd=first;
    while(hd!=NULL){
        printf("(%d , %d , %d)\n",hd->index,hd->bitValue,hd->level);
        hd=hd->next;
    }
}
/**
* This method will be used to print the maximal Square Array.
* @param maximalSquareArray  Maximal-square-Array.
* @param expo2 size of maximal square array
* @author Kavya Barnwal
* @date 31/07/2019
*/
void printMaximalSquareArray(int **maximalSquareArray,int expo2){
    printf("The maximal square array for given input is :\n");
    for(int i=0;i<expo2;i++){
        for(int j=0;j<expo2;j++){
            printf("%d ",maximalSquareArray[i][j]);
        }
        printf("\n");
    }
};

int main(int argc, char* argv[]){
    ///initializing the clock
    double time=0.0;
    clock_t starting=clock();

    ///get the path for the input array file
	char *path=argv[1];

    ///reading file from given path and converting to 2-d array
	FILE *fp;
    char str[1000];
    int i=0,l=0;
    fp = fopen(path, "r");
    if (fp == NULL){
        printf("Could not open file %s",path);
    }
	fgets(str, 1000, fp);
	l=strlen(str);
	int arr[l/2][l/2];	 
	for(int j=0;j<l-1;j+=2){
		arr[i][j/2]=(str[j]-'0');
	}   
	i++;
	while (fgets(str, 1000, fp) != NULL){
        for(int j=0;j<l-1;j+=2){
			arr[i][j/2]=(str[j]-'0');
		}   
		i++;   
    }	
    fclose(fp);
    ///file closed
	
    int row=l/2;
    int expo2=nearest2Exponent(row);

    ///sub is a substitue 2-d array for satisfying the condition of having sides of size exponents of 2
    int *sub[expo2];
    ///maximalSquareArray is maximal-aquare-array for given input
    int *maximalSquareArray[expo2];

    ///initializing maximalSquareArray and sub.
    for(int i=0;i<expo2;i++){
        sub[i]=(int *)malloc(sizeof(int)*expo2);
        maximalSquareArray[i]=(int *)malloc(sizeof(int)*expo2);
    }    
    for(int i=0;i<expo2;i++){
        for(int j=0;j<expo2;j++){
            if(i<(expo2-row) || j<(expo2-row)){
                sub[i][j]=0;
            }else{
                sub[i][j]=arr[i-(expo2-row)][j-(expo2-row)];
            }
        }
    }
    
    partition(maximalSquareArray,sub,0,0,expo2,1);   
    
    printMaximalSquareArray(maximalSquareArray,expo2);

    printQuadTree();

    clock_t ending=clock();
    time+=(double)(ending-starting)/CLOCKS_PER_SEC;
    printf("\nTotal Execution time is : %f (sec)\n",time);
    return 0;
}
