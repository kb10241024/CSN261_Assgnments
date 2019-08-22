#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
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
        printf("\n");       
    }
    fclose(fp);
	if(flag){
		int l=strlen(input);
		input[l-1]='\0';
	}
    return input;
};


int main(int varc,char *argv[]){
    double time=0.0;
    clock_t starting=clock();

    char *p1=argv[1];
    char *p2=argv[2];

    char* file1=readFile(p1);
    char* file2=readFile(p2);

    if(strcmp(file1,file2)==0){
        printf("Files matched\n");
    }else{
        printf("Files didn't match and files are :\n");
        printf("/******\n%s\n*****/",file1);
        printf("/******\n%s\n*****/",file2);        
    }

    clock_t ending=clock();
    time+=(double)(ending-starting)/CLOCKS_PER_SEC;
    printf("\nTotal Execution time is : %f (sec)\n",time);

    return 0;
}