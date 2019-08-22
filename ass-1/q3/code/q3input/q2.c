#include<stdio.h>

#include<string.h>

void getData(char *buff);
int main()
{        
	FILE *fp=fopen("q3input/Q3_ip_Blue.dat","r");
	int count=0;
	
	do{
		char buff[1268];
		fgets(buff,1268,(FILE*)fp);
		count++;
		//printf("%s",buff);
		getData(buff);
			
	}while((getc(fp))!=EOF);

	
}

void getData(char buff[])
{
	char *token = strtok(buff, ",");
	int counter=0;char arr[1500][1500];
	int i,j=0;
	
        while(token != NULL)
	{
		counter++;
		if(j<952){
			arr[i][j]=token;
			printf("%d\n",arr[i][j]);
			j++;		
		}else{ 
			arr[i][j]=token;
			printf("%d\n",arr[i][j]);
			i++;j=0;
			}
	}
		printf("%s\n",token);
			token=strtok(NULL,",");

}