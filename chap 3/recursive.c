
#include "recursive.h"


// Calculate factorial of an integer n (recursive)
int fact(int n)
{
    if (n < 0)
    {
        return 0;
    }

    if (n == 1 || n == 0)
    {
        return 1;
    }

    return n*fact(n - 1);
}


// Calculate factorial of an integer n (tail recursive)
int fact_tail(int n, int prod)
{
    if (n < 0)
    {
        return 0;
    }

    if (n == 1 || n == 0)
    {
        return 1;
    }

    return fact_tail(n - 1, prod*n);
}