#! /bin/bash

if [ "$1" == "run" ]; then
    bison -d calc.y
    flex calc.l
    gcc calc.tab.c lex.yy.c -o calc -lfl -lm

elif [ "$1" == "clean" ]; then
    rm -f calc.tab.c
    rm -f calc.tab.h
    rm -f lex.yy.c
    rm -f calc
fi
