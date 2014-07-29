/**
  * Each new term in the Fibonacci sequence is generated by adding the previous two terms. By starting with 1 and 2, the first 10 terms will be:
  *
  * 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
  *
  * By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.
  */

#include <stdio.h>
#include "common/eulersolution.h"

struct euler_state_s
{
    long answer;
};

static
size_t
memory
    ()
{
    return sizeof(euler_state);
}

static
void
solve
    (void *p_mem)
{
    euler_state *p_state = p_mem;
    unsigned long f0;
    unsigned long f1;
    unsigned long tmp;

    unsigned long sum = 0;

    for (f0 = 0, f1 = 1; f1 < 4000000; tmp = f1, f1 += f0, f0 = tmp)
    {
        if (!(f1 & 1))
        {
            sum += f1;
        }
    }
    p_state->answer = sum;
}

static
void
render
    (const void *p_mem
    ,char *p_str
    )
{
    const euler_state *p_state = p_mem;
    sprintf(p_str,"%d", p_state->answer);
}

static const euler_solution problem00002 =
{
    /* name   */ "Problem Name",
    /* memory */ &memory,
    /* solve  */ &solve,
    /* render */ &render,
};

const euler_solution *p_problem00002 = &problem00002;
