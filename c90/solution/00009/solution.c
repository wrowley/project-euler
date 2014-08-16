/**
  * Problem description goes here
  */

#include <stdio.h>
#include "common/eulersolution.h"

struct euler_state_s
{
    unsigned answer;
};

static
size_t
memory
    ()
{
    size_t sz = sizeof(euler_state);

    return sz;
}

static
euler_state *
solve
    (void *p_mem)
{
    unsigned a,b,c;

    euler_state *p_state = p_mem;
    p_mem = (char*)p_mem + sizeof(euler_state);

    for (a = 0; a < 1000/3; a++)
    {
        for (b = a + 1; b < 2 * 1000/3; b++)
        {
            for (c = b + 1; c < 1000; c++)
            {
                unsigned sum = a + b + c;

                if (sum == 1000)
                {
                    unsigned lhs = a*a + b*b;
                    unsigned rhs = c*c;

                    if (lhs == rhs)
                    {
                        p_state->answer = a * b * c;
                        return p_state;
                    }
                }

            }
        }
    }

    p_state->answer = 0;

    return p_state;
}

static
void
render
    (const euler_state *p_state
    ,      char        *p_str
    )
{
    sprintf(p_str,"%u", p_state->answer);
}

static const euler_solution problem00009 =
{
    /* name   */ "Problem Name",
    /* memory */ &memory,
    /* solve  */ &solve,
    /* render */ &render,
};

const euler_solution *p_problem00009 = &problem00009;
