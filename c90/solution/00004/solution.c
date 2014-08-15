/**
  * Problem description goes here
  */

#include <stdio.h>
#include "common/eulersolution.h"

#define MAX_3_BY_3_DIGITS 6

struct euler_state_s
{
    /* 999^2 > 2^16 */
    long answer;
};

static
size_t
is_palindrome_str
    (const char *candidate
    ,      int   length
    )
{
    int i;
    for (i = 0; i < length/2; i++)
    {
        if (!(candidate[i] == candidate[length - i - 1]))
        {
            return 0;
        }
    }
    return 1;
}

static
size_t
is_palindrome_long
    (long candidate)
{
    char buffer[MAX_3_BY_3_DIGITS + 1];
    int  str_length =
        sprintf
            (buffer
            ,"%lu"
            ,candidate
            );
    return
        is_palindrome_str
            (buffer
            ,str_length
            );
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
solve
    (void *p_mem)
{
    euler_state *p_state = p_mem;
    long result = 0;
    long factor0;
    long factor1;

    long MIN_3_DIGIT = 111;
    long MAX_3_DIGIT = 999;

    p_state->answer  = 0;

    /* The largest palindrome should probably be the first one we come across
     * by multiplying big numbers together. This means we need to search really
     * near the big number first, rather than go all the way down to big * small
     * straight away. Turns out this is non-trivial??!! i.e. the following
     * is of course completely broken: */
#if 0
    for (range = 0; range <= MAX_3_DIGIT - MIN_3_DIGIT; range++)
    {
        for (factor0 = MAX_3_DIGIT; factor0 >= (MIN_3_DIGIT + range); factor0--)
        {
            factor1 = factor0 - range;
#endif
    /* Instead, this actually doesn't take very long and the number of multiplies/
     * comparisons it has to do is well defined */
    for (factor0 = MIN_3_DIGIT; factor0 < MAX_3_DIGIT; factor0++)
    {
        for (factor1 = factor0; factor1 < MAX_3_DIGIT; factor1++)
        {
            result = factor0 * factor1;
            if ((p_state->answer < result) && is_palindrome_long(result))
            {
                p_state->answer = result;
            }
        }
    }

}

static
void
render
    (const void *p_mem
    ,      char *p_str
    )
{
    const euler_state *p_state = p_mem;
    sprintf(p_str,"%lu", p_state->answer);
}

static const euler_solution problem00004 =
{
    /* name   */ "Largest palindrome product",
    /* memory */ &memory,
    /* solve  */ &solve,
    /* render */ &render,
};

const euler_solution *p_problem00004 = &problem00004;
