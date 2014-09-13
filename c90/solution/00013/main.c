#include <stdio.h>
#include <stdlib.h>

#include "common/eulersolution.h"

extern const euler_solution *p_problem00013;

int
main
    (int argc, char **argv)
{
    /* A buffer to print the solution to */
    char soln_buffer[4096];

    /* Allocated memory required by the solution */
    const size_t mem_needed = p_problem00013->memory();
    void *p_buffer = malloc(mem_needed);

    /* Solve and render the solution */
    euler_state *p_state = p_problem00013->solve(p_buffer);
    p_problem00013->render(p_state,soln_buffer);

    /* Print it out */
    printf("%s\n",soln_buffer);

    free(p_buffer);

    (void)argc;
    (void)argv;
    return 0;
}
