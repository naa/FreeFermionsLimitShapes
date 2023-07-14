#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <getopt.h>
#include <stdlib.h>
#include <assert.h>

#include <sys/types.h>
#include <unistd.h>

double nrand(mpf_t rop,gmp_randstate_t state)
{
  mpf_urandomb (rop,  state, 256);
  return mpf_get_d(rop);
}

#define min(a, b) (((a)<(b))?(a):(b))

int8_t (*make_zero_one_matrix(int n,int k,  double *xs, double *ys, int seed))[] {
  int8_t (*result)[k]=malloc(sizeof(int8_t[n][k]));
  int i,j;
  gmp_randstate_t state;
  mpf_t rop;
  
  gmp_randinit_mt(state);
  gmp_randseed_ui(state, seed);
  mpf_init2(rop,256);  
  for (j=0;j<k/2;j++) {
    for (i=0;i<n;i++) {
      result[i][2*j]=nrand(rop,state)<xs[i]*ys[j]/(1.0+xs[i]*ys[j])?0:1;
      result[i][2*j+1]=nrand(rop,state)<xs[i]/(xs[i]+ys[j])?0:1;      
    }
  }
  return result;
}

struct tworows {
  int *u;
  int *v;
  long len;
};

typedef struct tworows tworows_t;

struct word {
  int *v;
  long len;
};

typedef struct word word_t;

// This function takes n x k zero-one matrix and produces sequence of words
// to insert of length k/2
word_t* matrix_to_words(int n,int k,int8_t a[n][k]) {
  int i,j,l;
  long pos=0;

  struct word *result;
  result=malloc(sizeof(word_t)*(k/2));
  //  fprintf(stderr,"matrix to words\n");

  for (j=0;j<k/2;j++) {
    result[j].v=malloc(sizeof(int)*(2*n));
    result[j].len=0;
    for (i=n-1;i>=0;i--) {
      //      fprintf(stderr,"i=%d, j=%d\n",i,j);      
      if ((a[i][2*j]==0) && (a[i][2*j+1]==0)) {
	result[j].v[result[j].len]=(i+1);
	result[j].len++;
      } 
      else if ((a[i][2*j]==0) && (a[i][2*j+1]==1)) {}
      else if ((a[i][2*j]==1) && (a[i][2*j+1]==0)) {
	result[j].v[result[j].len]=-(i+1);
	result[j].len++;
	result[j].v[result[j].len]=(i+1);
	result[j].len++;	
      }
      else if ((a[i][2*j]==1) && (a[i][2*j+1]==1)) {
	result[j].v[result[j].len]=-(i+1);
	result[j].len++;
      }
    }
  }
  //  fprintf(stderr,"matrix to words done\n");  
  return result;
}

void free_2d_array(int size, int **table){
  int i;
  for (i = 0; i < size; i++) {
    free(table[i]);
  }
  free(table);
}

int less(int a, int b) {
  if (abs(a)<abs(b)) return 1;
  else if ((abs(a)==abs(b)) && (a>b)) return 1;
  return 0;
}

void insert_words(struct word *words, long n, long m, int32_t tableP[n][2*m], int32_t trtableQ[n][2*m] ) {
  int i,j,k,l,ii,jj;  

  int rowlenP[n];
  int collenQ[n];

  memset(rowlenP,0,sizeof rowlenP);
  memset(collenQ,0,sizeof collenQ);  
  int nrows=0;
  rowlenP[0]=0;

  int val,t;
  int addrow=0;
  
  for (k=0;k<m;k++) {
    for (l=0;l<words[k].len;l++) {
      val=words[k].v[l];
      
      addrow=1;
      for (i=0;i<nrows;i++) {
	// Here we just try to insert at the end of the row i
	if ((!less(val,tableP[i][rowlenP[i]-1])) /*&& (rowlen[i]<m)*/ && ((i==0) || (rowlenP[i]<rowlenP[i-1]))){
	  tableP[i][rowlenP[i]]=val;
	  rowlenP[i]++;
	  addrow=0;
	  break; // We are succesful, we have inserted val at the end of the row i
	}
	// Now we try to insert at the row i and column j
	for (j=rowlenP[i]-1;j>=0;j--) {
	  if (less(val,tableP[i][j]) && ((j==0) || (!less(val,tableP[i][j-1])))) {
	    t=val;
	    val=tableP[i][j];
	    tableP[i][j]=t;
	    break; // We have inserted at the position i,j, now we have new value to insert in the next rows
	  }
	}
	if (less(val,i+2)) { // We are trying to insert a value below allowed row
	  tableP[i][j]=INT_MAX; // We should put infty in the box and shift it to the boundary

	  addrow=0;
	  // This loop moves empty box to the boundary position
	  while (!((j==rowlenP[i]-1) && ((i==nrows-1) || (j>=rowlenP[i+1])))) {
	    if ((i<nrows-1) && ((j==rowlenP[i]-1) || ((j<rowlenP[i+1]) && ((tableP[i][j+1]==tableP[i+1][j]==INT_MAX)||(!less(tableP[i][j+1],tableP[i+1][j])))))) {
	      tableP[i][j]=tableP[i+1][j];
	      tableP[i+1][j]=INT_MAX;
	      i+=1;
	    } else {
	      tableP[i][j]=tableP[i][j+1];
	      tableP[i][j+1]=INT_MAX;
	      j+=1;
	    }
	  }
	  //We are now erasing the box from P and adding it to Q
	  //	  fprintf(stderr,"Erasing box from the row %d and adding it to the table Q at row %d at position ",i,n-1-i);
	  //	  fprintf(stderr,"%d\n", collenQ[n-1-i]);
	  break;
	}
      }
      if (addrow) {
	tableP[nrows][0]=val;
	//      rectable[nrows][0]=k;      
	rowlenP[nrows]=1;
	nrows++;
      }
    }
    for (i=0;i<n;i++) {
      if (rowlenP[i]+collenQ[n-1-i]<k+1) {
	trtableQ[n-1-i][collenQ[n-1-i]]=(k+1); // We are adding word number to the extra Q boxes
	collenQ[n-1-i]++;
      }
    }
    for (i=0;i<nrows;i++) {
      if (tableP[i][rowlenP[i]-1]==INT_MAX) {
	tableP[i][rowlenP[i]-1]=0;
	rowlenP[i]--; // We are removing \infty signs from P and adding \bar{word number} to Q
	trtableQ[n-1-i][collenQ[n-1-i]]=-(k+1);// We are adding \bar{word number}
	collenQ[n-1-i]++;	  
      }
    }
    if (nrows>0) {
      while ((rowlenP[nrows-1]==0) && (nrows>0)) {
	nrows--;
      }
    }    
  }
}

int main(int argc, char **argv)
{
  long k=1000;
  long n=20;
  long iter=100000;
  int opt;
  double q=1,t=1;
  int inpx=0,inpy=0,pyout=0,print_table=0;
  while ((opt = getopt(argc, argv, "n:k:q:t:xypP")) != -1) {
    switch (opt) {
    case 'k':
      k=atol(optarg);
      break;
    case 'n':
      n = atol(optarg);
      break;
    case 'q':
      q=atof(optarg);
      break;
    case 't':
      t=atof(optarg);
      break;
    case 'x':
      inpx=1;
      break;
    case 'y':
      inpy=1;
      break;
    case 'p':
      pyout=1;
      break;
    case 'P':
      print_table=1;
      break;            
      
    default: /* '?' */
      fprintf(stderr, "Usage: %s [-n rows] [-k columns] for C^{2nk}\n [-q first principal specialization parameter] [-t second principal specialization parameter] [-x read x parameters from stdout] [-y read y parameters from stdout] [-p python output] [-P print tableaux]\n",      
	      //      fprintf(stderr, "Usage: %s [-n rows] [-k columns] for C^{2nk}\n",
	      argv[0]);
      exit(EXIT_FAILURE);
    }
  }
  int rows[n];
  int columns[n];  
  int ncolumns=0;
  int nrows=0;
  int hook_length;
  long i,j;
  int newk;
  double xs[n],ys[k];
  for (i=0;i<n;i++) {
    if (inpx) {
      scanf("%lf",&(xs[i]));
    } else {
      xs[i]=pow(q,i);
    }
  }
  for (i=0;i<k;i++) {
    if (inpy) {
      scanf("%lf",&ys[i]);
    } else {
      ys[i]=pow(t,i);      
    }
  }
  int8_t (*tt)[n]=make_zero_one_matrix(n,2*k,xs,ys,time(0) ^ getpid());

  struct word* tr=matrix_to_words(n,2*k,tt);
  free(tt);

  int32_t tableP[n][2*k];
  int32_t trtableQ[n][2*k];
  memset(tableP, 0, sizeof(tableP));
  memset(trtableQ, 0, sizeof(trtableQ));  
  insert_words(tr,n,k,tableP, trtableQ);

  int rowlen[n];
  memset(rowlen, 0, sizeof(rowlen));  
  nrows=0;
  if (pyout) {printf("{");}
  if (print_table) {  
    if (pyout) {printf("'instable':[");}
    for (i=0;i<n;i++){
      if (pyout) {printf("[");}            
      for (j=0;(j<2*k) && (tableP[i][j]!=0);j++) {
	rowlen[i]++;
	printf("%d, ",tableP[i][j]);
      }
      nrows++;
      if (pyout) {printf("],"); }      
      printf("\n");
    }
    if (pyout) {printf("],"); }          
    printf("\n");
    if (pyout) {printf("'rectable':[");}          
    for (i=0;i<2*k;i++){
      if (pyout) {printf("[");}            
      for (j=0;((j<n) && (trtableQ[j][i]!=0));j++) {
	printf("%d, ",trtableQ[j][i]);
      }
      if (pyout) {printf("],");}            
      printf("\n");
    }
    if (pyout) { printf("],"); }
    printf("\n");  
  } else {
    for (i=0;i<n;i++){
      for (j=0;(j<2*k) && (tableP[i][j]!=0);j++) {
	rowlen[i]++;
      }
      nrows++;
    }
  }
  if (pyout) { printf("'diagram':[");  }    
  for (i=0;(i<nrows) && (rowlen[i]>0);i++){
    printf("%d, ",rowlen[i]);
  }
  if (pyout) {printf("]}");}
  printf("\n");

  for (j=0;j<k; j++)
    free(tr[j].v);
  free(tr);
  printf("\n");

  return 0;
}
