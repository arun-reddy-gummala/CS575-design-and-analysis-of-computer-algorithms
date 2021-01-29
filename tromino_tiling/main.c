#include<stdio.h>
#include<stdlib.h>
#include <math.h>

int ** board;
int board_size;
int x_missing,y_missing;
int** createBoard(int,int,int);
void printBoard(int);
void tromino(int,int,int,int,int);
void putTromino(int,int,int,int,int,int,int);

int ** createBoard(int board_size,int x_missing,int y_missing)
{
	int ** array = (int**)malloc(board_size*sizeof(int *));
	int i,j;
	for(i=0;i<board_size;i++)
	{
		array[i] = (int*)malloc(board_size*sizeof(int));
	}
	for( i = board_size-1; i >= 0;i--)
  {
   	 	for( j = 0; j < board_size; j++)
      {
				if((j==x_missing) && (i==y_missing))
      	{
        	array[j][i]= -1;
      	}
				else
      	{
        	array[j][i] = 0;
      	}
			}
	}
	return array;
}

void tromino( int x_board, int y_board, int x_missing, int y_missing, int board_size )
{
	int i,j;
	if(board_size == 2)
	{
		int k;
    k = board_size/2;
    if(x_missing < x_board+k && y_missing < y_board+k)
    {
		putTromino(x_board,y_board+k,x_board+k,y_board,x_board+k,y_board+k,1);

    }
    else if(x_missing < x_board+k && y_missing >= y_board+k)
    {
		putTromino(x_board,y_board,x_board+k,y_board,x_board+k,y_board+k,2);

    }
    else if(x_missing >= x_board+k && y_missing < y_board+k)
    {
		putTromino(x_board,y_board,x_board,y_board+k,x_board+k,y_board+k,3);

    }
    else
    {
			putTromino(x_board,y_board,x_board+k,y_board,x_board,y_board+k,4);
    }
	}

 else
 {
	if(x_missing < x_board + board_size/2 && y_missing < y_board+ board_size/2)
	{
		int a=1;
		putTromino(x_board+(board_size/2)-1,y_board+ (board_size/2),x_board+board_size/2,y_board+board_size/2,x_board+board_size/2,y_board+(board_size/2)-1,a);
		tromino(x_board,y_board,x_missing, y_missing, board_size/2);
		tromino(x_board,y_board+board_size/2,x_board+(board_size/2)-1,y_board+board_size/2, board_size/2);
		tromino(x_board+board_size/2,y_board+board_size/2,x_board+board_size/2,y_board+board_size/2, board_size/2);
		tromino(x_board+board_size/2,y_board,x_board+board_size/2,y_board+(board_size/2)-1, board_size/2);
	}

	else if(x_missing>=x_board+ board_size/2 && y_missing < y_board + board_size/2)
	{
		int a=3;
		putTromino(x_board+board_size/2,y_board+ (board_size/2),x_board+(board_size/2)-1,y_board+board_size/2,x_board+(board_size/2)-1,y_board+(board_size/2)-1,a);
		tromino(x_board+board_size/2,y_board,x_missing,y_missing,board_size/2);
		tromino(x_board,y_board,x_board+(board_size/2)-1,y_board+(board_size/2)-1,board_size/2);
		tromino(x_board+board_size/2,y_board+board_size/2,x_board+board_size/2,y_board+board_size/2,board_size/2);
		tromino(x_board,y_board+board_size/2,x_board+(board_size/2)-1,y_board+board_size/2,board_size/2);
	}

	else if(x_missing < x_board + board_size/2 && y_missing >= y_board + board_size/2)
	{
		int a=2;
		putTromino(x_board+(board_size/2),y_board+ (board_size/2),x_board+(board_size/2),(y_board+board_size/2)-1,x_board+(board_size/2)-1,y_board+(board_size/2) -1,a);
		tromino(x_board,y_board+board_size/2,x_missing,y_missing,board_size/2);
		tromino(x_board+board_size/2,y_board+board_size/2,x_board+board_size/2,y_board+board_size/2, board_size/2);
		tromino(x_board,y_board,x_board+(board_size/2)-1,y_board+(board_size/2)-1, board_size/2);
		tromino(x_board+board_size/2,y_board,x_board+board_size/2,y_board+(board_size/2)-1,board_size/2);
	}
	//If missing Tile is in 4th quadrant
	else if(x_missing >= x_board + board_size/2 && y_missing >= y_board + board_size/2)
	{
		int a=4;
		putTromino(x_board+(board_size/2)-1, y_board+ (board_size/2),x_board+(board_size/2),y_board+(board_size/2) -1,x_board+(board_size/2)-1,y_board+(board_size/2)-1,a);
		tromino(x_board+board_size/2,y_board+board_size/2,x_missing,y_missing,board_size/2);
		tromino(x_board,y_board+board_size/2,x_board+board_size/2-1,y_board+board_size/2,board_size/2);
		tromino(x_board,y_board,x_board+(board_size/2)-1,y_board+(board_size/2)-1,board_size/2);
		tromino(x_board+board_size/2,y_board,x_board+board_size/2,y_board+(board_size/2)-1,board_size/2);
	}
 }
}

void putTromino(int x1,int y1,int x2,int y2,int x3, int y3,int z)
{
	board[x1][y1] = z;
	board[x2][y2] = z;
	board[x3][y3] = z;
}

void printBoard(int board_size)
{
	int i,j;
	for(i = board_size-1; i >= 0;i--)
	{
		for(j =0; j < board_size; j++)
		{
			if(board[j][i] == 1)
			{
				printf("UR\t");
			}
			else if(board[j][i] == 2)
			{
				printf("LR\t");
			}
			else if(board[j][i] == 3)
			{
				printf("UL\t");
			}
			else if(board[j][i] == 4)
			{
				printf("LL\t");
			}
			else if(board[j][i] == -1)
			{
				printf("MS\t");
			}
		}
		printf("\n");
	}
}

int main(int argc,char ** argv)
{
  int i,j;
  printf("Please enter board_size of board (0 to quit | need to be 2^n):");
  scanf("%d",&board_size);

	printf("\n");

  if (board_size == 0)
  {
    exit(0);
  }

  printf("Please enter coordinates of missing square (separate by a space):");
  scanf("%d %d",&x_missing,&y_missing);

	printf("\n");

	board = createBoard(board_size,x_missing,y_missing);
	tromino(0,0,x_missing, y_missing,board_size);

  printf("\n");
	printBoard(board_size);

	//return 0;
}
