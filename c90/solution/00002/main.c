#include "common/eulersolution.h"
#include "solution.h"

int
main
    (void)
{

    euler_solution soln;
    solve00002(&soln);
    soln.print_solution(&soln);
    return 0;
}