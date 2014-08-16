#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "include/extuint.h"

#define BASE 10

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

void
extensible_uint_render
    (const extensible_uint *p_state
    ,      char            *p_str
    )
{
    unsigned i;
    unsigned ci;
    unsigned leading_zeros_finished;
    for (i = 0, ci = 0, leading_zeros_finished = 0; i < p_state->num_digits; i++)
    {
        if (p_state->result[i] == 0)
        {
            /* Only want to print non-leading zeros */
            if (leading_zeros_finished)
            {
                sprintf(p_str + (ci++), "%lu", p_state->result[i]);
            }
        }
        else
        {
            sprintf(p_str + (ci++), "%lu", p_state->result[i]);
            leading_zeros_finished = 1;
        }
    }
    /* Terminate the string */
    *(p_str + ci) = 0;
}

void
extensible_uint_copy
    (const extensible_uint *p_src
    ,      extensible_uint *p_dst
    )
{
    unsigned i;

    /* TODO: implement a max_digits concept */
    assert(p_dst->num_digits >= p_src->num_digits);
    p_dst->num_digits = p_src->num_digits;

    for (i = 0; i < p_src->num_digits; i++)
    {
        p_dst->result[i] = p_src->result[i];
    }

}

int
extensible_uint_lt
    (const extensible_uint *p_a
    ,const extensible_uint *p_b
    )
{
    unsigned i;
    unsigned num_digits = p_a->num_digits;

    /* TODO: this could be a bit more digits-agnostic */
    assert(p_a->num_digits == p_b->num_digits);

    for (i = 0; i < num_digits; i++)
    {
        if (p_b->result[i] > p_a->result[i])
        {
            return 1;
        }
        else if (p_a->result[i] > p_b->result[i])
        {
            return 0;
        }
    }

    /* No, it is not strictly less than the other */
    return 0;
}

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

static
void
normalise_base
    (extensible_uint *p_state
    )
{
    unsigned i;

    for (i = p_state->num_digits - 1; i > 0; i--)
    {
        unsigned long carry   = p_state->result[i] / BASE;
        unsigned long remaind = p_state->result[i] % BASE;
        p_state->result[i]    = remaind;
        p_state->result[i-1] += carry;
    }
}

void
extensible_uint_add_ulong
    (extensible_uint *p_state
    ,unsigned long    addend
    )
{
    const unsigned last_digit_index = p_state->num_digits - 1;

    /* Add to the last digit */
    p_state->result[last_digit_index] += addend;

    normalise_base(p_state);

}

int
extensible_uint_divide_ulong
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

void
extensible_uint_multiply_ulong
    (extensible_uint *p_state
    ,unsigned long    multiplier
    )
{
    /* TODO: make this less naive by normalising bases as we go maybe? */
    unsigned i;

    for (i = 0; i < p_state->num_digits; i++)
    {
        p_state->result[i] *= multiplier;
    }

    normalise_base(p_state);
}
