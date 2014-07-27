/**
  * Problem description here
  */
#include <stdio.h>
#include "solution.h"

struct euler_state_s
{
    int some_thing;
    float some_thing_else;
    int array[100];
};

static
void
print_solution
    (euler_solution *p_solution)
{
    printf("no solution yet\n");
}

void
solve00004
    (euler_solution *p_solution)
{
    euler_state es = {0};
    p_solution->p_state = &es;
    p_solution->print_solution = print_solution;
}
