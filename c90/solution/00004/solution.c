/**
  * Problem description goes here
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

static const euler_solution problem00004 =
{
    /* name   */ "Problem Name",
    /* memory */ &memory,
    /* solve  */ &solve,
    /* render */ &render,
};

const euler_solution *p_problem00004 = &problem00004;
