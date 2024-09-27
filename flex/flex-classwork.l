%{
#include <stdio.h>


%}

%%

[0-9]+          {printf("INT");} //int
[0-9]*\.[0-9]+  {printf("FLOAT");} //float

[mM]{1}[oO]{1}[nN]{1}[dD]{1}[aA]{1}[yY]{1}                      {printf("VALIDDAY");} //moneday
[tT]{1}[uU]{1}[eE]{1}[sS]{1}[dD]{1}[aA]{1}[yY]{1}               {printf("VALIDDAY");} //tuesday
[wW]{1}[eE]{1}[dD]{1}[nN]{1}[eE]{1}[sS]{1}[dD]{1}[aA]{1}[yY]{1} {printf("VALIDDAY");} //wednesday
[tT]{1}[hH]{1}[uU]{1}[rR]{1}[sS]{1}[dD]{1}[aA]{1}[yY]{1}        {printf("VALIDDAY");} //thursday
[fF]{1}[rR]{1}[iI]{1}[dD]{1}[aA]{1}[yY]{1}                      {printf("VALIDDAY");} //friday
[sS]{1}[aA]{1}[tT]{1}[uU]{1}[rR]{1}[dD]{1}[aA]{1}[yY]{1}        {printf("VALIDDAY");} //saturday
[sS]{1}[uU]{1}[nN]{1}[dD]{1}[aA]{1}[yY]{1}                      {printf("VALIDDAY");} //sunday

[a-zA-Z0-9]+@[a-zA-Z0-9]+.{1}[cC]{1}[oO]{1}[mM]{1}   {printf("EMAIL");} //.com
[a-zA-Z0-9]+@[a-zA-Z0-9]+.{1}[oO]{1}[rR]{1}[gG]{1}   {printf("EMAIL");} //.org
[a-zA-Z0-9]+@[a-zA-Z0-9]+.{1}[eE]{1}[dD]{1}[uU]{1}   {printf("EMAIL");} //.edu

%%

int main(int argc, char** argv) {
    yylex();

    return 0;
}