#include <string.h>

#include "include/extuint.h"

/* Definitions for the extensible unsigned integer class to use.
 * It's assumed that the base of the unsigned's in the class is
 * 10. This is obviously super inefficient, but should be relatively
 * easy to read. */
struct extensible_uint_s
{
    /* How many digits the number can hold */
    unsigned       num_digits;
    /* The current state of the number */
    unsigned long *result;
    /* A buffer required for calculating intermediate state */
    unsigned long *scratch;
};

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
