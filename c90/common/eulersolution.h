/* This file contains definitions that make it easier to provide generic solutions to euler problems */

#ifndef EULERSOLUTION_H
#define EULERSOLUTION_H

typedef struct euler_state_s euler_state;

typedef struct euler_solution_s
{
    void (*print_solution)(struct euler_solution_s *p_solution);

    euler_state *p_state;
} euler_solution;

#endif /* EULERSOLUTION_H */
