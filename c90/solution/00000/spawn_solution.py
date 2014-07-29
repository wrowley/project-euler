#!/usr/bin/python

import sys
import shutil
import os
import argparse

HERE         = os.path.abspath(os.path.dirname(__file__))
ROOT_DIR     = os.path.abspath(os.path.join(HERE, '..'))
TEMPLATE_DIR = os.path.abspath(os.path.join(HERE, 'template'))

def make_path(path):
    print "Making dir %s" % path
    try:
        os.mkdir(path)
    except Exception as e:
        pass

def populate_solution_dir_with_file(
    src,
    dst,
    substitutions,
    ):

    # Read source file
    with open(src,'r') as fp:
        src_lines = fp.readlines()

    # Make substitutions
    if src.endswith('.template'):
        dst_lines = []
        for line in src_lines:
            for subkey,subval in substitutions.items():
                substring = '${' + subkey + '}'
                while substring in line:
                    line = line.replace(substring,subval)
            dst_lines.append(line)
    else:
        dst_lines = src_lines

    # Write out destination file
    with open(dst,'w+') as fp:
        fp.writelines(dst_lines)

def main(solution_num):
    solution_name = "%05d" % solution_num
    solution_dir  = os.path.join(ROOT_DIR, solution_name)

    make_path(solution_dir)

    substitutions = {
        'SOLUTION_FUNCTION_NAME' : 'problem' + solution_name,
    }

    # Populate directory
    templates = {
        'Makefile'            : 'Makefile'   ,
        'main.c.template'     : 'main.c'     ,
        'solution.c.template' : 'solution.c' ,
    }
    for src,dst in templates.items():
        populate_solution_dir_with_file(
            os.path.join(TEMPLATE_DIR, src),
            os.path.join(solution_dir, dst),
            substitutions,
            )

if __name__=='__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument(
        "solution_num",
        help="The solution number",
        type=int,
        )

    (args) = parser.parse_args(sys.argv[1:])

    main(args.solution_num)
