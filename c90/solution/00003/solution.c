/**
  * The prime factors of 13195 are 5, 7, 13 and 29.
  *
  * What is the largest prime factor of the number 600851475143 ?
  */

#include <stdio.h>
#include <string.h>
#include "common/eulersolution.h"

/* Number of digits in the problem, to begin with */
#define NUM_DIGITS 12

/* Definitions for the extensible unsigned integer class to use.
 * It's assumed that the base of the unsigned's in the class is
 * 10. This is obviously super inefficient, but should be relatively
 * easy to read. */
typedef struct
{
    /* How many digits the number can hold */
    unsigned       num_digits;
    /* The current state of the number */
    unsigned long *result;
    /* A buffer required for calculating intermediate state */
    unsigned long *scratch;
} extensible_uint;

static
extensible_uint *
extensible_uint_init
    (void     *p_mem
    ,unsigned  num_digits
    )
{
    extensible_uint *p_state = p_mem;
    p_mem = (char*)p_mem + sizeof(extensible_uint);

    p_state->num_digits = num_digits;

    p_state->result = p_mem;
    p_mem = (char*)p_mem + sizeof(unsigned long) * num_digits;
    memset(p_state->result, 0, sizeof(unsigned long) * num_digits);

    p_state->scratch = p_mem;
    p_mem = (char*)p_mem + sizeof(unsigned long) * num_digits;
    memset(p_state->scratch, 0, sizeof(unsigned long) * num_digits);

    return p_state;
}

static
size_t
extensible_uint_memory
    (unsigned num_digits
    )
{
    size_t sz = 0;

    /* State */
    sz += sizeof(extensible_uint);
    /* Buffer for real digits */
    sz += sizeof(unsigned long) * num_digits;
    /* Buffer for scratch digits */
    sz += sizeof(unsigned long) * num_digits;

    return sz;
}

/* Populates the integer from a buffer */
static
void
extensible_uint_populate
    (      extensible_uint *p_state
    ,const unsigned long   *p_digits
    ,const unsigned         num_digits
    )
{
    unsigned i;
    p_state->num_digits = num_digits;
    for (i = 0; i < p_state->num_digits; i++)
    {
        p_state->result[i] = p_digits[i];
    }
}

/* This performs an integer division, and stores the result if successful.
 * It also returns a boolean indicating its own success (i.e. whether the
 * result has changed). */
static
int
extensible_uint_divide
    (extensible_uint *p_state
    ,unsigned long    divisor
    )
{
    unsigned i;
    unsigned long dividend = 0;

    /* We're working in the scratch buffer */
    memset
        (p_state->scratch
        ,0
        ,p_state->num_digits * sizeof(unsigned long)
        );

    for (i = 0; i < p_state->num_digits; i++)
    {
        unsigned long digit = p_state->result[i];

        /* Dividend grows by the current digit in the result */
        dividend += digit;

        /* If dividend >= divisor, so we do the division and keep the remainder
         * in the dividend. If divisor < dividend, we don't have anything for this
         * digit. Note that this of course covers divisor == 0. */
        if (dividend >= divisor)
        {
            p_state->scratch[i] = dividend/divisor;
            dividend = dividend % divisor;
        }

        /* The dividend is scaled up by 10 in either case */
        dividend *= 10;
    }

    if (dividend == 0)
    {
        /* We don't have a remainder at the end of the loop, so integer division
         * happened and we store the result */
        memmove
            (p_state->result
            ,p_state->scratch
            ,p_state->num_digits * sizeof(unsigned long)
            );
        return 1;
    }
    else
    {
        /* Division did not occur */
        return 0;
    }

}

#if 0
static
void
extensible_uint_print
    (extensible_uint *p_state
    )
{
    unsigned i;
    for (i = 0; i < p_state->num_digits; i++)
    {
        printf("%u", p_state->result[i]);
    }
    printf("\n");
}
#endif

struct euler_state_s
{
    unsigned long    answer;
    extensible_uint *exuint;
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
    p_state->exuint =
        extensible_uint_init
            (p_mem
            ,NUM_DIGITS
            );
    p_mem = (char*)p_mem + extensible_uint_memory(NUM_DIGITS);

    /* Load up the number */
    extensible_uint_populate
        (p_state->exuint
        ,number
        ,NUM_DIGITS
        );

    /* Fairly naive loop, but leaves out even numbers. It also starts at 3, as we
     * know the number is not divisble by 2. */
    for (factor = 3; factor < MAX_FACTOR; factor+=2)
    {
        int division_happened = extensible_uint_divide(p_state->exuint,factor);

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
