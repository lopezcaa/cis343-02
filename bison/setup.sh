#! /bin/bash

if( $1 == "run" ) {
    bison -d calc.y

    flex calc.l

    gcc calc.tab.c lexy.yy.c -o calc -lfl -lm
}

if( $1 == "clean" ) {
    rm calc.tab.c
    rm calc.tab.h
    rm lexy.yy.c
}