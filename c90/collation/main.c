#include <stdio.h>
#include <stdlib.h>

#include "common/eulersolution.h"

#define NUM_SOLNS 8

extern const euler_solution *p_problem00001;
extern const euler_solution *p_problem00002;
extern const euler_solution *p_problem00003;
extern const euler_solution *p_problem00004;
extern const euler_solution *p_problem00005;
extern const euler_solution *p_problem00006;
extern const euler_solution *p_problem00007;
extern const euler_solution *p_problem00008;

int
main
    (int argc, char **argv)
{
    /* All available solutions. This is gonna get unwieldy (hopefully) */
    const euler_solution *solns[NUM_SOLNS];

    int i;

    /* Had to go this way due to Error: initializer element is not computable at
     * load time */
    solns[0] = p_problem00001;
    solns[1] = p_problem00002;
    solns[2] = p_problem00003;
    solns[3] = p_problem00004;
    solns[4] = p_problem00005;
    solns[5] = p_problem00006;
    solns[6] = p_problem00007;
    solns[7] = p_problem00008;

    for (i = 0; i < NUM_SOLNS; i++)
    {
        /* A buffer to print the solution to */
        char soln_buffer[4096];

        /* Grab a problem */
        const euler_solution *p_problem = solns[i];

        /* Get some memory for it */
        const size_t mem_needed = p_problem->memory();
        void *p_buffer = malloc(mem_needed);

        /* Solve and render the solution */
        euler_state *p_state = p_problem->solve(p_buffer);
        p_problem->render(p_state,soln_buffer);

        /* Print it out */
        printf("Problem %d - ", i+1);
        printf("%s\n", p_problem->name);
        printf("%s\n", soln_buffer);
        printf("\n");

        free(p_buffer);
    }

    (void)argc;
    (void)argv;
    return 0;
}
