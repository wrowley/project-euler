#!/usr/bin/python

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

    solution_list = []
    solution_object_list = []
    build_solution_steps = []
    clean_solution_steps = []


    for solnum in solution_numbers:
        solution_number = (SOLUTION_FORMAT % solnum)
        solution_object = SOLUTION_OBJECT_TEMPLATE.format(solution_number=solution_number)
        build_solution_step = BUILD_SOLUTION_TEMPLATE.format(solution_number=solution_number)
        clean_solution_step = CLEAN_SOLUTION_TEMPLATE.format(solution_number=solution_number)

        solution_list.append("solution" + solution_number)
        solution_object_list.append(solution_object)
        build_solution_steps.append(build_solution_step)
        clean_solution_steps.append(clean_solution_step)


    build_collation_step = \
        BUILD_COLLATION_TEMPLATE.format(
            solution_list=' '.join(solution_list),
            solution_object_list=' '.join(solution_object_list),
            )

    makefile = \
        MAKEFILE_TEMPLATE.format(
            build_collation_step=build_collation_step,
            build_solution_steps='\n'.join(build_solution_steps),
            clean_solution_steps='\n'.join(clean_solution_steps),
            )
    print makefile


if __name__ == '__main__':
    main(range(1,9))
