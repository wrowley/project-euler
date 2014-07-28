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
    return (((a/factor)*factor) == a);
}

static
size_t
memory
    ()
{
    return sizeof(euler_state);
}

static
euler_state *
init
    (void        *p_mem
    )
{
    euler_state *p_state = (euler_state*)p_mem;
    return p_state;
}

static
void
print
    (euler_state *p_state
    )
{
    printf("sum == %d\n", p_state->sum);
}

static
void
solve
    (euler_state *p_state
    )
{

    int i;
    int sum = 0;
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
    /* init   */ &init,
    /* memory */ &memory,
    /* solve  */ &solve,
    /* print  */ &print,
};

const euler_solution *p_problem00001 = &problem00001;
