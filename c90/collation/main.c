#include <stdio.h>
#include <stdlib.h>

#include "common/eulersolution.h"

extern const euler_solution *p_problem00001;
extern const euler_solution *p_problem00002;
extern const euler_solution *p_problem00003;
extern const euler_solution *p_problem00004;
extern const euler_solution *p_problem00005;
extern const euler_solution *p_problem00006;
extern const euler_solution *p_problem00007;

int
main
    (int argc, char **argv)
{
    /* All available solutions. This is gonna get unwieldy (hopefully) */
    const euler_solution *solns[] =
    {
        p_problem00001,
        p_problem00002,
        p_problem00003,
        p_problem00004,
        p_problem00005,
        p_problem00006,
        p_problem00007,
    };
    const static int NUM_SOLNS = sizeof(solns)/sizeof(euler_solution*);

    /* A buffer to print the solution to */
    char soln_buffer[4096];

    int i;
    for (i = 0; i < NUM_SOLNS; i++)
    {
        /* Grab a problem */
        const euler_solution *p_problem = solns[i];

        /* Get some memory for it */
        const size_t mem_needed = p_problem->memory();
        void *p_buffer = malloc(mem_needed);

        /* Solve and render the solution */
        p_problem->solve(p_buffer);
        p_problem->render(p_buffer,soln_buffer);

        /* Print it out */
        printf("Problem %d - ",i+1);
        printf("%s\n",p_problem->name);
        printf("%s\n",soln_buffer);
        printf("\n");

        free(p_buffer);
    }

    (void)argc;
    (void)argv;
    return 0;
}
