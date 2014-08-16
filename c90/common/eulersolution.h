/* This file contains definitions that make it easier to provide generic solutions to euler problems */

#ifndef EULERSOLUTION_H
#define EULERSOLUTION_H

#include <stddef.h>

/* Each solution must implement this struct privately. */
typedef struct euler_state_s euler_state;

/* This struct enables solutions to expose only the necessary details required
 * to run their implementation and print their result */
typedef struct euler_solution_s
{
    /* This is the name of the problem. For example, Problem 1 is called
     * "Multiples of 3 and 5" */
    const char            *name;

    /* This function must return the amount of memory required by the solution's
     * solve function. This can be thought of as the sum of size of a solution's
     * euler_state_s and its scratch requirements. */
    size_t                (*memory)();

    /* This function must solve the problem in its entirety. It takes a single
     * argument of a buffer of a size returned by memory(). It must be able
     * to solve the problem without any assumptions about the contents of
     * the buffer. It returns a pointer to the solution's implementation
     * of euler_state. */
    euler_state*          (*solve)(void *);

    /* This function simply exists to render the solution of the problem to
     * a buffer of chars. Behaviour is undefined unless its first argument is
     * a pointer to the same pointer as returned by the most recent call to solve().
     * This function expects the contents of its state not to have changed since
     * solve() was last called. The second argument must be a pointer to a buffer
     * of chars guaranteed to be large enough to fit the whole solution, just as
     * it would be copy-pasted into the project-euler website for any
     * given problem. */
    void                  (*render)(const euler_state*, char *);
} euler_solution;

#endif /* EULERSOLUTION_H */
