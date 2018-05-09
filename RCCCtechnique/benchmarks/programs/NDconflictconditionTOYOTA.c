#include<stdio.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

# define PRINT_DEBUG 1

int vflag;

int vflag_copy;
int vflag_file;
int idx, sink;
double dsink;
void *psink;

int rand (void);

void conflicting_cond_001 ()
{
	int a;
	int b = 0;
	int ret;

	a = rand();
	if ((a == 0) || (a == 1)) /*Tool should Not detect this line as error*/ /*No ERROR:contradict condition*/
	{
		b += a;
	}
	ret = b;
        sink = ret;
}


void conflicting_cond_002 ()
{
	int a;
	int b = 0;
	int ret;

	a = rand();
	if (!((a < 5) || (10 < a))) /*Tool should Not detect this line as error*/ /*No ERROR:contradict condition*/
	{
		b += a;
	}
	ret = b;
        sink = ret;
}


void conflicting_cond_003 ()
{
	int a;
	int b = 0;
	int ret;

	a = rand();
	if (((0 < a) && (a < 2)) || ((8 < a) && (a < 10)))/*Tool should Not detect this line as error*/ /*No ERROR:contradict condition*/
	{
		b += a;
	}
	ret = b;
        sink = ret;
}


void conflicting_cond_004 ()
{
	int a;
	int b = 0;
	int ret;

	a = rand();
	if (a < 5)
	{
		a += 10;
		if (10 < a)/*Tool should Not detect this line as error*/ /*No ERROR:contradict condition*/
		{
			b += a;
		}
	}
	ret = b;
        sink = ret;
}

void conflicting_cond_005 ()
{
	int a;
	int b;
	int ret;

	a = rand();
	if ((a == 0) || (a == 1))
        {
        b = 0;
        }
        else
        {
        b = 1;
        }
        ret = b;
        sink = ret;
}

void conflicting_cond_006 ()
{
	int a=0;
	int b = 0;
	int ret;

	while ((a == 0) || (a == 1))
        {
         b += a;
         a++;
        }
	ret = b;
        sink = ret;
}


void conflicting_cond_007 ()
{
	int a;
	int b = 0;
	int ret;

	a = rand();
	while ((a == 0) || (a == 1))/*Tool should Not detect this line as error*/ /*No ERROR:contradict condition*/
	{
		b += a;
		a ++;
	}
	ret = b;
        sink = ret;
}


void conflicting_cond_008 ()
{
	int a;
	int b = 0;
	int ret;

	a = rand();
	while (!((a < 5) || (10 < a)))/*Tool should Not detect this line as error*/ /*No ERROR:contradict condition*/
	{
		b += a;
		a ++;
	}
	ret = b;
        sink = ret;
}

void conflicting_cond_009 ()
{
	int a;
	int b = 0;
	int ret;

	a = rand();
	while (((0 < a) && (a < 2)) || ((8 < a) && (a < 10)))/*Tool should Not detect this line as error*/ /*No ERROR:contradict condition*/
	{
		b += a;
		a ++;
	}
	ret = b;
        sink = ret;
}


void conflicting_cond_010 ()
{
	int a;
	int ret;
        a = rand();
	while ((a == 0) || (a == 1))
	{
		a = rand();
	}
	/*Tool should Not detect this line as error*/ /*No ERROR:contradict condition*/
	ret = a;
        sink = ret;
}

int main()
{
        
        klee_make_symbolic(&vflag_copy, sizeof(int), "vflag_copy");
        klee_make_symbolic(&vflag_file, sizeof(int), "vflag_file");
        klee_make_symbolic(&vflag, sizeof(int), "vflag");
        



/* Conflicting Condition */
	if (vflag_file ==5 || vflag_file == 888 )
	{
		if (vflag ==1 || vflag ==888)
	{
		conflicting_cond_001();
	}

	if (vflag ==2 || vflag ==888)
	{
		conflicting_cond_002();
	}

	if (vflag ==3 || vflag ==888)
	{
		conflicting_cond_003();
	}

	if (vflag ==4 || vflag ==888)
	{
		conflicting_cond_004();
	}

	if (vflag ==5 || vflag ==888)
	{
		conflicting_cond_005();
	}

	if (vflag ==6 || vflag ==888)
	{
		conflicting_cond_006();
	}

	if (vflag ==7 || vflag ==888)
	{
		conflicting_cond_007();
	}

	if (vflag ==8 || vflag ==888)
	{
		conflicting_cond_008();
	}

	if (vflag ==9 || vflag ==888)
	{
		conflicting_cond_009();
	}

	if (vflag ==10 || vflag ==888)
	{
		conflicting_cond_010();
	}
	}
	   
return 0;
}

