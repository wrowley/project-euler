/**
  * By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
  *
  * What is the 10 001st prime number?
  */

#include <stdio.h>
#include <string.h>
#include "common/eulersolution.h"

/* Probably a decent approach to use a Sieve of Eratosthenes here,
 * since the target prime isn't very high up. Can tweak the size
 * of the table here. */
#define SIZE_OF_SIEVE_2_POW (18)
#define SIZE_OF_SIEVE       (1 << SIZE_OF_SIEVE_2_POW)
#define SQRT_SIZE_OF_SIEVE  (1 << (SIZE_OF_SIEVE_2_POW/2))

#define TARGET_PRIME        (10001)

struct euler_state_s
{
    unsigned long answer;
    unsigned long *p_sieve;
};

static
size_t
memory
    ()
{
    size_t sz = sizeof(euler_state);

    sz += SIZE_OF_SIEVE * sizeof(unsigned long);

    return sz;
}

static
void
solve
    (void *p_mem)
{
    euler_state *p_state = p_mem;
    p_mem = (char*)p_mem + sizeof(euler_state);

    p_state->p_sieve = p_mem;
    p_mem = (char*)p_mem + SIZE_OF_SIEVE * sizeof(unsigned long);

    /* Assume they're all prime. This memory setting doesn't have
     * to result in sensible long values, it just has to be non-zero.
     */
    memset
        (p_state->p_sieve
        ,1
        ,SIZE_OF_SIEVE * sizeof(unsigned long)
        );

    /* Hollow out the sieve */
    {
        /* Sieve index */
        unsigned long si;
        unsigned long factor;

        /* We know 2 is the first prime. */
        for (si = 2; si <= SIZE_OF_SIEVE; si += 1)
        {
            for (factor = 2; factor <= SQRT_SIZE_OF_SIEVE; factor+=1)
            {
                unsigned long result = si * factor;
                if (result > SIZE_OF_SIEVE)
                {
                    break;
                }
                p_state->p_sieve[result] = 0ul;
            }
        }
    }

    /* Count the primes */
    {
        /* Sieve index */
        unsigned long si;

        unsigned prime_count = 0;

        /* Start from 2 again, of course */
        for (si = 2; si < SIZE_OF_SIEVE; si += 1)
        {
            if (p_state->p_sieve[si] != 0)
            {
                prime_count++;
                if (prime_count == TARGET_PRIME)
                {
                    p_state->answer = si;
                    break;
                }
            }
        }
    }

}

static
void
render
    (const void *p_mem
    ,      char *p_str
    )
{
    const euler_state *p_state = p_mem;
    sprintf(p_str,"%lu", p_state->answer);
}

static const euler_solution problem00007 =
{
    /* name   */ "10001st prime",
    /* memory */ &memory,
    /* solve  */ &solve,
    /* render */ &render,
};

const euler_solution *p_problem00007 = &problem00007;
