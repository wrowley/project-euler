#include <stddef.h>

typedef struct extensible_uint_s extensible_uint;

extensible_uint *
extensible_uint_init
    (void     *p_mem
    ,unsigned  num_digits
    );

size_t
extensible_uint_memory
    (unsigned num_digits
    );

void
extensible_uint_render
    (const extensible_uint *p_state
    ,      char            *p_str
    );

/* Copies one extensible_uint to another */
void
extensible_uint_copy
    (const extensible_uint *p_src
    ,      extensible_uint *p_dst
    );

/* Tests whether one extensible uint is strictly less than another */
int
extensible_uint_lt
    (const extensible_uint *p_a
    ,const extensible_uint *p_b
    );

/* Populates the integer from a buffer */
void
extensible_uint_populate
    (      extensible_uint *p_state
    ,const unsigned long   *p_digits
    ,const unsigned         num_digits
    );

/* Adds an unsigned long to the extensible uint */
void
extensible_uint_add_ulong
    (extensible_uint *p_state
    ,unsigned long    addend
    );

/* This performs an integer division, and stores the result if successful.
 * It also returns a boolean indicating its own success (i.e. whether the
 * result has changed). */
int
extensible_uint_divide_ulong
    (extensible_uint *p_state
    ,unsigned long    divisor
    );

/* This performs an integer muliplication. */
void
extensible_uint_multiply_ulong
    (extensible_uint *p_state
    ,unsigned long    divisor
    );
