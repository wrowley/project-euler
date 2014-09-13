#include <stddef.h>

/* An opaque type to the state struct */
typedef struct extensible_uint_s extensible_uint;


/** State Handling **/

/* Returns the amount of memory required to initialise an extensible uint
 * of num_digits length.
 */
size_t
extensible_uint_memory
    (unsigned num_digits
    );

/* Initialises an extensible uint. Returns an opaque handle to its own state.
 *   p_mem      - Must be a block of memory of at least the size returned by
 *       extensible_uint_memory()
 *   num_digits - The maximum number of digits this extensible uint is
 *       expected to hold. Behaviour is undefined if this is not the same
 *       argument passed to extensible_uint_memory().
 */
extensible_uint *
extensible_uint_init
    (void     *p_mem
    ,unsigned  num_digits
    );

/* Renders the number in base 10 into a buffer. The length of p_str must be
 * at least as long as (num_digits + 1).
 */
void
extensible_uint_render
    (const extensible_uint *p_state
    ,      char            *p_str
    );

/* Copies one extensible uint to another. */
void
extensible_uint_copy
    (const extensible_uint *p_src
    ,      extensible_uint *p_dst
    );


/** Logical and Arithmetic Operations */

/* Tests whether one extensible uint is strictly less than another. Returns
 * 1 if so and 0 otherwise. */
int
extensible_uint_lt
    (const extensible_uint *p_a
    ,const extensible_uint *p_b
    );

/* Populates the extensible uint from a buffer. */
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

/* Adds a extensible uint to the extensible uint. They must have been initialised with
 * the same number of digits. It is undefined behaviour if p_state does not have enough
 * headroom for the addition to take place. */
void
extensible_uint_add_extensible_uint
    (      extensible_uint *p_state
    ,const extensible_uint *p_addend
    );

/* This performs an unsigned integer division, and stores the result if
 * successful.
 * It returns a boolean indicating its own success (i.e. whether the
 * result has changed). */
int
extensible_uint_divide_ulong
    (extensible_uint *p_state
    ,unsigned long    divisor
    );

/* This performs an integer multiplication. */
void
extensible_uint_multiply_ulong
    (extensible_uint *p_state
    ,unsigned long    multiplier
    );
