#ifndef RECURSIVE_H
#define RECURSIVE_H

int fact(int n);
int fact_tail(int n, int prod);

#define FACTORIAL(n) fact_tail(n, 1)

#endif