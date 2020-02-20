#!/bin/bash

# @Author: AnthonyKenny98
# @Date:   2019-10-30 16:22:45
# @Last Modified by:   AnthonyKenny98
# @Last Modified time: 2020-02-19 23:04:19

### Constants

# List of project files
PROJECTS=(\
    1_Proposal \
    2_TechnicalSpecifications \
    3_Design \
    4_Report \
)

### GLOBAL VARS
projectName=""

### Functions

usage() {
    echo "usage: ./make.sh [ [[-p | --project ] ] | [-c | --clean] | [-h | --help]]"
}

all() {
    func=$1
    for PROJECT in ${PROJECTS[@]};
    do
        cd $PROJECT
        $func
        cd ..
    done
}

run_clean() { 
    make clean 
}

run_make() { 
    make 
}

project() {
    func=$1
    project=${PROJECTS[$2-1]}
    case $project in 
        "")     echo "No Project"
                exit
                ;;
        *)      cd $project
                $func
                cd ..
                ;;
    esac
}

### MAIN


# Loop until all parameters are used up
while [ "$1" != "" ]; do
    case $1 in
        # Options
        -a | -all)              shift
                                all run_make
                                ;;
        -c | --clean)           shift
                                all run_clean
                                ;;
        -h | --help )           usage
                                exit
                                ;;
        # Parameters
        -p | --project )        shift
                                project run_make $1
                                ;;
        * )                     usage
                                exit 1
    esac
    shift
done