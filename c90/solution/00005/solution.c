/**
  * 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
  *
  * What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
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
euler_state *
solve
    (void *p_mem)
{
    euler_state *p_state = p_mem;

    /* Use this to hold LCM(1:20), which we suspect is less than a long */
    long answer = 1;

    /* We just care about the prime factorisation of all numbers
     * from 1:20. If the prime factors that make up a number have
     * already been accounted for by another number, i.e.
     *      n is equally divisible by (n - p)
     *      n % (n - p) = 0
     * then we just use the remaining prime factors. Seemed
     * like doing this manually was the most pragmatic way:
     */
    answer *= 20; /* 20 = 2 x 2 x 5     */
    answer *= 19; /* 19 = 19            */
    answer *= 9 ; /* 18 = 2 x 3 x 3     */
    answer *= 17; /* 17 = 17            */
    answer *= 4 ; /* 16 = 2 x 2 x 2 x 2 */
    answer *= 1 ; /* 15 = 3 x 5         */
    answer *= 7 ; /* 14 = 2 x 7         */
    answer *= 13; /* 13 = 13            */
    answer *= 1 ; /* 12 = 2 x 3 x 3     */
    answer *= 11; /* 11 = 11            */
    answer *= 1 ; /* 10 = 2 x 5         */
    answer *= 1 ; /* 9  = 3 x 3         */
    answer *= 1 ; /* 8  = 2 x 2 x 2     */
    answer *= 1 ; /* 7  = 7             */
    answer *= 1 ; /* 6  = 2 x 3         */
    answer *= 1 ; /* 5  = 5             */
    answer *= 1 ; /* 4  = 2 x 2         */
    answer *= 1 ; /* 3  = 3             */
    answer *= 1 ; /* 2  = 2             */

    p_state->answer = answer;

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

static const euler_solution problem00005 =
{
    /* name   */ "Smallest multiple",
    /* memory */ &memory,
    /* solve  */ &solve,
    /* render */ &render,
};

const euler_solution *p_problem00005 = &problem00005;
