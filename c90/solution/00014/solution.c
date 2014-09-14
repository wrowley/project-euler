/**
  * The following iterative sequence is defined for the set of positive integers:
  *
  * n → n/2 (n is even)
  * n → 3n + 1 (n is odd)
  *
  * Using the rule above and starting with 13, we generate the following sequence:
  *
  * 13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
  * It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.
  *
  * Which starting number, under one million, produces the longest chain?
  *
  * NOTE: Once the chain starts the terms are allowed to go above one million.
  */

#include <assert.h>
#include <stdio.h>
#include "common/eulersolution.h"

struct euler_state_s
{
    unsigned long answer;
};

static
unsigned long
collatz_length
    (unsigned long n)
{
    assert(n != 0);
    if (n == 1)
    {
        return 1;
    }

    if (n % 2 == 0)
    {
        n = n/2;
    }
    else
    {
        n = 3*n + 1;
    }

    return 1 + collatz_length(n);
}

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
    unsigned long n;
    unsigned long longest_collatz = 0;

    euler_state *p_state = p_mem;
    p_mem = (char*)p_mem + sizeof(euler_state);

    for (n = 1; n < 1000000; n++)
    {
        unsigned long length = collatz_length(n);
        if (longest_collatz < length)
        {
            longest_collatz = length;
            p_state->answer = n;
        }
        longest_collatz = longest_collatz > length ? longest_collatz : length;
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

static const euler_solution problem00014 =
{
    /* name   */ "Longest Collatz sequence",
    /* memory */ &memory,
    /* solve  */ &solve,
    /* render */ &render,
};

const euler_solution *p_problem00014 = &problem00014;
