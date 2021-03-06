
#include<stdio.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif


#include <stdlib.h>

int *a, *b;
int n;



void foo()
{
  int i;
  for (i = 0; i < n; i++)
    a[i] = n;
  for (i = 0; i < n - 1; i++)
    b[i] = n;
}

int main()
{
  n = 1;
  int a1;
  klee_make_symbolic(&a1, sizeof(int), "a1");
  while(a1 && (n < 3)) {
    n++;
  }

  a = malloc(n * sizeof(*a));
  b = malloc(n * sizeof(*b));

  *b++ = 0;
  foo();

  if (b[-2]) /* invalid deref */
  { 
  free(a); 
  free(b-1); 
  }
  else
  { 
  free(a); 
  free(b-1); 
  }

  return 0;
}
