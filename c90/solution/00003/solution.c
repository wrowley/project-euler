/**
  * The prime factors of 13195 are 5, 7, 13 and 29.
  *
  * What is the largest prime factor of the number 600851475143 ?
  */

#include <stdio.h>
#include "common/eulersolution.h"

struct euler_state_s
{
    int answer;
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
    p_state->answer = 0;
}

static
void
render
    (const void *p_mem
    ,char *p_str
    )
{
    const euler_state *p_state = p_mem;
    sprintf(p_str,"%d", p_state->answer);
}

static const euler_solution problem00003 =
{
    /* name   */ "Problem Name",
    /* memory */ &memory,
    /* solve  */ &solve,
    /* render */ &render,
};

const euler_solution *p_problem00003 = &problem00003;
