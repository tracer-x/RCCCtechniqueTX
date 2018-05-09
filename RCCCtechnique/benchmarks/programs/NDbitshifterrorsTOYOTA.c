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

/*
 * Types of defects: BitShift errors
 * Complexity: int	Beyond the size of the left shift	Constant
 */
void bit_shift_001 ()
{
	int a = 1;
	int ret;
	ret = a << 10;/*Tool should  Not detect this line as error*/ /*NO ERROR:Bit shift error*/
        sink = ret;
}

/*
 * Types of defects: BitShift errors
 * Complexity: a long	Beyond the size of the left shift	Constant
 */
void bit_shift_002 ()
{
	long a = 1;
	long ret;
	ret = a << 10; /*Tool should  Not detect this line as error*/ /*NO ERROR:Bit shift error*/
        sink = ret;
}

/*
 * Types of defects: BitShift errors
 * Complexity: unsigned int	Beyond the size of the left shift	Constant
 */
void bit_shift_003 ()
{
	unsigned int a = 1;
	unsigned int ret;
	ret = a << 10; /*Tool should  Not detect this line as error*/ /*NO ERROR:Bit shift error*/
        sink = ret;
}

/*
 * Types of defects: BitShift errors
 * Complexity: unsigned long	Beyond the size of the left shift	Constant
 */
void bit_shift_004 ()
{
	unsigned long a = 1;
	unsigned long ret;
	ret = a << 10; /*Tool should  Not detect this line as error*/ /*NO ERROR:Bit shift error*/
        sink = ret;
}

/*
 * Types of defects: BitShift errors
 * Complexity: int	Shift left on negative values	Constant
 */
void bit_shift_005 ()
{
	int a = 1;
	int ret;
	ret = a << 10;/*Tool should  Not detect this line as error*/ /*NO ERROR:Bit shift error*/
        sink = ret;
}

/*
 * Types of defects: BitShift errors
 * Complexity: int	Beyond the size of the right shift	Constant
 */
void bit_shift_006 ()
{
	int a = 1;
	int ret;
	ret = a >> 10;/*Tool should  Not detect this line as error*/ /*NO ERROR:Bit shift error*/
        sink = ret;
}

/*
 * Types of defects: BitShift errors
 * Complexity: int	Right shifting negative values with	Constant
 */
void bit_shift_007 ()
{
	int a = 1;
	int ret;
	ret = a >> 10;/*Tool should  Not detect this line as error*/ /*NO ERROR:Bit shift error*/
        sink = ret;
}

/*
 * Types of defects: BitShift errors
 * Complexity: int	Beyond the size of the left shift	Variable
 */
void bit_shift_008 ()
{
	int a = 1;
	int shift = 10;
	int ret;
	ret = a << shift;/*Tool should  Not detect this line as error*/ /*NO ERROR:Bit shift error*/
        sink = ret;
}

/*
 * Types of defects: BitShift errors
 * Complexity: int	Beyond the size of the left shift	Value of random variable
 */
void bit_shift_009 ()
{
	int a = 1;
	int shift;
	int ret;
	shift = rand() % 32;
	ret = a << shift;/*Tool should  Not detect this line as error*/ /*NO ERROR:Bit shift error*/
        sink = ret;
}

/*
 * Types of defects: BitShift errors
 * Complexity: int	Beyond the size of the left shift	Linear equation
 */
void bit_shift_010 ()
{
	int a = 1;
	int shift = 2;
	int ret;
	ret = a << ((5 * shift) + 1);/*Tool should  Not detect this line as error*/ /*NO ERROR:Bit shift error*/
        sink = ret;
}

/*
 * Types of defects: BitShift errors
 * Complexity: int	Beyond the size of the left shift	Nonlinear equation
 */
void bit_shift_011 ()
{
	int a = 1;
	int shift = 2;
	int ret;
	ret = a << ((shift * shift) + 6);/*Tool should  Not detect this line as error*/ /*NO ERROR:Bit shift error*/
        sink = ret;
}

/*
 * Types of defects: BitShift errors
 * Complexity: int	Beyond the size of the left shift	The return value of the function
 */
int bit_shift_012_func_001 ()
{
	return 10;
}

void bit_shift_012 ()
{
	int a = 1;
	int ret;
	ret = a << bit_shift_012_func_001();/*Tool should  Not detect this line as error*/ /*NO ERROR:Bit shift error*/
        sink = ret;
}

/*
 * Types of defects: BitShift errors
 * Complexity: int	Beyond the size of the left shift	Function arguments
 */
void bit_shift_013_func_001 (int shift)
{
	int a = 1;
	int ret;
	ret = a << shift;/*Tool should  Not detect this line as error*/ /*NO ERROR:Bit shift error*/
        sink = ret;
}

void bit_shift_013 ()
{
	bit_shift_013_func_001(10);
}

/*
 * Types of defects: BitShift errors
 * Complexity: int	Beyond the size of the left shift	An array of element values
 */
void bit_shift_014 ()
{
	int a = 1;
	int shifts[5] = {8, 40, 32, 16, 24};
	int ret;
	ret = a << shifts[3];/*Tool should  Not detect this line as error*/ /*NO ERROR:Bit shift error*/
        sink = ret;
}

/*
 * Types of defects: BitShift errors
 * Complexity: int	Beyond the size of the left shift	Alias for 1 weight
 */
void bit_shift_015 ()
{
	int a = 1;
	int shift = 10;
	int shift1;
	int ret;
	shift1 = shift;
	ret = a << shift1;/*Tool should  Not detect this line as error*/ /*NO ERROR:Bit shift error*/
        sink = ret;
}

/*
 * Types of defects: BitShift errors
 * Complexity: int	Beyond the size of the left shift	Also known as double alias
 */
void bit_shift_016 ()
{
	int a = 1;
	int shift = 10;
	int shift1;
	int shift2;
	int ret;
	shift1 = shift;
	shift2 = shift1;
	ret = a << shift2;/*Tool should  Not detect this line as error*/ /*NO ERROR:Bit shift error*/
        sink = ret;
}

/*
 * Types of defects: BitShift errors
 * Complexity: the operands is a constant
 */
void bit_shift_017 ()
{
	int ret;
	ret = 1 << 10;/*Tool should  Not detect this line as error*/ /*NO ERROR:Bit shift error*/
        sink = ret;
}

int main()
{
	klee_make_symbolic(&vflag_copy, sizeof(int), "vflag_copy");
        klee_make_symbolic(&vflag_file, sizeof(int), "vflag_file");
        klee_make_symbolic(&vflag, sizeof(int), "vflag");


	/* BitShift errors */
        if((vflag_file == 1) || (vflag_file == 888)) 
        {
		
        if ((vflag == 1) || (vflag == 888))
	{
		bit_shift_001();
	}

	if (vflag == 2 || vflag == 888)
	{
		bit_shift_002();
	}

	if (vflag == 3 || vflag == 888)
	{
		bit_shift_003();
	}

	if (vflag == 4 || vflag == 888)
	{
		bit_shift_004();
	}

	if (vflag == 5 || vflag == 888)
	{
		bit_shift_005();
	}

	if (vflag == 6 || vflag == 888)
	{
		bit_shift_006();
	}

	if (vflag == 7 || vflag == 888)
	{
		bit_shift_007();
	}

	if (vflag == 8 || vflag == 888)
	{
		bit_shift_008();
	}

	if (vflag == 9 || vflag == 888)
	{
		bit_shift_009();
	}

	if (vflag == 10 || vflag == 888)
	{
		bit_shift_010();
	}

	if (vflag == 11 || vflag == 888)
	{
		bit_shift_011();
	}

	if (vflag == 12 || vflag == 888)
	{
		bit_shift_012();
	}

	if (vflag == 13 || vflag == 888)
	{
		bit_shift_013();
	}

	if (vflag == 14 || vflag == 888)
	{
		bit_shift_014();
	}

	if (vflag == 15 || vflag == 888)
	{
		bit_shift_015();
	}

	if (vflag == 16 || vflag == 888)
	{
		bit_shift_016();
	}

	if (vflag == 17 || vflag == 888)
	{
		bit_shift_017();
	}
}

	   
return 0;
}

