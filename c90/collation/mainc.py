EXTERN_SOLUTION_TEMPLATE  = """\
extern const euler_solution *p_problem{five_digit_problem_number};"""

SOLN_ARRAY_ENTRY_TEMPLATE = """\
    solns[{soln_num}] = p_problem{five_digit_problem_number};"""

MAIN_C_TEMPLATE = """\
#include <stdio.h>
#include <stdlib.h>

#include "common/eulersolution.h"

#define NUM_SOLNS {num_solutions}

{extern_solutions}

int
main
    (int    argc
    ,char **argv
    )
{{
    /* All available solutions. This is gonna get unwieldy (hopefully) */
    const euler_solution *solns[NUM_SOLNS];

    unsigned i;

    /* Had to go this way due to Error: initializer element is not computable at
     * load time */
{soln_array_entries}

    for (i = 0; i < NUM_SOLNS; i++)
    {{
        /* A buffer to print the solution to. Just guessing at how big this
         * ought to be... */
        char soln_buffer[4096];

        /* Grab a problem */
        const euler_solution *p_problem = solns[i];

        /* Get some memory for it. It is sensible to allocate memory on a
         * problem-by-problem basis because then valgrind can be helpful. */
        const size_t mem_needed = p_problem->memory();
        void *p_buffer = malloc(mem_needed);

        /* Solve and render the solution */
        euler_state *p_state = p_problem->solve(p_buffer);
        p_problem->render(p_state,soln_buffer);

        /* Print it out */
        printf("Problem %d - ", i+1);
        printf("%s\\n", p_problem->name);
        printf("%s\\n", soln_buffer);
        printf("\\n");

        free(p_buffer);
    }}

    (void)argc;
    (void)argv;
    return 0;
}}
"""
