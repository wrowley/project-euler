#!/usr/bin/python

import os
import mainc

HERE = os.path.dirname(__file__)

SOLUTION_FORMAT = "%05d"

SOLUTION_OBJECT_TEMPLATE = """../solution/{solution_number}/solution.o"""

BUILD_SOLUTION_TEMPLATE = """\
solution{solution_number}:
\t$(MAKE) -C ../solution/{solution_number} solution.o\
"""

CLEAN_SOLUTION_TEMPLATE = """\
\t$(MAKE) -C ../solution/{solution_number} clean\
"""

BUILD_COLLATION_TEMPLATE = """\
collation: main.o {solution_list} mathlib.a
\t$(CC) $(LDFLAGS) main.o {solution_object_list} -o collation.out -l:mathlib.a\
"""

MAKEFILE_TEMPLATE = """\
CC=gcc
LD=gcc

CC_INCLUDE=..
LD_INCLUDE=../mathlib/lib

CFLAGS=-I$(CC_INCLUDE) -pedantic -std=c90 -g -c -Wall
LDFLAGS=-L$(LD_INCLUDE)

{build_collation_step}

main.o: main.c
\t$(CC) $(CFLAGS) main.c -o main.o

{build_solution_steps}

mathlib.a: ../mathlib/src/* ../mathlib/include/*
\t$(MAKE) -C ../mathlib/make

clean:
\trm -rf *.o collation.out
\t$(MAKE) -C ../mathlib/make clean
{clean_solution_steps}
"""

def main(solution_numbers):

    # Makefile stuff
    solution_list = []
    solution_object_list = []
    build_solution_steps = []
    clean_solution_steps = []

    # main.c stuff
    c_idx = 0
    extern_solutions   = []
    soln_array_entries = []

    num_solutions = len(solution_numbers)

    for solnum in solution_numbers:
        # Makefile stuff
        solution_number = (SOLUTION_FORMAT % solnum)
        solution_object = SOLUTION_OBJECT_TEMPLATE.format(solution_number=solution_number)
        build_solution_step = BUILD_SOLUTION_TEMPLATE.format(solution_number=solution_number)
        clean_solution_step = CLEAN_SOLUTION_TEMPLATE.format(solution_number=solution_number)

        solution_list.append("solution" + solution_number)
        solution_object_list.append(solution_object)
        build_solution_steps.append(build_solution_step)
        clean_solution_steps.append(clean_solution_step)

        # main.c stuff
        extern_solutions.append(
            mainc.EXTERN_SOLUTION_TEMPLATE.format(
                five_digit_problem_number=solution_number,
                )
            )

        soln_array_entries.append(
            mainc.SOLN_ARRAY_ENTRY_TEMPLATE.format(
                soln_num=c_idx,
                five_digit_problem_number=solution_number,
                )
            )

        c_idx += 1

    build_collation_step = \
        BUILD_COLLATION_TEMPLATE.format(
            solution_list=' '.join(solution_list),
            solution_object_list=' '.join(solution_object_list),
            )

    # Construct makefile contents
    makefile = \
        MAKEFILE_TEMPLATE.format(
            build_collation_step=build_collation_step,
            build_solution_steps='\n'.join(build_solution_steps),
            clean_solution_steps='\n'.join(clean_solution_steps),
            )

    with open(os.path.join(HERE,'Makefile'),'w+') as fp:
        fp.write(makefile)

    # Construnct main.c contents
    main_c = \
        mainc.MAIN_C_TEMPLATE.format(
            num_solutions=num_solutions,
            extern_solutions='\n'.join(extern_solutions),
            soln_array_entries='\n'.join(soln_array_entries),
            )

    with open(os.path.join(HERE,'main.c'),'w+') as fp:
        fp.write(main_c)


if __name__ == '__main__':
    main(range(1,16))
