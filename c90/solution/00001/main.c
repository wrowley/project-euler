#include <stdio.h>
#include <stdlib.h>

#include "common/eulersolution.h"

extern const euler_solution *p_problem00001;

int
main
    (void)
{

    euler_state *p_state;
    void *buffer;
    const size_t mem_needed = p_problem00001->memory();

    buffer = malloc(mem_needed);

    p_state = p_problem00001->init(buffer);
    p_problem00001->solve(p_state);
    p_problem00001->print(p_state);

    free(buffer);

    return 0;
}
