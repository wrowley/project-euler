/**
  * The sum of the squares of the first ten natural numbers is,
  *
  * 1^ + 2^2 + ... + 10^2 = 385
  *
  * The square of the sum of the first ten natural numbers is,
  *
  * (1 + 2 + ... + 10)^2 = 552 = 3025
  *
  * Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 − 385 = 2640.
  *
  * Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
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

    /* The difference is made up of all the cross-multiplication terms, so
     * sum{1x2, 1x3, ..., 1x100, 2x1, 2x3, ..., 2x100, ..., 100x1, 100x2, ..., 100x99}.
     *
     * Interesting to note there are heaps of redundant calculations...
     *
     * It can be trivially simplified as follows:
     *     sum{ n * (sum(1:100) - n), for n = 1:100 }
     *   = sum{ n * (5050 - n),       for n = 1:100 }
     *   = sum{ 5050*n - n^2,         for n = 1:100 }
     *
     * The figure must be way smaller than 100 * (5050 * 100 - 100^2) = 49500000,
     * and log2(49500000) = 25.*
     *
     * So the answer will definitely fit in an unsigned long according to ANSI C.
     */

    unsigned long n;
    unsigned long sum = 0;

    for (n = 1; n <= 100; n++)
    {
        sum += 5050*n - n*n;
    }

    p_state->answer = sum;
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

static const euler_solution problem00006 =
{
    /* name   */ "Sum square difference",
    /* memory */ &memory,
    /* solve  */ &solve,
    /* render */ &render,
};

const euler_solution *p_problem00006 = &problem00006;
