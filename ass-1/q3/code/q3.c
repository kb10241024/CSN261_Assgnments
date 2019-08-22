#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/**
* @file Imamge modification 
* @brief Shades of image were modified
*
* @author Kavya Barnwal
*
* @date 31/07/2019
*/
int red[953][1268];///<2-d Array for Red color
int blue[953][1268];///<2-d Array for Blue color
int green[953][1268];///<2-d Array for Green color

//!Method to read a color .dat file with an argument "color"{e.g., "blue","red","green"}
/**
* This method will be used to read a color .dat file with an argument "color"{e.g., "blue","red","green"}
* @author Kavya Barnwal
* @param color to be choosen
* @date 31/07/2019
*/
void readcolor(char *color){
  int r=0,c=0;
  FILE *file;
  if(color=="red"){
    file=fopen("q3input/Q3_ip_Red.dat","r");
  }else if(color=="green"){
    file=fopen("q3input/Q3_ip_Green.dat","r");
  }else{
    file=fopen("q3input/Q3_ip_Blue.dat","r");
  }
    char yoyo[6000];
     if(file == NULL)
    {
       printf("Error: can't open file to read\n");
    }
    else{
      while(r<953){
          c=0;
          fgets(yoyo,6000,file);
          char latest[6000];
          strcpy(latest,yoyo);
          int  i=strlen(latest)-1;
          while(i>0){
              if(latest[i]==' '){
                  latest[i]='\0';
              }else{
                  break;
              }
              i--;
          }
          char* as=strtok(latest,",");
          while(as!=NULL){
            if(color=="red"){
              red[r][c]=atoi(as); 
            }else if(color=="blue"){
              blue[r][c]=atoi(as);
            }else{
              green[r][c]=atoi(as);
            }
              as=strtok(NULL,",");
              c++;
          }
        r++;
      }
    }   
    fclose(file);
}
/**
* This method will be used to print the pixel-value at (x,y).
* @author Kavya Barnwal
* @param x,y pixel co-ordinates
* @date 31/07/2019
*/
void pixelValue(int x,int y){
  if(x<953 && y<1268){
    printf("( %d , %d , %d )\n",red[x][y],green[x][y],blue[x][y]);
  }
  else{
    printf("Out Of Bounds\n");
  }
}

//!Removes only red shades
/**
* This method will be used to remove all red shades.
* @author Kavya Barnwal
* @date 31/07/2019
*/
void removeRed(){
  for(int i=0;i<953;i++){
    for(int j=0;j<1268;j++){
      if(red[i][j]>blue[i][j] && blue[i][j]>green[i][j]){
        red[i][j]=0;
      }
    }
  }
}

//!Removes only blue shades
/**
* This method will be used to remove all blue shades.
* @author Kavya Barnwal
* @date 31/07/2019
*/
void removeBlue(){
  for(int i=0;i<953;i++){
    for(int j=0;j<1268;j++){
      if(blue[i][j]>red[i][j] && blue[i][j]>green[i][j]){
        blue[i][j]=0;
      }
    }
  }
}

//!Removes only green shades
/**
* This method will be used to remove all green shades.
* @author Kavya Barnwal
* @date 31/07/2019
*/
void removeGreen(){
  for(int i=0;i<953;i++){
    for(int j=0;j<1268;j++){
      if(green[i][j]>blue[i][j] && green[i][j]>red[i][j]){
        green[i][j]=0;
      }
    }
  }
}

//!Removes blue and green shades
/**
* This method will be used to remove shades except red.
* @author Kavya Barnwal
* @date 31/07/2019
*/
void redOnly(){
  removeGreen();
  removeBlue();
}

//!Removes red and green shades
/**
* This method will be used to remove shades except blue.
* @author Kavya Barnwal
* @date 31/07/2019
*/
void blueOnly(){
  removeGreen();
  removeRed();
}

//!Removes red and green shades
/**
* This method will be used to remove shades except green.
* @author Kavya Barnwal
* @date 31/07/2019
*/
void greenOnly(){
  removeRed();
  removeBlue();
}

//!Save new .dat for modified red shades
/**
* This method will be used to Save new .dat for modified red shades.
* @author Kavya Barnwal
* @date 31/07/2019
*/
void saveRedFile(){
    FILE* save=fopen("SavedRed.dat","w");
    for(int i=0;i<953;i++ ){
        for(int j=0;j<1268;j++){
            char stri[4];
            sprintf(stri, "%d", red[i][j]);
            //printf("%s\n",stri);
            fprintf (save,stri);
            if(j!=1267)
            fprintf(save,",");
        }
        fprintf(save,"\n");
    }
    printf("\nSavedBlue.dat file has been saved\n");
    fclose(save);
}

//!Save new .dat for modified blue shades
/**
* This method will be used to Save new .dat for modified blue shades.
* @author Kavya Barnwal
* @date 31/07/2019
*/
void saveBlueFile(){
    FILE* save=fopen("SavedBlue.dat","w");
    for(int i=0;i<953;i++ ){
        for(int j=0;j<1268;j++){
            char stri[4];
            sprintf(stri, "%d", blue[i][j]);
            //printf("%s\n",stri);
            fprintf (save,stri);
            if(j!=1267)
            fprintf(save,",");
        }
        fprintf(save,"\n");
    }
    printf("\nSavedBlue.dat file has been saved\n");
    fclose(save);
}

//!Save new .dat for modified green shades
/**
* This method will be used to Save new .dat for modified green shades.
* @author Kavya Barnwal
* @date 31/07/2019
*/
void saveGreenFile(){
    FILE* save=fopen("SavedGreen.dat","w");
    for(int i=0;i<953;i++ ){
        for(int j=0;j<1268;j++){
            char stri[4];
            sprintf(stri, "%d", green[i][j]);
            //printf("%s\n",stri);
            fprintf (save,stri);
            if(j!=1267)
            fprintf(save,",");
        }
        fprintf(save,"\n");
    }
    printf("\nSavedBlue.dat file has been saved\n");
    fclose(save);
}


int main(){
  double time=0.0;
  clock_t starting=clock();

  readcolor("red");
  readcolor("green");
  readcolor("blue");

  removeGreen();
  saveGreenFile();
  saveRedFile();
  saveBlueFile();

  
  clock_t ending=clock();
  time+=(double)(ending-starting)/CLOCKS_PER_SEC;
  printf("\nTotal Execution time is : %f (sec)\n",time);
    
  return 0;
}