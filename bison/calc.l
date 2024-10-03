%{
#include "calc.tab.h"
#include <stdlib.h>

// add more operators
// edit regex for floating point and integer number
%}

%option yylineno

%%
C			{ return CLR_OP; }
\+			{ return ADD_OP; }
=			{ return EQL_OP; }
[0]+ { return NUMZERO; }

[0-9]{1,5}		{ yylval.fVal = atof(yytext); return NUMBER; }
[ \t\n\r]		

-   { return SUB_OP; }
\*  { return MUL_OP; }
\/  { return DIV_OP; }
\^  { return POW_OP; }

[mM]        { return MEM_M; }
[aA][cC]    { return CLR_AC; }
[rR]        { return RECALL_R; }

;
%%
