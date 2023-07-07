#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <getopt.h>
#include <stdlib.h>

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

  for (i=0;i<n;i++)
    for (j=0;j<k;j++)
      result[i][j]=nrand(rop,state)<1.0/(1.0+xs[i]*ys[j])?0:1;
  return result;
}

struct tworows {
  int *u;
  int *v;
  long len;
};

typedef struct tworows tworows_t;

tworows_t* matrix_to_tworows(int n,int k,int8_t a[n][k]) {
  long sum=0;
  int i,j,l;
  long pos=0;
  for (i=0;i<n;i++)
    for (j=0;j<k;j++)
      sum+=a[i][j];
  struct tworows *result;
  result=malloc(sizeof(tworows_t));
  (*result).u=malloc(sizeof(int[sum]));
  (*result).v=malloc(sizeof(int[sum]));  
  (*result).len=sum;
  for (i=0;i<n;i++) {
    for (j=0;j<k;j++) {
      for (l=0;l<a[i][j];l++) {
	(*result).u[pos]=i+1;
	(*result).v[pos]=j+1;
	pos++;
      }
    }
  }
  return result;
}

void rsk(struct tworows *tr, long n, long m, int32_t table[n][m], int32_t rectable[n][m]) {
  long i,j,k;  
  int *permutation=(*tr).v;
  int *column_numbers=(*tr).u;
  long permlen=(*tr).len;
  int rowlen[n];
  int nrows=1;
  rowlen[0]=1;

  int val,t;
  int addrow=0;
  table[0][0]=permutation[0];
  rectable[0][0]=column_numbers[0];
  
  for (k=1;k<permlen;k++) {
    val=permutation[k];
    addrow=1;
    for (i=0;i<nrows;i++) {
      if ((table[i][rowlen[i]-1]<val) && (rowlen[i]<m) && ((i==0) || (rowlen[i]<rowlen[i-1]))){
	table[i][rowlen[i]]=val;
	rectable[i][rowlen[i]]=column_numbers[k];		
	rowlen[i]++;
	addrow=0;
	break;
      }
      for (j=rowlen[i]-1;j>=0;j--) {
	if ((val<=table[i][j]) && ((j==0) || (val>table[i][j-1]))) {
	  t=val;
	  val=table[i][j];
	  table[i][j]=t;
	  break;
	}
      }
    }
    if (addrow) {
      table[nrows][0]=val;
      rectable[nrows][0]=column_numbers[k];      
      rowlen[nrows]=1;
      nrows++;
    }
  }
}

long double qpower(int i, int n, double q) {
  return powl(q,(double)i/n);
}

long double qcospower (int i, int n, double q) {
  return powl(q,cos(M_PI*i/n));
}

int main(int argc, char **argv)
{
  long k=500;
  long n=200;
  long iter=10000;
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
      fprintf(stderr, "Usage: %s [-n rows] [-k columns] [-q first principal specialization parameter] [-t second principal specialization parameter] [-x read x parameters from stdout] [-y read y parameters from stdout] [-p python output] [-P print tables]\n",
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
      xs[i]=q;
    }
  }
  for (i=0;i<k;i++) {
    if (inpy) {
      scanf("%lf",&ys[i]);
    } else {
      ys[i]=t;
    }
  }
  int8_t (*tt)[n]=make_zero_one_matrix(n,k,xs,ys,time(0) ^ getpid());
  
  tworows_t *tr=matrix_to_tworows(n,k,tt);
  free(tt);

  int32_t trtableP[n][k];
  int32_t tableQ[n][k];
  memset(trtableP, 0, sizeof(trtableP));
  memset(tableQ, 0, sizeof(tableQ));
  
  rsk(tr,n,k,trtableP,tableQ);
  free(tr);
  int rowlen[n];
  memset(rowlen, 0, sizeof(rowlen));  
  nrows=0;
  if (pyout) {printf("{");}
  if (print_table) {  
    if (pyout) {printf("'rectable':[");}
    for (i=0;i<n;i++){
      if (pyout) {printf("[");}            
      for (j=0;(j<k) && (tableQ[i][j]!=0);j++) {
	rowlen[i]++;
	printf("%d, ",tableQ[i][j]);
	fprintf(stderr,"%d, ",tableQ[i][j]);	
      }
      nrows++;
      if (pyout) {printf("],"); }      
      printf("\n");
      fprintf(stderr,"\n");            
    }
    if (pyout) {printf("],"); }          
    printf("\n");
    fprintf(stderr,"\n");          
    if (pyout) {printf("'instable':[");}          
    for (i=0;i<k;i++){
      if (pyout) {printf("[");}            
      for (j=0;((j<n) && (trtableP[j][i]!=0));j++) {
	printf("%d, ",trtableP[j][i]);
	fprintf(stderr,"%d, ",trtableP[j][i]);	
      }
      if (pyout) {printf("],");}            
      printf("\n");
      fprintf(stderr,"\n");      
    }
    if (pyout) { printf("],"); }
    printf("\n");  
  } else {
    for (i=0;i<n;i++){
      for (j=0;(j<k) && (tableQ[i][j]!=0);j++) {
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
  fprintf(stderr,"\n");          

  printf("\n");
  
  fclose(stderr);
  return 0;
}
