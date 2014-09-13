/**
  * Problem description goes here
  */

#include <stdio.h>
#include "common/eulersolution.h"

/* Is it likely to have a prime factor larger than 1000 */
#define PRIME_FACTOR_ARRAY_SIZE 1000
#define DIVISOR_TARGET           500

static
unsigned
count_divisors_ulong
    (unsigned long num)
{
    unsigned long i;
    unsigned num_divisors = 1;

    unsigned prime_factor_power[PRIME_FACTOR_ARRAY_SIZE] = {0};

    /* Count prime factors in the number */
    for (i = 2; i < PRIME_FACTOR_ARRAY_SIZE; i++)
    {

        /* We should reach this condition eventually */
        if (i == num)
        {
            if (num != 1)
            {
                prime_factor_power[num]++;
            }
            break;
        }

        /* It's divisible, but it might be divisible again */
        if ((num % i) == 0)
        {
            num = num/i;
            prime_factor_power[i]++;
            i--;
        }

    }

    /* d(n) = (a+1)(b+1)(c+1)... */
    for (i = 0; i < PRIME_FACTOR_ARRAY_SIZE; i++)
    {
        if (prime_factor_power[i])
        {
            num_divisors *= (prime_factor_power[i] + 1);
        }
    }

    return num_divisors;
}

struct euler_state_s
{
    unsigned long answer;
};

static
size_t
memory
    ()
{
    size_t sz = sizeof(euler_state);

    return sz;
}

static
euler_state *
solve
    (void *p_mem)
{
    unsigned long i;

    unsigned long triangle_number = 0;
    unsigned num_divisors = 0;

    euler_state *p_state = p_mem;
    p_mem = (char*)p_mem + sizeof(euler_state);

    for (i = 1; num_divisors <= 500; i++)
    {
        triangle_number += i;
        num_divisors = count_divisors_ulong(triangle_number);
    }

    p_state->answer = triangle_number;


    return p_state;
}

static
void
render
    (const euler_state *p_state
    ,      char        *p_str
    )
{
    sprintf(p_str,"%lu", p_state->answer);
}

static const euler_solution problem00012 =
{
    /* name   */ "Problem Name",
    /* memory */ &memory,
    /* solve  */ &solve,
    /* render */ &render,
};

const euler_solution *p_problem00012 = &problem00012;
