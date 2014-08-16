/**
  * The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
  *
  * Find the sum of all the primes below two million.
  */

#include <stdio.h>
#include <string.h>
#include "common/eulersolution.h"
#include "mathlib/include/extuint.h"

/* Probably a decent approach to use a Sieve of Eratosthenes again,
 * as in problem 7. log2(2000000) == 20.9*, so we need the next even
 * power, 2^22.
 */
#define SIZE_OF_SIEVE_2_POW (22)
#define SIZE_OF_SIEVE       (1 << SIZE_OF_SIEVE_2_POW)
#define SQRT_SIZE_OF_SIEVE  (1 << (SIZE_OF_SIEVE_2_POW/2))

struct euler_state_s
{
    unsigned long   *p_sieve;
    /* Crazily conservative maximum for number of bits required
     * to hold the answer is ceil(log2(2000000 * 1000000)) = 41
     * So I guess use the extended uint. */
    extensible_uint *p_extuint;
};

/* Crazily conservative maximum for this is ceil(log10(2000000 * 1000000)) = 13 */
#define MAX_NUM_DIGITS (13)

static
size_t
memory
    ()
{
    size_t sz = sizeof(euler_state);

    sz += SIZE_OF_SIEVE * sizeof(unsigned long);

    sz += extensible_uint_memory(MAX_NUM_DIGITS);

    return sz;
}

static
euler_state *
solve
    (void *p_mem)
{
    euler_state *p_state = p_mem;
    p_mem = (char*)p_mem + sizeof(euler_state);

    p_state->p_sieve = p_mem;
    p_mem = (char*)p_mem + SIZE_OF_SIEVE * sizeof(unsigned long);

    p_state->p_extuint =
        extensible_uint_init
          (p_mem
          ,MAX_NUM_DIGITS
          );
    p_mem = (char*)p_mem + extensible_uint_memory(MAX_NUM_DIGITS);

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
                if (result >= SIZE_OF_SIEVE)
                {
                    break;
                }
                p_state->p_sieve[result] = 0ul;
            }
        }
    }

    /* Add the primes below 2mil */
    {
        /* Sieve index */
        unsigned long si;

        /* Start from 2 again, of course */
        for (si = 2; si < SIZE_OF_SIEVE; si += 1)
        {
            if (p_state->p_sieve[si] != 0)
            {
                if (si < 2000000ul)
                {
                    extensible_uint_add_ulong
                        (p_state->p_extuint
                        ,si
                        );
                }
            }
        }
    }


    return p_state;

}

static
void
render
    (const euler_state *p_state
    ,      char        *p_str
    )
{
    extensible_uint_render
        (p_state->p_extuint
        ,p_str
        );
}

static const euler_solution problem00010 =
{
    /* name   */ "Summation of primes",
    /* memory */ &memory,
    /* solve  */ &solve,
    /* render */ &render,
};

const euler_solution *p_problem00010 = &problem00010;
