#include "common/eulersolution.h"

#include "solution/00003/solution.h"
#include "solution/00004/solution.h"

#include <stdio.h>

int
main
    (void)
{
    euler_solution es;

    solve00003
        (&es);
    es.print_solution(&es);
    printf("%x\n",es.p_state);
    solve00004
        (&es);
    es.print_solution(&es);
    printf("%x\n",es.p_state);
    return 0;
}
