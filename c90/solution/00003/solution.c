/**
  * Problem description here
  */
#include <stdio.h>
#include "solution.h"

static
void
print_solution
    (euler_solution *p_solution)
{
    printf("no solution yet\n");
}

void
solve00003
    (euler_solution *p_solution)
{
    p_solution->print_solution = print_solution;
}
