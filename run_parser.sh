#!/usr/bin/env bash
set -euo pipefail

bison -d parser.y
flex contador.l
gcc -o parser parser.tab.c lex.yy.c -lfl

if [[ $# -gt 0 ]]; then
    if [[ -f "$1" ]]; then
        ./parser < "$1"
    else
        printf '%s\n' "$*" | ./parser
    fi
elif [[ ! -t 0 ]]; then
    ./parser
else
    echo "Parser compilado em ./parser"
    echo "Uso:"
    echo "  ./run_parser.sh 'a+b'"
    echo "  ./run_parser.sh examples/input.txt"
    echo "  echo 'a+b' | ./run_parser.sh"
fi
