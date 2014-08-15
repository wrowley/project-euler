/**
  * Multiples of 3 and 5
  * Problem 1
  * Published on 05 October 2001 at 06:00 pm [Server Time]
  * If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
  *
  * Find the sum of all the multiples of 3 or 5 below 1000.
  */

#include <stdio.h>
#include "common/eulersolution.h"

struct euler_state_s
{
    int sum;
};

static
int
is_multiple_of
    (int a
    ,int factor
    )
{
    return (a % factor == 0);
}

static
size_t
memory
    ()
{
    return sizeof(euler_state);
}

static
void
render
    (const void *p_mem
    ,char *p_str
    )
{
    const euler_state *p_state = p_mem;
    sprintf(p_str,"%d", p_state->sum);
}

static
void
solve
    (void *p_mem)
{

    int i;
    int sum = 0;
    euler_state *p_state = p_mem;
    for (i = 0; i < 1000; i++)
    {
        if (is_multiple_of(i,3) || is_multiple_of(i,5))
        {
            sum += i;
        }
    }
    p_state->sum = sum;
}

static const euler_solution problem00001 =
{
    /* name   */ "Multiples of 3 and 5",
    /* memory */ &memory,
    /* solve  */ &solve,
    /* render */ &render,
};

const euler_solution *p_problem00001 = &problem00001;
