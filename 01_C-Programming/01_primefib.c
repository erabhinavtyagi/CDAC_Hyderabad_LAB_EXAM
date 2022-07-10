// Prime Fibonacci numbers in given range using Recursion.

#include<stdio.h>

int fib (int);

int
main ()
{
  int n, i, j, p, m = 0;
  printf ("Enter the Number greater than zero: ");
  scanf ("%d", &n);
// Fibonacci series upto n
  printf ("Prime number in Fibonacci Series upto %d terms: ", n);
  for (i = 1; i <= n; i++)
    {
      p = fib (m);
//      printf("Fibonacci Series for %d terms: %d \n",n,p);
      for (j = 2; j <= p; j++)
	{
	  if (p % j == 0)
	    break;
	}
      {
	if (p == j)
	  printf ("%d\t", p);
      }
      m++;
    }
  printf ("\n");
}

int
fib (int x)
{
  if (x == 0 || x == 1)
    return x;
  else
    return (fib (x - 1) + fib (x - 2));
}
