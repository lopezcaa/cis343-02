%{
#include <stdio.h>


%}

%%

[0-9]+          {printf("INT");} //int
[0-9]*\.[0-9]+  {printf("FLOAT");} //float

[m,M]{1}[o,O]{1}[n,N]{1}[d,D]{1}[a,A]{1}[y,Y]{1}                            {printf("VALIDDAY");} //moneday
[t,T]{1}[u,U]{1}[e,E]{1}[s,S]{1}[d,D]{1}[a,A]{1}[y,Y]{1}                    {printf("VALIDDAY");} //tuesday
[w,W]{1}[e,E]{1}[d,D]{1}[n,N]{1}[e,E]{1}[s,S]{1}[d,D]{1}[a,A]{1}[y,Y]{1}    {printf("VALIDDAY");} //wednesday
[t,T]{1}[h,H]{1}[u,U]{1}[r,R]{1}[s,S]{1}[d,D]{1}[a,A]{1}[y,Y]{1}            {printf("VALIDDAY");} //thursday
[f,F]{1}[r,R]{1}[i,I]{1}[d,D]{1}[a,A]{1}[y,Y]{1}                            {printf("VALIDDAY");} //friday
[s,S]{1}[a,A]{1}[t,T]{1}[u,U]{1}[r,R]{1}[d,D]{1}[a,A]{1}[y,Y]{1}            {printf("VALIDDAY");} //saturday
[s,S]{1}[u,U]{1}[n,N]{1}[d,D]{1}[a,A]{1}[y,Y]{1}                            {printf("VALIDDAY");} //sunday

[a-zA-Z0-9]+@[a-zA-Z0-9]+.{1}[c,C]{1}[o,O]{1}[m,M]{1}   {printf("EMAIL");} //.com
[a-zA-Z0-9]+@[a-zA-Z0-9]+.{1}[o,O]{1}[r,R]{1}[g,G]{1}   {printf("EMAIL");} //.org
[a-zA-Z0-9]+@[a-zA-Z0-9]+.{1}[e,E]{1}[d,D]{1}[u,U]{1}   {printf("EMAIL");} //.edu

%%

int main(int argc, char** argv) {
    yylex();

    return 0;
}