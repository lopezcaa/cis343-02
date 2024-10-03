%{
#include "calc.tab.h"
#include <stdlib.h>

// add more operators
// edit regex for floating point and integer number
%}

%option yylineno

%%
[cC]		    { return CLR_OP; }
=			    { return EQL_OP; }

\+			    { return ADD_OP; }
\-              { return SUB_OP; }
\*              { return MUL_OP; }
\/              { return DIV_OP; }
\^              { return POW_OP; }

[0-9]{1,5}      { yylval.fVal = atof(yytext); return NUMBER; } //int
[0-9]*\.[0-9]+  { yylval.fVal = atof(yytext); return NUMBER; } //float
[0]+            { return NUMZERO; }
[ \t\n\r]		

[mM]            { return MEM_M; }
[aA][cC]        { return CLR_AC; }
[rR]            { return RECALL_R; }

;
%%
