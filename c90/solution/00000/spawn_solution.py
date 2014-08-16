#!/usr/bin/python

import sys
import shutil
import os
import argparse

HERE         = os.path.abspath(os.path.dirname(__file__))
ROOT_DIR     = os.path.abspath(os.path.join(HERE, '..'))
TEMPLATE_DIR = os.path.abspath(os.path.join(HERE, 'template'))

def make_path(path):
    if not os.path.exists(path):
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

def main(solution_num, force, makefiles_only):
    solution_name = "%05d" % solution_num
    solution_dir  = os.path.join(ROOT_DIR, solution_name)

    if (os.path.exists(solution_dir) and not force) and not makefiles_only:
        print ("%s exists, won't override files" % solution_dir)
        return

    make_path(solution_dir)

    substitutions = {
        'SOLUTION_FUNCTION_NAME' : 'problem' + solution_name,
    }

    # Populate directory
    templates = {
        'Makefile'            : 'Makefile'   ,
        'main.c.template'     : 'main.c'     ,
    }
    if not makefiles_only:
        templates.update({
            'solution.c.template' : 'solution.c' ,
        }
    )
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
    parser.add_argument(
        "--force",
        "-f",
        action="store_true",
        help="Force the rollout of a solution template, even if the directory exists",
        )
    parser.add_argument(
        "--dont-wipe-solution",
        "-m",
        action="store_true",
        default=False,
        help="Only update the Makefile and main.c of each solution",
        )

    (args) = parser.parse_args(sys.argv[1:])

    main(args.solution_num, args.force, args.dont_wipe_solution)
