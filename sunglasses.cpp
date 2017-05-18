#include<bits/stdc++.h>
#include <stdlib.h>
//#include "PGM.h"
using namespace std;

#define MAXLENGTH 1000
#define MAXCOLS 130
#define MAXROWS 130
#define Max 100000





/* INPUT: a filename (char*),row and column dimension variables (long), and
 *   a pointer to a 2D array of unsigned char's of size MAXROWS x MAXCOLS
 *   (row major).
 * OUTPUT: an integer is returned indicating whether or not the
 *   file was read into memory (in row major order).  1 is returned if the
 *   file is read correctly, 0 if it is not.  If there are
 *   too few pixels, the function still returns 1, but returns an error
 *   message.  Error messages are also returned if a file cannot be open,
 *   or if the specifications of the file are invalid.
 * NOTE: The case where too many pixels are in a file is not detected.
 */
int pgmRead (char *fileName,long *rows,long *cols,
	     unsigned char image[130][130])
{
      FILE *filePointer;    /* for file buffer */
      char line[1000]; /* for character input from file */
      int maximumValue = 0; /* max value from header */
      int binary;           /* flag to indicate if file is binary (P5)*/
      long numberRead = 0;  /* counter for number of pixels read */
      long i,j;             /* (i,j) for loops */
      int test,temp;        /* for detecting EOF(test) and temp storage */
       char c;
      /* Open the file, return an error if necessary. */
      if ((filePointer = fopen(fileName,"rb")) == NULL) {
	//   printf ("ERROR: cannot open file\n\n");
	   fclose (filePointer);
	   return (0);
      }

      /* Initialize columnsidth, and height */
      *cols = *rows =0;

      /* Check the file signature ("Magic Numbers" P2 and P5); skip comments
       * and blank lines (CR with no spaces before it).*/
      fgets (line,MAXLENGTH,filePointer);
      while (line[0]=='#' || line[0]=='\n') fgets (line,MAXLENGTH,filePointer);
      if (line[0]=='P' && (line[1]=='2')) {
	   binary = 0;
	 /*   printf ("\nFile Format: P2\n"); */
      }
      else if (line[0]=='P' && (line[1]=='5')) {
	   binary = 1;
	  /*  printf ("\nFORMAT: P5\n"); */
      }
      else {
	  // printf ("ERROR: incorrect file format\n\n");
	   fclose (filePointer);
	   return (0);
      }

      /* Input the width, height and maximum value, skip comments and blank
       * lines. */
      fgets (line,MAXLENGTH,filePointer);
      while (line[0]=='#' || line[0]=='\n') fgets (line,MAXLENGTH,filePointer);
      sscanf (line,"%ld %ld",cols,rows);

      fgets (line,MAXLENGTH,filePointer);
      while (line[0]=='#' || line[0]=='\n') fgets(line,MAXLENGTH,filePointer);
      sscanf (line,"%d",&maximumValue);

      /* display specifications and return an error if h,w, or
      *  maximum value is illegal.*/
   /*    printf("Rows: %ld   Columns: %ld\n",*rows,*cols); */
/*       printf("Maximum value: %d\n\n",maximumValue); */

      if ((*cols)<1 ||(*rows)<1 || maximumValue<0 || maximumValue>Max){
	   printf ("ERROR: invalid file specifications (cols/rows/max value)\n\n");
	   fclose (filePointer);
	   return (0);
      }
      else if ((*cols) > MAXCOLS || (*rows) > MAXROWS) {
	   printf ("ERROR: increase MAXROWS/MAXCOLS in PGM.h");
	   fclose (filePointer);
	   return (0);
      }
      /* Read in the data for binary (P5) or ascii (P2) PGM formats   */
      if (binary) {

	   for (i = 0; i < (*rows); i++) {
	        numberRead += fread((void *)&(image[i][0]),
		  sizeof(unsigned char),(*cols),filePointer);
		if (feof(filePointer)) break;
	   }

        /*
        for (i= 0; i < (*rows); i++) {
	        for (j =0; j < (*cols); j++) {
	             test = fscanf (filePointer,"%c",&temp);
		     if (test == EOF) break;
		     image[i][j] = (int)test;

		     numberRead++;
		}
		if (test == EOF) break;
	   }

        */

      }
      else {
	   for (i= 0; i < (*rows); i++) {
	        for (j =0; j < (*cols); j++) {
	             test = fscanf (filePointer,"%d",&temp);
		     if (test == EOF) break;
		     image[i][j] = (unsigned char)temp;

		     numberRead++;
		}
		if (test == EOF) break;
	   }
      }

   /*    printf ("  Rows * Columns = %ld\n",(*rows)*(*cols)); */
/*       printf ("  Number of pixels read = %ld\n\n",numberRead); */

      /* Insure the number of pixels read is at least the
       *   number indicated by w*h.
       * If not, return an error message, but proceed */
      if (numberRead < ((*rows)*(*cols))) {
	   printf ("ERROR: fewer pixels than rows*cols indicates\n\n");
      }

      /* close the file and return 1 indicating success */
      fclose (filePointer);
      return (1);
}

long double o[2],in[961],h[3];
long double ih[961][3],ho[3][2];
long double eih[961][3]={0},eho[3][2]={0};
long double t[2],delta[2];
long double momen=0.3;








int main()
{
FILE * fp=fopen("list/straightrnd_train.list","r");

int num=0;
char str[1000][200];
while(1)
{
    char c=fgetc(fp);
    if(feof(fp))
        break;
    fgets(str[num],10000,fp);
    if(feof(fp))
        break;
    num++;
}
num++;

long double error=100;
int iter=1000;//
int b=0;



srand(time(NULL));

int i,j;
for(i=0;i<961;i++)
{
    for(j=0;j<3;j++)
        ih[i][j]=(rand()%1001-500)/(long double)1000;
}
for(i=0;i<3;i++)
{
    for(j=0;j<2;j++)
        ho[i][j]=(rand()%1001-500)/(long double)1000;
}
cout<<"ho[0][0] "<<ho[0][0]<<endl;


while(error>0.1&&iter>0)
{
error=0;
for(b=0;b<num;b++)
{
       char st[200];
    strcpy(st,str[b]);
    int len=strlen(st);
    st[len-1]='\0';
  //  cout<<st;
//FILE * fp=fopen(st,"r");
unsigned char s[130][130];
long arr[130][130],i,j;
//if(fp==NULL);
  //  cout<<"null"<<endl;

//calculate value of t array//

if(st[len-8]=='s')
    {
        t[0]=1;
        t[1]=0;
    }
else
    {
        t[0]=0;
        t[1]=1;
    }

i=30;
j=32;
pgmRead(st,&i,&j,s);
//cout<<"i is "<<i<<endl;
//cout<<"j is "<<j<<endl;
int i1,j1;
int k=1;
in[0]=1;
for(i1=0;i1<i;i1++)
{
    for(j1=0;j1<j;j1++)
    {
        in[k++]=(long double)s[i1][j1];
    }
}



for(i=1;i<k;i++)
    in[i]=in[i]/(long double)255;
//for(i=0;i<10;i++)
 //   cout<<in[i]<<" ";
//cout<<endl;
    h[0]=1;
   for(i=1;i<3;i++)
   {
       long double sum=0;
       for(j=0;j<961;j++)
       {
           sum+=in[j]*ih[j][i];

       }
//       cout<<"ih[5][i] is "<<ih[5][i]<<" ";
//         cout<<sum<<endl;
       h[i]=1/(long double)(1+exp((-1)*sum));
        //cout<<"exp((-1)*sum) is "<<exp((-1)*sum)<<endl;
   }
   for(i=0;i<2;i++)
   {
       long double sum=0;
       for(j=0;j<3;j++)
       {
           sum+=h[j]*ho[j][i];
       }
       o[i]=1/(long double)(1+exp((-1)*sum));
       delta[i]=o[i]*(1-o[i])*(t[i]-o[i]);
   }

   long double sum=0;
   for(i=0;i<2;i++)
    sum+=(t[i]-o[i])*(t[i]-o[i]);
   error+=sum/2;
   for(i=0;i<3;i++)
   {
       for(j=0;j<2;j++)
       {

         ho[i][j]+=momen*h[i]*(t[j]-o[j])*o[j]*(1-o[j]);//-momen*eho[i][j];
        //eho[i][j]=momen*h[i]*(t[j]-o[j])*o[j]*(1-o[j])-momen*eho[i][j];
       }
   }

   for(i=0;i<961;i++)
   {

       for(j=0;j<3;j++)
       {
          long double sum=0;
          for(k=0;k<2;k++)
          {
              sum+=delta[k]*ho[j][k];
          }
        ih[i][j]+=momen*h[j]*(1-h[j])*sum*in[i];//-momen*eih[i][j];
        //eih[i][j]=momen*h[j]*(1-h[j])*sum*in[i]-momen*eih[i][j];
       }
   }
}
    iter--;
}
cout<<"error : "<<error<<endl;
cout<<"done"<<endl;
fclose(fp);


FILE * fj=fopen("list/straightrnd_test1.list","r");
if(fj==NULL)
{
    cout<<"null"<<endl;
    return 0;
}
num=0;
char test[1000][200];
while(1)
{
    char c=fgetc(fj);
    if(feof(fj))
        break;
    fgets(test[num],1000,fj);
    if(feof(fj))
        break;
    num++;
}
num++;
//cout<<test[0]<<endl;
//cout<<num<<endl;



fclose(fj);


int corr=0;
for(b=0;b<num;b++)
{
        char st[200];
    strcpy(st,test[b]);
    int len=strlen(st);
    st[len-1]='\0';
  //  cout<<st;
//FILE * fp=fopen(st,"r");
unsigned char s[130][130];
long arr[130][130],i,j;
//if(fp==NULL);
  //  cout<<"null"<<endl;

//calculate value of t array//

if(st[len-8]=='s')
    {
        t[0]=1;
        t[1]=0;
    }
else
    {
        t[0]=0;
        t[1]=1;
    }

i=30;
j=32;
pgmRead(st,&i,&j,s);
//cout<<"i is "<<i<<endl;
//cout<<"j is "<<j<<endl;
int i1,j1;
int k=1;
in[0]=1;
for(i1=0;i1<i;i1++)
{
    for(j1=0;j1<j;j1++)
    {
        in[k++]=(long double)s[i1][j1];
    }
}


for(i=1;i<k;i++)
    in[i]=in[i]/(double)255;
for(i=0;i<10;i++)
    cout<<in[i]<<" ";
cout<<endl;
h[0]=1;
   for(i=1;i<3;i++)
   {
       long double sum=0;
       for(j=0;j<961;j++)
       {
           sum+=in[j]*ih[j][i];
       }
       h[i]=1/(long double)(1+exp((-1)*sum));
       cout<<"h[i] is "<<h[i]<<" ";

   }

   for(i=0;i<2;i++)
   {
       long double sum=0;
       for(j=0;j<3;j++)
       {
           sum+=h[j]*ho[j][i];
       }
       o[i]=1/(long double)(1+exp((-1)*sum));
       //delta[i]=o[i]*(1-o[i]);
   }
   //cout<<st<<endl;
   cout<<"t0 and t1 "<<t[0]<<" "<<t[1]<<endl;
   cout<<"o0 and o1 "<<o[0]<<" "<<o[1]<<endl;
  //  if(t[0]>t[1]&&o[0]>o[1])
    //    corr++;
  //  if(t[0]<=t[1]&&o[0]<=o[1])
    //    corr++;

    if(o[0]>0.5&&t[0]==1)
        corr++;
    if(o[0]<0.5&&t[0]==0)
        corr++;

}
//cout<<corr<<endl<<num<<endl;
cout<<"Accuracy is ";
cout<<corr/(long double)35<<endl;


}
