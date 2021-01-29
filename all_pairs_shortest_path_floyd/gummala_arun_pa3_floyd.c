#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>

int ** d;
int ** board;
int num;
int temp = 0;

int** createD(int);
int** createBoard(int);
int mini(int,int);

//void floyd(int,int);
void printBoard(int);
void printBoardP(int);

//finding the minimum of the two
int mini(int a,int b){
 if(a<b){
  return(a);
 }
 else{
  return(b);
 }
}

//creating the array for the D - Matrix
int ** createD(int num)
{
	int ** array = (int**)malloc(num*100*sizeof(int *));
	int i,j;
	for(i=1;i<=num;i++)
	{
		array[i] = malloc(num*100*sizeof(int));
	}
	for( i = 1; i <= num;i++)
  {
   	 	for( j = 1; j <= num; j++)
      if(i==j)
      {
         array[i][j] = 0; //Assigning the weight to each edge
      }

      else
      {
        int w = (rand() % (10)) + 1;

        array[i][j] = w; //Assigning the weight to each edge

        array[j][i] = array[i][j];
      }
	}
	return array;
}

//creating the array for the P - Matrix
int ** createBoard(int num)
{
	int ** parr = (int**)malloc(num*sizeof(int *));
  int i;
	for(i=1;i<=num;i++)
	{
		parr[i] = malloc(num*sizeof(int));
	}
	for( i = 1; i <= num;i++)
  {
   	 	for(int j = 1; j <= num; j++)
      {
        	parr[i][j]= 0;
			}
	}
	return parr;
}

//Print function for the D- Matrix
void printBoard(int num)
{
	for(int i = 1; i <= num;i++)
	{
		for(int j =1; j <= num; j++)
		{
      printf("%d\t",d[i][j]);
		}
		printf("\n");
	}
}

//Print function for the P - Matrix
void printBoardP(int num)
{
	for(int i = 1; i <= num;i++)
	{
		for(int j =1; j <= num; j++)
		{
      printf("%d\t",board[i][j]);
		}
		printf("\n");
	}
}

//Floyd's Algorithm
void floyd(int ** d, int ** board)
{
  for(int k=1;k<=num;k++)
  {
   for(int i=1;i<=num;i++)
   {
    for(int j=1;j<=num;j++)
     {
         if(i==j)
         {
           d[i][j]=0;
         }
         else
         {
           if(d[i][j] > d[i][k]+d[k][j])
           {
            board[i][j] = k;
           }

           d[i][j]=mini(d[i][j],d[i][k]+d[k][j]);

         }
       }
    }
   }
}

//Path Function
void path(int a, int b)
{
	if(board[a][b] == 0)
  {
    temp = temp + d[a][b];
		return;
	}
    path(a,board[a][b]);
    printf("V%d ",board[a][b]);
  	path(board[a][b],b);
}

int main()
{

  int i,j;

  //Using current time as a seed for random generator
  srand(time(0));

  //Generating a random number to take in as 'n' vertices
  num = (rand() % (6)) + 5;

  printf("Selected n value = %d \n\n", num);

	printf("\n");

  d = createD(num);

	board = createBoard(num);

  floyd(d, board);

  printf("D-Matrix after Floyd's Algorithm:\n\n");

  printBoard(num);  //Printing the D - Matrix

  printf("\n");

  printf("P-Matrix:\n\n");

  printBoardP(num);  //Printing the P - Matrix

  printf("\n");

  for(i = 1; i <= num;i++)
	{
    printf("V%d-Vj:shortest path and length\n\n",i);
		for(j =1; j <= num; j++)
		{
      printf("V%d ",i);
      path(i,j);
      if (board[i][j] == 0)
      {
        printf("V%d : %d\n",j,d[i][j]);
        temp = 0;
      }
      else
      {
        printf("V%d : %d\n",j,temp);
        temp =0;
      }
		}
		printf("\n");
	}

  free(d);
  free(board);

	return 0;
}
