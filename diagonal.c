
// combination of Horizontal, Vertical, Left Diagonal and Right Diagonal scan of the input image and generate the output image. 

#include <string.h>
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

unsigned char buff[(1920*2560)];
unsigned int data[1920][2560];
unsigned int mat[1920][2560];
unsigned int data1[1920][2560];
unsigned int data2[1920][2560];
static int data3[3000][3000];
unsigned int M[1920][2560];
unsigned int M1[1920][2560];
unsigned int M2[1920][2560];
unsigned int M3[1920][2560];
unsigned int M4[1920][2560];
unsigned int N[1920][2560];
int h,w,comp;
int row=1920;
int col=2560;
void regiongrow(int,int,int);


void pgmRead(char *filesource)
{
    
	int i,j,g=0;
	FILE *fp1;
	char c;
	size_t n;
    fp1=fopen(filesource,"rb");
    if (!fgets(buff, sizeof(buff), fp1)) {
              perror(filesource);
              exit(1);
         }

//check for comments
     c = getc(fp1);
    while (c == '#') {
    while (getc(fp1) != '\n') ;
         c = getc(fp1);
    }

ungetc(c, fp1);
if (fscanf(fp1, "%d %d", &h, &w) != 2) {
         fprintf(stderr, "Invalid image size (error loading '%s')\n", filesource);
         exit(1);
    }

    if (fscanf(fp1, "%d", &comp) != 1) {
         fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filesource);
         exit(1);
    }

while (fgetc(fp1) != '\n') ;

 n = fread( buff, sizeof(buff[0]), sizeof(buff), fp1 );
fclose(fp1);

}
//End of pgmRead



void copy_in_2D(unsigned int a[1920][2560],unsigned char *buff)
{
  int i,j,g=0;
  for(i=0;i<1920;i++)
     { for(j=0;j<2560;j++)
        a[i][j]=buff[g++];
      }
}


void pgmWrite(int n, char * filedestination)
{
    FILE *fp2;
    int i,j,g=0,l,c;
    
for(i=0;i<1920;i++)
    for(j=0;j<2560;j++)
        buff[g++]=data[i][j];
    fp2 = fopen(filedestination, "wb");
    if (!fp2) {
         fprintf(stderr, "Unable to open file '%s'\n", filedestination);
         exit(1);
    }
    fprintf(fp2, "P5\n");

    //image size
    fprintf(fp2, "%d %d\n",h,w);

    // rgb component depth
    fprintf(fp2, "%d\n",comp);
    fwrite( buff, sizeof(buff[0]), sizeof(buff), fp2 );
    fclose(fp2);
}
//End of pgmWrite

// code SID


void copy_2D_to_2D( unsigned int a[1920][2560],unsigned int b[1920][2560])
{
        int i,j;
        for(i=0;i<1920;i++)
	{
		for(j=0;j<2560;j++)
		{
			a[i][j]=b[i][j];
                }
        }
     
}

void regiongrow(int i,int j,int l)
{

          data3[i][j]=l;
          if(i<1920-1)
	       if(data3[i+1][j]==255)
                   regiongrow(i+1,j,l);
          if(j<2560-1)
               if(data3[i][j+1]==255)
                   regiongrow(i,j+1,l);
	  if(i>0)
                if(data3[i-1][j]==255)
                   regiongrow(i-1,j,l);
	  if(j>0)
               if(data3[i][j-1]==255)
                   regiongrow(i,j-1,l);
	     
}      


int main(int argc,char *argv[])
{
int n,t,b,l,diff1,diff2,i,j;
char filesource1[100],filesource2[100],filedestination1[100],filedestination2[100];
FILE *fp1,*fp2, *fp7;
int rn,r,k,minr,x,y;
double min,dist;
fp7=fopen("diagonalQ4.txt","a");
strcpy(filesource1,argv[1]);

pgmRead(filesource1);
copy_in_2D(data,buff);

//Otsu thresholding

// Calculate histogram

int histData[256];
int threshold,a;

for(i=0;i<256;i++)
histData[i]=0;

for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			k=data[i][j];
                        histData[k]++;
                }
        }

// Total number of pixels
int total = row*col;

float sum = 0;
for ( a=0 ; a<256 ; a++)
 sum += a * histData[a];

float sumB = 0;
int wB = 0;
int wF = 0;

float varMax = 0;
threshold = 0;

for ( a=0 ; a<256 ; a++) {
   wB += histData[a];               // Weight Background
   if (wB == 0) continue;

   wF = total - wB;                 // Weight Foreground
   if (wF == 0) break;

   sumB += (float) (a * histData[a]);

   float mB = sumB / wB;            // Mean Background
   float mF = (sum - sumB) / wF;    // Mean Foreground

   // Calculate Between Class Variance
   float varBetween = (float)wB * (float)wF * (mB - mF) * (mB - mF);

   // Check if new maximum found
   if (varBetween > varMax) {
      varMax = varBetween;
      threshold = a;
   }
}
printf("threshold is %d \n",threshold);
for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			if (data[i][j]>threshold)
{
                           data[i][j]=255;
}
                         else 
                           data[i][j]=0;

                }
        }

//using  Region growing concept

int kk;
int a4;
int a5;
int a6;
int a7;
int a8;
int a9;
int a10;
int a11;
int a12;
int a13;
int a14;
int a15;

for(i=0;i<row;i++)
 {  
 for(j=0;j<col;j++)
   {
data3[i][j]=data[i][j];
    }
 }
int l1=256;
for(i=0;i<row;i++)
   for(j=0;j<col;j++)
   {
        if(data3[i][j]==255)
          {
            regiongrow(i,j,l1);
            l1=l1+1;
           }
         
    }
printf("level=%d\n",l1);
for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
                    N[i][j]=0;
                      }
                        }

for(l=256;l<l1;l++)
{

	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
                  M1[i][j]=0;
                  M2[i][j]=0;
                  M3[i][j]=0;
                  M4[i][j]=0;                  
                } 
         }

	for(i=0;i<row;i++)
	{
	   for(j=0;j<col;j++)
	   {
        	if(data3[i][j]==l)	
             	{
               		M1[i][j]=255;
               		M2[i][j]=255;
               		M3[i][j]=255;
               		M4[i][j]=255;  
            	}
       	   }
    	}  




// for horizantal


//Here no function for flag1 and flag2 variable
int xx;
int yy;
   int flag1;
   int flag2;
   for(i=0;i<row;i++)
       {
             flag1=0;
             for(j=0;j<col;j++)
             {
                   if(M1[i][j]==255)
                     
                {
                  a4=j;
		  flag1=1;
		  break;
                  }
             }
		flag2=0;
       
             for(j=col-1;j>0;j--)
             {
                      if(M1[i][j]==255)
                         
                     {
                       a5=j;
			flag2=1;
                       break;
                       }
              }

	      if(flag1==1 && flag2==1)
              for(j=a4;j<a5;j++)
              { 
                     M1[i][j]=255;
               } 
       } 
   
    
//for vertical


 for(j=0;j<col;j++)
       {
             flag1=0;
             for(i=0;i<row;i++)
             {
                   if(M2[i][j]==255)
                     
                 {
                  a6=i;
		  flag1=1;
		  break;
                  }
             }
		flag2=0;
           
             for(i=row-1;i>0;i--)
             {
                      if(M2[i][j]==255)
                         
                      {
                        a7=i;
			flag2=1;
                        break;
                       }
              }

	      if(flag1==1 && flag2==1)
   
               for(i=a6;i<a7;i++)
      
             
                   { 
                     M2[i][j]=255;
		     } 
     
       }

   //for diagonal
// Diagonal scan1

int x1, x2, y1, y2, l, m;
        flag1=0;
        for(i=0;i<row;i++)
         {
           for(j=0;j<col;j++)
            {
              if(M3[i][j]==255)
                 {
                   if(flag1==0)
                    {
                      x1=i;
                      flag1=1;
                    }
                   else
                   x2=i;
                }
            }
         }


 flag2=0;
     for(i=0;i<col;i++)
      {
        for(j=0;j<row;j++)
         {
              if(M3[j][i]==255)
                 {
                   if(flag2==0)
                    {
                      y1=i;
                      flag2=1;
                    }
                   else
                   y2=i;
                }
            }
         }


 i=x1;
        for(j=y1;j<=y2;j++)
         {
           int min_x=0;
           int min_y=0;
           int max_x=0;
           int max_y=0;
           flag1=0;
           for(l=i,m=j;l<=x2 && m<=y2;l++,m++)
           {
              if(M3[l][m]!=0)
               {
                 if(flag1==0)
                  {
                    flag1=1;
                    min_x=l;
                    max_x=l;
                    min_y=m;
                    max_y=m;
                  } //end of if
                 else
                  {
                    max_x=l;
                    max_y=m;
                  }//end of else
               } //end of outer if
            } //end of lth and mth loop
   //if any white pixel found
           if(flag1==1)
            {
              for(l=min_x,m=min_y;l<=max_x && m<=max_y;l++,m++)
              M3[l][m]=255;
            }//end of if
          }//end of jth loop
  
  
//Diagonal scan2

flag1=0;
        for(i=0;i<row;i++)
         {
           for(j=0;j<col;j++)
            {
              if(M4[i][j]==255)
                 {
                   if(flag1==0)
                    {
                      x1=i;
                      flag1=1;
                    }
                   else
                   x2=i;
                }
            }
         }

     flag2=0;
     for(i=0;i<col;i++)
      {
        for(j=0;j<row;j++)
         {
              if(M4[j][i]==255)
                 {
                   if(flag2==0)
                    {
                      y1=i;
                      flag2=1;
                    }
                   else
                   y2=i;
                }
            }
         }

 j=y1;
        for(i=x1;i<=x2;i++)
         {
           int min_x=0;
           int min_y=0;
           int max_x=0;
           int max_y=0;
           flag1=0;
           for(l=i,m=j;l>=x1 && m<=y2;l--,m++)
           {
              if(M4[l][m]!=0)
               {
                 if(flag1==0)
                  {
                    flag1=1;
                    min_x=l;
                    max_x=l;
                    min_y=m;
                    max_y=m;
                  } //end of if
                 else
                  {
                    max_x=l;
                    max_y=m;
                  }//end of else
               } //end of outer if
      
           } //end of lth and mth loop
   //if any white pixel found
           if(flag1==1)
            {
              for(l=min_x,m=min_y;l>=max_x && m<=max_y;l--,m++)
              M4[l][m]=255;
            }//end of if
          }//end of jth loop

  
for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
                      
			if(M1[i][j]==255 && M2[i][j]==255 && M3[i][j]==255 && M4[i][j]==255)

			N[i][j]=255;                         
			 
                }
        }    

//pgmWrite(n,argv[2]);
  
     
  }


for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
                      data[i][j]=N[i][j];
                      

                 }
         }
pgmWrite(n,argv[2]);
int count=0;
for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
		   if(N[i][j]==0)
                   
			count=count+1;
		}
	}
//fprintf(fp7,"no of black pixels of Q4 HVD1D2 are   %d \n",count);
int aa=row*col;
printf("total pixels are %d \n",aa);
 
for(i=0;i<1024;i++)
	{
		for(j=0;j<1280;j++)
		{
                      data[i][j]=N[i][j];
                      

                 }
         }
pgmWrite(n,argv[2]);
return 0;
}


