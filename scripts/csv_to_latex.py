"""Convert CSV to Latex table format."""
# -*- coding: utf-8 -*-
# @Author: AnthonyKenny98
# @Date:   2020-02-24 15:06:14
# @Last Modified by:   AnthonyKenny98
# @Last Modified time: 2020-02-27 18:57:05

import sys
import csv


def write_line(line):
    """Write Line."""
    out = ''
    for i in range(len(line)):
        out += line[i]
        out += ' & ' if (i < len(line) - 1) else ' \\\\\n'
    return out


def main():
    """Main Function."""
    help_msg = 'Usage: csv_to_latex.py <input>.csv <path/to/output>.tex'

    # Validate arguments
    if len(sys.argv) != 3:
        print(help_msg)
        return

    # Validate input and output file names
    infile, outfile = sys.argv[1], sys.argv[2]
    if not infile.endswith('.csv') or not outfile.endswith('.tex'):
        print(help_msg)
        return

    # Open output file
    out = open(outfile, 'w')

    # Begin Table
    out.write("\\begin{center}\n\\begin{tabular}")

    # Open input file
    with open(infile, 'r') as f:

        # Open reade
        reader = csv.reader(f)

        # Write Table Options
        header = next(reader)
        out.write('{|')
        [out.write('m{' + str(0.94 / len(header)) + '\\linewidth}|')
            for h in header]
        out.write('}\n\\hline\n')

        # Write Header
        out.write(write_line(header))
        out.write("\\hline\n")

        # Loop through remaining rows
        for row in reader:
            out.write(write_line(row))
        out.write("\\hline\n")

    # End table
    out.write("\\end{tabular}\n\\end{center}")

    out.close()

if __name__ == "__main__":
    main()
