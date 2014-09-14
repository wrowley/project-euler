/**
  * Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.
  *
  * How many such routes are there through a 20×20 grid?
  */

#include <string.h>
#include <stdio.h>
#include "common/eulersolution.h"
#include "mathlib/include/extuint.h"

struct euler_state_s
{
    unsigned long answer;
};

#define PASCAL_DIGITS 40
#define PASCAL_ROWS   40

typedef struct pascals_triangle_s
{
    extensible_uint **p_cells;
    int              *p_initialised;

    unsigned          num_cells;
} pascals_triangle;

/* To get the offset to the start of Row N, call as pascals_triangle_row_offset(N-1).
 * For example, calling this with an argument of 0 returns 1, giving you the offset
 * into the first element of the 1st row. An argument of 1 returns 3, giving you
 * the offset into the first element of the 2nd row. */
static
unsigned
pascals_triangle_row_offset
    (unsigned row
    )
{
    /* Ignoring symmetry:
     *    Row 0 has 1
     *    Row 1 has 2
     *    Row 2 has 3
     *    Row 3 has 4
     */
    unsigned cells_in_row = (row + 1);
    if (row == 0)
    {
        return cells_in_row;
    }
    else
    {
        return cells_in_row + pascals_triangle_row_offset(row-1);
    }
}

static
const extensible_uint*
pascals_triangle_choose
    (pascals_triangle *p_triangle
    ,unsigned long     n
    ,unsigned long     k
    )
{
    unsigned offset  = pascals_triangle_row_offset(n - 1);
    unsigned cellnum = offset + k;

    if (p_triangle->p_initialised[cellnum])

}

static
size_t
pascals_triangle_memory
    (unsigned num_digits
    ,unsigned max_n
    )
{
    unsigned i;
    size_t mem = 0;

    /* This gives the number of cells required to form max_n rows without
     * exploiting symmetry */
    unsigned num_cells = pascals_triangle_row_offset(max_n);

    /* The struct */
    mem += sizeof(pascals_triangle);
    /* The cells themselves */
    mem += num_cells * sizeof(extensible_uint*);
    mem += num_cells * extensible_uint_memory(num_digits);
    /* Whether a given cell has been initialised */
    mem += num_cells * sizeof(int);
}

static
pascals_triangle*
pascals_triangle_init
    (void*    p_mem
    ,unsigned num_digits
    ,unsigned max_n
    )
{
    unsigned i;
    unsigned num_cells = pascals_triangle_row_offset(max_n);

    /* The struct */
    pascals_triangle *p_triangle = p_mem;
    p_mem = (char*)p_mem + sizeof(pascals_triangle);

    /* Store the number of cells we're expecting to have */
    p_triangle->num_cells = num_cells;

    /* Pointers to the cells */
    p_triangle->p_cells = p_mem;
    p_mem = (char*)p_mem + num_cells * sizeof(extensible_uint*);
    /* Allocate the cells */
    for (i = 0; i < p_triangle->num_cells; i++)
    {
        p_triangle->p_cells[i] = extensible_uint_init(p_mem, num_digits);
        p_mem = (char*)p_mem + extensible_uint_memory(num_digits);
    }

    /* Allocate the bit which checks whether we've calculated a cell already */
    p_triangle->p_initialised = p_mem;
    p_mem = (char*)p_mem + p_triangle->num_cells * sizeof(int);

    memset
        (p_triangle->p_initialised
        ,0
        ,p_triangle->num_cells * sizeof(int)
        );

    return p_triangle;
}

static
size_t
memory
    ()
{
    size_t sz = sizeof(euler_state);

    sz +=
        pascals_triangle_memory
            (PASCAL_DIGITS
            ,PASCAL_ROWS
            );

    return sz;
}

static
euler_state *
solve
    (void *p_mem)
{
    /*
     * For N = 1; M = N - 1;
     *  we want:
     *   1 |+ 1;
     *
     * For N = 2; M = N - 1;
     *  we want:
     *   1 + 2 |+ 2 +1;
     *
     * For N = 3; M = N - 1;
     *  we want
     *   1 + 3 + 6 |+ 6 + 3 +1;
     *   2c0 + 3c1 + 4c2
     *
     * For N = 4; M = N - 1;
     *  we want
     *   1   + 4         + 10      + 20      |+
     *   3c0 + 4c1       + 5c2     + 6c3     |+
     *   Mc0 + (M+1)c(1) + (M+2)c2 + (M+M)cM |+
     *
     * For N = 5; M = N - 1;
     *   1   + 5         + 15      + 35      + 70      |+
     *   4c0 + 5c1       + 6c2     + 7c3     + 8c4     |+
     *   Mc0 + (M+1)c(1) + (M+2)c2 + (M+3)c3 + (M+M)cM |+
     *
     * This is clearly a diagonal traversal of pascal's triangle.
     *
     * However, for N=20, calculating 38c19 is going to be a bit of a pig, as it doesn't fit in 32 bits.
     * We can calculate the rows of Pascal's triangle directly, or as we need them. We are going to use
     * a lot of them so we might precalculate them. The number of cells we need is:
     *    1 + 1 + 2 + 2 + 3 + 3 + ... + 19 + 19
     * =  2 * (1 + 2 + 3 + ... + 19)
     * =  2 * (20 * 9 + 10)
     * =  2 * (190)
     *
     * This is not strictly true, because we only need 19c0->19c19 (incl. symmetry) to seed the values
     * we actually want to calculate. Hmmm...
     */


    euler_state *p_state = p_mem;
    p_mem = (char*)p_mem + sizeof(euler_state);

    p_state->answer = 0;

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

static const euler_solution problem00015 =
{
    /* name   */ "Lattice paths",
    /* memory */ &memory,
    /* solve  */ &solve,
    /* render */ &render,
};

const euler_solution *p_problem00015 = &problem00015;
