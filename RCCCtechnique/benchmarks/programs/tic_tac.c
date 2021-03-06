#include<stdio.h>
#include<stdlib.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

void Board();
void PlayerX();
void PlayerO();
void Player_win();
void check();
int win,wrong_X,wrong_O,chk;

char name_X[30];
char name_O[30];
int pos_for_X[4][4];
int pos_for_O[4][4];
int pos_marked[4][4];
int row,col;




void Board()
{
	int i,j;
	//clrscr();
	printf("\n\t\t\t\tTIC TAC TOE BOARD");
	printf("\n\t\t\t\t*****************");
	printf("\n\n\n");
	printf("\n\t\t\t    1\t      2\t        3");
        for(i=1;i<=3;i++)
	{
		printf("\n \t\t\t _____________________________");
		printf("\n \t\t\t?\t  ?\t   ?\t     ?");
		printf("\n\t\t%d\t",i);
            for(j=1;j<=3;j++)
		{
              int a = pos_for_X[i][j];
			   int b = pos_for_O[i][j];
			if(a == 1)
			{
				printf("    X");
				printf("     ");
			}
			else if(b == 1)
			{
				printf("    O");
				printf("     ");
			}
			else
			{
				printf("          ");
				continue;
			}
		}
		printf("\n\t\t\t?\t  ?\t   ?\t     ?");
	}
	printf("\n\t\t\t------------------------------");
	Player_win();
}


void PlayerX()
{

	if(win == 1)
		return;
	int c = pos_marked[row][col];
	if(c==1 || row<1 || row>3 || col<1 || col>3)
	{
		printf("\nWRONG POSITION!! Press any key.....");
		wrong_X=1;
		Board();
	}
	else
	{
		pos_for_X[row][col]=1;
		pos_marked[row][col]=1;
		Board();
	}
}
void PlayerO()
{
	int row,col;
	if(win==1)
		return;

	int d = pos_marked[row][col];
	if(d == 1 || row<1 || row>3 || col<1 || col>3)
	{
		printf("\nWRONG POSITION!! Press any key....");
		wrong_O=1;
		Board();
	}
	else
	{
		pos_for_O[row][col]=1;
		pos_marked[row][col]=1;
		Board();
	}
}
void Player_win()
{
	int i;
        for(i=1;i<=3;i++)
	{
	    int e = pos_for_X[i][1];
 	    int f = pos_for_X[i][2];
	    int g = pos_for_X[i][3];
		if(e == 1 && f == 1 && g == 1)
		{
			win=1;
			printf("\n\nRESULT: %s wins!!",name_X);
			printf("\nPress any key............");
			return;
		}
	}
        for(i=1;i<=3;i++)
	{
	    int h = pos_for_X[1][i];
	    int ii = pos_for_X[2][i];
	    int j = pos_for_X[3][i];
		if(h == 1 && ii == 1 && j == 1)
		{
			win=1;
			printf("\n\nRESULT: %s wins!!",name_X);
			printf("\nPress any key............");
			return;
		}
	}
	int k = pos_for_X[1][1];
	int l = pos_for_X[2][2];
	int m = pos_for_X[3][3];
	int n = pos_for_X[1][3];
	int o = pos_for_X[2][2];
	int p = pos_for_X[3][1];
	if(k == 1 && l == 1 && m == 1)
	{
		win=1;
		printf("\n\nRESULTL: %s wins!!",name_X);
		printf("\nPress any key......");
		return;
	}
	else if(n == 1 && o == 1 && p ==1 )
	{
        	win=1;
		printf("\n\nRESULT: %s wins!!",name_X);
                printf("\nPress any key.....");
		return;
	}

        for(i=1;i<=3;i++)
	{
	    int q = pos_for_O[i][1];
	    int r = pos_for_O[i][2];
	    int s = pos_for_O[i][3];

		if(q == 1 && r == 1 && s == 1)
		{
			win=1;
			printf("\n\nRESULT: %s wins!!",name_O);
                        printf("\nPress any key.....");
			return;
		}
	}
        for(i=1;i<=3;i++)
	{
	    int t = pos_for_O[1][i];
	    int u = pos_for_O[2][i];
	    int v = pos_for_O[3][i];
		if(t == 1 && u == 1 && v == 1)
		{
			win=1;
			printf("\n\nRESULT: %s wins!!",name_O);
                        printf("\nPress any key.....");
			return;
		}
	}
	int w = pos_for_O[1][1];
	int x = pos_for_O[2][2];
	int y = pos_for_O[3][3];
	int z = pos_for_O[1][3];
	int z1 = pos_for_O[2][2];
	int z2 = pos_for_O[3][1];
	if(w == 1 && x == 1 && y == 1)
	{
		win=1;
		printf("\n\nRESULT: %s wins!!",name_O);
		printf("\nPress any key.....");
		return;
	}
	else if(z == 1 && z1 == 1 && z2 == 1)
	{
        	win=1;
		printf("\n\nRESULT: %s wins!!",name_O);
                printf("\nPress any key.....");
		return;
	}
}
void check()
{
	int i,j;
        for(i=1;i<=3;i++)
	{
            for(j=1;j<=3;j++)
		{
			if(pos_marked[i][j]==1)
				chk++;
			else
				continue;
		}
	}
}

int main()
{

	int i,j,ch;
	char ans;
klee_make_symbolic(&win, sizeof(int), "win");
klee_make_symbolic(&wrong_X, sizeof(int), "wrong_X");
klee_make_symbolic(&wrong_O, sizeof(int), "wrong_O");
klee_make_symbolic(&chk, sizeof(int), "chk");
klee_make_symbolic(&ch, sizeof(int), "ch");
klee_make_symbolic(&ans, sizeof(char), "ans");
klee_make_symbolic(&row, sizeof(int), "row");
klee_make_symbolic(&col, sizeof(int), "col");
	do
	{
		//clrscr();
		printf("\n\t\t\t\tTIC TAC TOE");
		printf("\n\t\t\t\t");
            for (i=1 ; i <= 11 ; i++)
		{
			//delay(10000);
			printf("*");
		}
		printf("\n1.Start The Game");
		printf("\n2.Quit The Game");

		//switch(ch)
		//{
			if (ch == 1)
            {
				chk=0;
				win=0;
                    for(i=1;i<=3;i++)
				{
                        for(j=1;j<=3;j++)
					{
						pos_for_X[i][j]=0;
						pos_for_O[i][j]=0;
						pos_marked[i][j]=0;
					}
				}
				printf("\n\n");


								Board();
                    for(;;)
				{
					if(win==1)
						break;
					check();
					if(chk==9)
					{
						printf("\n\t\t\tMATCH DRAWS!!");
						printf("\nPress any key....");
						break;
					}
					else
						chk=0;
					printf("\nTURN FOR %s:",name_X);
					PlayerX();
					do
					{
						if(wrong_X!=1)
							break;
						wrong_X=0;
						printf("\nTURN FOR %s:",name_X);
						PlayerX();
					}while(wrong_X == 1);
					check();
					if(chk == 9)
					{
						printf("\n\t\t\tMATCH DRAWS");
						printf("\nPress any key....");
						break;
					}
					else
						chk=0;
					printf("\nTURN FOR %s:",name_O);
					PlayerO();
					do
					{
						if(wrong_O!=1)
							break;
						wrong_O=0;
						printf("\nTURN FOR %s:",name_O);
						PlayerO();
					}while(wrong_O == 1);

					}
				Board();
				if(win!=1)
				{
					printf("\n\t\t\tMATCH DRAWS!!");
					printf("\nPress any key.......");
				}
            }
            else
           {
           		printf("\n\n\n\t\t\tThank You For Playing The Game.");
				printf("\n\t\t\t###############################");
			    exit(1);

		}

	}while(ans=='y' || ans=='Y');

	return 0;
}
