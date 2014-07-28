/* This file contains definitions that make it easier to provide generic solutions to euler problems */

#ifndef EULERSOLUTION_H
#define EULERSOLUTION_H

#include <stddef.h>

typedef struct euler_state_s euler_state;

typedef struct euler_solution_s
{
    const char*           name;
    struct euler_state_s* (*init)(void *p_mem);
    size_t                (*memory)();
    void                  (*solve)(struct euler_state_s*);
    void                  (*print)(struct euler_state_s*);
} euler_solution;

#endif /* EULERSOLUTION_H */
