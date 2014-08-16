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

/* Populates the integer from a buffer */
void
extensible_uint_populate
    (      extensible_uint *p_state
    ,const unsigned long   *p_digits
    ,const unsigned         num_digits
    );

/* This performs an integer division, and stores the result if successful.
 * It also returns a boolean indicating its own success (i.e. whether the
 * result has changed). */
int
extensible_uint_divide
    (extensible_uint *p_state
    ,unsigned long    divisor
    );
