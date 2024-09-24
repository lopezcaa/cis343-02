%{
#include <stdio.h>


%}

%%

[0-9]+          {printf("INT");}
[0-9]*\.[0-9]+  {printf("FLOAT");}



%%

int main(int argc, char** argv) {
    yylex();

    return 0;
}