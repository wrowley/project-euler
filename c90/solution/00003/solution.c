/**
  * The prime factors of 13195 are 5, 7, 13 and 29.
  *
  * What is the largest prime factor of the number 600851475143 ?
  */

#include <stdio.h>
#include <string.h>
#include "common/eulersolution.h"
#include "mathlib/include/extuint.h"

/* Number of digits in the problem, to begin with */
#define NUM_DIGITS 12

struct euler_state_s
{
    unsigned long    answer;
    extensible_uint *p_extuint;
};

static
size_t
memory
    ()
{
    size_t sz = 0;
    sz += sizeof(euler_state);
    sz += extensible_uint_memory(NUM_DIGITS);
    return sz;
}

static
euler_state *
solve
    (void *p_mem)
{
    /* The problem looks like this */
    static const unsigned long number[NUM_DIGITS] = {6,0,0,8,5,1,4,7,5,1,4,3};
    /* The maximum factor that it could possibly be is floor(sqrt(600851475143)) */
    static const unsigned long MAX_FACTOR         = 775146;

    unsigned long factor;

    /* Set up state */
    euler_state *p_state = p_mem;
    p_mem = (char*)p_mem + sizeof(euler_state);

    /* Set up the integer we'll use to calculate the result */
    p_state->p_extuint =
        extensible_uint_init
            (p_mem
            ,NUM_DIGITS
            );
    p_mem = (char*)p_mem + extensible_uint_memory(NUM_DIGITS);

    /* Load up the number */
    extensible_uint_populate
        (p_state->p_extuint
        ,number
        ,NUM_DIGITS
        );

    /* Fairly naive loop, but leaves out even numbers. It also starts at 3, as we
     * know the number is not divisble by 2. */
    for (factor = 3; factor < MAX_FACTOR; factor+=2)
    {
        int division_happened = extensible_uint_divide_ulong(p_state->p_extuint,factor);

        if (division_happened)
        {
            /* This is the largest factor we know of */
            p_state->answer = factor;
            /* We might need to divide by it again! */
            factor -= 2;
        }
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

static const euler_solution problem00003 =
{
    /* name   */ "Largest prime factor",
    /* memory */ &memory,
    /* solve  */ &solve,
    /* render */ &render,
};

const euler_solution *p_problem00003 = &problem00003;
