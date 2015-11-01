/**
  * 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
  *
  * What is the sum of the digits of the number 2^1000?
  */

#include <stdio.h>
#include "common/eulersolution.h"

#define NUM_DIGITS 500

struct euler_state_s
{
    unsigned long answer;
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
    unsigned digits[NUM_DIGITS] = {0};
    unsigned i, j;

    euler_state *p_state = p_mem;
    p_mem = (char*)p_mem + sizeof(euler_state);

    /* Start with 1 */
    digits[0] = 1;

    for (i = 0; i < 1000; i++)
    {
        /* Multiply the number by two */
        for (j = 0; j < NUM_DIGITS; j++)
        {
            digits[j] <<= 1;
        }
        /* Perform carry operation */
        for (j = 0; j < NUM_DIGITS - 1; j++)
        {
            unsigned n = digits[j];
            unsigned r = n % 10;

            if (r != n)
            {
                digits[j]    = r;
                digits[j+1] += 1;
            }
        }
    }

    /* Sum all the digits */
    p_state->answer = 0;
    for (j = 0; j < NUM_DIGITS; j++)
    {
        p_state->answer += digits[j];
    }

    return p_state;
}

static
void
render
    (const euler_state *p_state
    ,      char        *p_str
    )
{
    sprintf(p_str,"%lu", p_state->answer);
}

static const euler_solution problem00016 =
{
    /* name   */ "Power digit sum",
    /* memory */ &memory,
    /* solve  */ &solve,
    /* render */ &render,
};

const euler_solution *p_problem00016 = &problem00016;
