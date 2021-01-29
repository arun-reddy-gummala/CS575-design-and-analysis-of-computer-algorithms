#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
//Function to find the minimum value of two
int maxi(int a,int b){
 if(a>b){
  return(a);
 }
 else{
  return(b);
 } }
void lcs( char *X, char *Y, int m, int n ){
  int i,j;
   int C[m+1][n+1];
   //filling up the C - Matrix
   for (i=0; i<=m; i++){
     for (j=0; j<=n; j++){
       if (i == 0){
         C[0][j] = 0;
       }
       else if (j == 0){
         C[i][0] = 0;
       }
       else if (X[i-1] == Y[j-1]){
         C[i][j] = C[i-1][j-1] + 1;
       }
       else{
          C[i][j] = maxi(C[i-1][j], C[i][j-1]);
        }
     } }
   int k = C[m][n]; //consider the value of common variable in two strings
   // Create a character array to store the lcs string
   char lcs[k+1];
   lcs[k] = '\0'; // Set the terminating character
   // Start from the right-most-bottom-most corner and
   // one by one store characters in lcs[]
   int m1 = m;
   int n1 = n;
   while (m1 > 0 && n1 > 0){
      if (C[m1-1][n1] > C[m1][n1-1]){
          m1--;
      }
      else if (X[m1-1] == Y[n1-1]){
        lcs[k-1] = X[m1-1];
        m1--, n1--, k--;  // reduce values of i, j and index
      }
      else{
        n1--;
      }
   }
   printf("Length of LCS: %d\n",C[m][n] );
   printf("LCS : %s\n",lcs );
}

int main(int argc, char *argv[]){
  if(argc<2){
    return 0;
  }
  // declaring character array
  char X[strlen(argv[1])];
  char Y[strlen(argv[2])];
  // copying the contents of the
  // string to char array
  strcpy(X, argv[1]);
  strcpy(Y, argv[2]);
  //storing the lengths of X and Y strings
  int m = strlen(X);
  int n = strlen(Y);
  //calling the lcs function
  lcs(X,Y,m,n);

  return 0;
}
