#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/**
* @file Students DataBase
* @brief Implemented using doubly-linked-list of Student Nodes
*
* @author Kavya Barnwal
*
* @date 31/07/2019
*/

///student nodes storing Roll,Name,Address,DOB and Phone number.
struct Student { 
    int Roll; 
    char Name[100],Address[100],DOB[20];
    long long int Phone;
    struct Student* next,*prev; 
};
///first and last Nodes pointing to front and rear of doubly-linked-list
struct Student *first = NULL,*last=NULL;
///containing the current roll count at each instant
int rollCount=100;

///QNode for storing unusedRolls
struct QNode{
    int data;
    struct QNode* link;
};
///Qfront and Qrear are the pointers to front and rear of the queue
struct QNode *Qfront=NULL,*Qrear=NULL;
///enqueue data into the queue for unusedRolls
void enqueue(int d){
    struct QNode* temp=(struct QNode*)malloc(sizeof(struct QNode));
    temp->data=d;
    if(Qrear==NULL){
        Qfront=Qrear=temp;
        Qrear->link=NULL;
    }else{
        Qrear->link=temp;
        Qrear=temp;
        Qrear->link=NULL;
    }
}
///dequeue data from the queue for unusedRolls
int dequeue(){
    if(Qfront==NULL){
        printf("Nothing to return");
        return -1;
    }else{
        struct QNode* temp=(struct QNode*)malloc(sizeof(struct QNode));
        temp=Qfront;
        int d=temp->data;
        if(Qfront!=Qrear){
            Qfront=Qfront->link;
        }
        else{
            Qfront=Qrear=NULL;
        }
        free(temp);
        return d;
    }
}

//search with roll
/**
* This method will be used to search the student with given Roll.
* @author Kavya Barnwal
* @param roll used to search in DataBase
* @date 31/07/2019
*/

struct Student* search(int roll){
    struct Student* head=first;
    while(head!=NULL){
        if(head->Roll==roll){
            return head;
        }
        head=head->next;
    }
    printf("No Student exist in database with roll : %d\n",roll);
    return NULL;
}
//insert a student in the last with his details
/**
* This method will be used to inserStudent with given details except Roll.
* @author Kavya Barnwal
* @param name , dob , addrs ,phone required details of sudents
* @date 31/07/2019
*/
void insertStudent(char nm[],char dob[],char adrs[],long long int phone){
    struct Student* stdnt=malloc(sizeof(struct Student));
    strcpy(stdnt->Name,nm);
    strcpy(stdnt->Address,adrs);
    strcpy(stdnt->DOB,dob);
    stdnt->Phone=phone;
    if(last==NULL){
        rollCount=101;
        stdnt->Roll=101;
        first=last=stdnt;
        first->prev=NULL;
        last->next=NULL;
    }
    else{
        if(Qfront==NULL){
            stdnt->Roll=++rollCount;
        }else{
            stdnt->Roll=dequeue();
        }
        last->next=stdnt;
        stdnt->prev=last;
        last=stdnt;
        last->next=NULL;
    }
}
//perform deletion of student with given roll
/**
* This method will be used to perform deletion of student with given Roll.
* @author Kavya Barnwal
* @param roll used to search in DataBase
* @date 31/07/2019
*/
struct Student* delete(int roll){
    if(first!=NULL){
        if(first->Roll==roll){
            struct Student *temp=first;
            first=first->next;
            first->prev=NULL;
            enqueue(roll);
            return temp;
        }
        if(last->Roll==roll){
            struct Student *temp=last;
            last=last->prev;
            last->next=NULL;
            enqueue(roll);
            return temp;
        }
        struct Student* head=first->next;
        while(head!=NULL){
            if(head->Roll==roll){
                struct Student* temp=head;
                head->prev->next=head->next;
                head->next->prev=head->prev;
                enqueue(roll);
                return temp;
            }
            head=head->next;
        }
        printf("No Student exist in database with roll : %d\n",roll);
        return NULL;
    }
    printf("There is No student in database.\n");
    return NULL;
}
//modifies the details of student except Roll
/**
* This method will be used to modify details of student excpept Roll.
* @author Kavya Barnwal
* @param roll used to search in DataBase, nm,dob,adrs,phone to be updated.
* @date 31/07/2019
*/
void modify(int roll,char nm[],char dob[],char adrs[],long long int phone){
    struct Student* stdnt=search(roll);
    if(stdnt!=NULL){
        strcpy(stdnt->Name,nm);
        strcpy(stdnt->Address,adrs);
        strcpy(stdnt->DOB,dob);
        stdnt->Phone=phone;
    }
}
// the given Student 
/**
* This method will be used to print the list of all students.
* @author Kavya Barnwal
* @param student ,head of the Doubly-linked-list of students
* @date 31/07/2019
*/
void print(struct Student* n){
    printf("/**********\n");
    while (n != NULL) { 
        //printf("Student with Roll:%d,Name:%s,DOB:%s,Address:%s , and Phone: %lld \n",n->Roll,n->Name,n->DOB,n->Address,n->Phone); 
        printf("Roll:%d,Name:%s,DOB:%s.\n",n->Roll,n->Name,n->DOB); 
        n = n->next; 
    } 
    printf("**********/\n");    
} 
/**
* This method will be used to perform swapping of details of two students.
* @author Kavya Barnwal
* @param s1,s2 to be swapped
* @date 31/07/2019
*/
void swap(struct Student* s1,struct Student* s2){
    int temp=s1->Roll;
    s1->Roll=s2->Roll;
    s2->Roll=temp;
    char ch[100];
    strcpy(ch,s1->Name);
    strcpy(s1->Name,s2->Name);
    strcpy(s2->Name,ch);
    
    strcpy(ch,s1->DOB);
    strcpy(s1->DOB,s2->DOB);
    strcpy(s2->DOB,ch);
    
    strcpy(ch,s1->Address);
    strcpy(s1->Address,s2->Address);
    strcpy(s2->Address,ch);
    
    long long int p1=s1->Phone;
    s1->Phone=s2->Phone;
    s2->Phone=p1;
}
/**
* This method will be used to perform sorting by name.
* @author Kavya Barnwal
* @date 31/07/2019
*/
void sort(){
    struct Student* hd=first;
    while(hd->next!=NULL){
        struct Student* hd2=first;
        while(hd2->next!=NULL){
            int cmp=strcmp(hd2->Name,hd2->next->Name);
            if(cmp>0){
                swap(hd2,hd2->next);
            }
            hd2=hd2->next;
        }
        hd=hd->next;
    }
}
void removeChar(char *s, int c){ 

    int j=0, n = strlen(s); 
    for (int i=j=0; i<n; i++) 
    if (s[i] != c) 
        s[j++] = s[i]; 
    
    s[j] = '\0'; 
}
long long int ConvertCharToLong(char *pSrc) {
    int i=1;
    long long int result = (int)pSrc[0] - '0';
    while(i<strlen(pSrc)){
         result = result * 10 + ((int)pSrc[i] - '0');
         ++i;
    }
    return result;
}
void getData(char data[])
{
   char dd[15][100];
   char *token = strtok(data,",");
   int counter=0;
 
   while( token != NULL ) 
   {
    strcpy(dd[counter],token);
        counter++; 
    token = strtok(NULL,",");
   }      
    int i=4;
    while(i!=counter-1){
        strcat(dd[3],",");
        strcat(dd[3],dd[i]);
        i++;
    }
    removeChar(dd[1],'\"');
    removeChar(dd[2],'\"');
    removeChar(dd[3],'\"'); 
    removeChar(dd[counter-1],'\"');
    long long int phn=ConvertCharToLong(dd[counter-1]);
    insertStudent(dd[1],dd[2],dd[3],phn);  

}
/**
* This method will be used to read the complete data in Student.csv file(all students).
* @author Kavya Barnwal
* @date 31/07/2019
*/
void readData(){
    FILE* stream = fopen("StudentData.csv", "r");

    char line[1024];
    fgets(line, 1024, stream);//it will initially read the header so that we'll not pass it 
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        getData(tmp);     
        // NOTE strtok clobbers tmp
        free(tmp);
    }
}
/**
* This method will be used to perform insertion of student with given number.
* @author Kavya Barnwal
* @param num representing the (row-1) to be inserted
* @date 31/07/2019
*/
void insert(int num){
    FILE* stream = fopen("StudentData.csv", "r");

    char line[1024];
    fgets(line, 1024, stream);//it will initially read the header so that we'll not pass it 
    while (num-->0 && fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        if(num==0)
        getData(tmp);     
        // NOTE strtok clobbers tmp
        free(tmp);
    }
}


int main() 
{ 
    double time=0.0;
    clock_t starting=clock();

    delete(108);
    insert(1);
    insert(2);
    insert(3);
    insert(4);
    delete(102);
    delete(101);
    insert(5);
    insert(6);
    insert(7);
    print(first);

    sort();

    print(first);
    
    modify(103,"Kavya Barnwal","30-sep-2001","G45 Ravindra Bhawan IIT Roorkee",8409466819);
    print(first);
    
    clock_t ending=clock();
    time+=(double)(ending-starting)/CLOCKS_PER_SEC;
    printf("\nTotal Execution time is : %f (sec)\n",time);
    
    return 0; 
}








