#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

/**
* This method will be used to get inverse-modulo of a w.r.t b .
* @param a  whose inverse is to find.
* @param b  w.r.t whose inverse is to find.
* @author Kavya Barnwal
* @date 31/07/2019
*/
int modularInverse(int a,int b){
	a%=b;
	if(a==0)return -1000000;
	if(a==1)return 1;
	return ((((1-b*modularInverse(b,a))/a)%b)+b)%b;
};
/**
* This method will be used to read File from a given path and return it as a string .
* @param path  Path of the file. 
* @author Kavya Barnwal
* @date 31/07/2019
*/
char* readFile(char *path){
    char *input=(char*)malloc(sizeof(char)*5000);
    
    FILE *fp;
    char str[1000];
    
    fp = fopen(path, "r");
    if (fp == NULL){
        printf("Could not open file %s",path);
        return NULL;
    }
	bool flag=true;
    while (fgets(str, 1000, fp) != NULL){
        int l=strlen(str);
        if(str[l-2]=='\r'){
            /*Remember '\r'==13 */
            // printf("Its backslash r -- carriage\n");
            str[l-2]='\0';        
			strcat(input,str);
			strcat(input,"\n");
			flag=true;
        }else{
			strcat(input,str);
			flag=false;
		}        
    }
    fclose(fp);
	if(flag){
		int l=strlen(input);
		input[l-1]='\0';
	}
    return input;
};
/**
* This method will be used to generate a new File to a given path by passing a string.
* @param filename  Path of the file to be genarated.
* @param output  String to be written in the new file.
* @author Kavya Barnwal
* @date 31/07/2019
*/
void generateOutput(char* filename,char *output){
    FILE * fp2;
    /* open the file for writing*/
    fp2 = fopen (filename,"w");
    
    /* write 10 lines of text into the file stream*/
    fprintf (fp2,output,1);
    
    /* close the file*/  
    fclose (fp2);
};
/**
* This method will be used to generate decrypted file with name "decryptedOutputfile.txt" by decrypting the file whose path is provided.
* @param n n(key) used for the encryption
* @param a a(key) used for the encryption
* @param b b(key) used for the encryption
* @param path  Path of the file to be decrypted.
* @author Kavya Barnwal
* @date 31/07/2019
*/
char* inverseTranspose(int n,int a,int b,char *path){
	char *str=(char*)malloc(sizeof(char)*5000);
    str=readFile(path);
	
    int ia=modularInverse(a,n);
    int ib=(n-(ia*b)%n)%n;

    int l=strlen(str);
    int rounds=l/n;
    char *plain;
    plain=(char*)malloc(sizeof(char)*(l));
    for(int i=0;i<rounds;i++){
        for(int j=0;j<n;j++){
            if(str[i*n+(ia*j+ib)%n]=='_'){
                plain[i*n+j]='\0';
                j=n;
            }else{
                plain[i*n+j]=str[i*n+(ia*j+ib)%n];
            }
        }
    }
	generateOutput("decryptedOutputfile.txt",plain);
    return plain;
};



int main(int argc,char *argv[]){
    double time=0.0;
    clock_t starting=clock();

    int n=atoi(argv[1]);
    int a=atoi(argv[2]);
    int b=atoi(argv[3]);
    char *s=argv[4];

    char *input=(char*)malloc(sizeof(char)*5000);
    char* filename = (char*)malloc(sizeof(char)*5000);
    strcpy(filename,s);
    
    char *plainText=inverseTranspose(5,3,2,filename);

    clock_t ending=clock();
    time+=(double)(ending-starting)/CLOCKS_PER_SEC;
    printf("\nTotal Execution time is : %f (sec)\n",time);
}
