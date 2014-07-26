/* This file contains definitions that make it easier to provide generic solutions to euler problems */

#ifndef EULERSOLUTION_H
#define EULERSOLUTION_H

typedef struct euler_solution_s
{
    void (*print_solution)(struct euler_solution_s *p_solution);
} euler_solution;

#endif /* EULERSOLUTION_H */
