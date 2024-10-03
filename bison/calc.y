%{
#include <math.h>
#include <stdio.h>
int yylex();
extern int yylineno;
void yyerror(const char* msg);

double total = 0;
double memory_m = 0;
%}

%union {
    double fVal;
}

%define parse.error verbose
%start program

%token CLR_OP
%token EQL_OP
%token ADD_OP
%token SUB_OP
%token MUL_OP
%token DIV_OP
%token POW_OP
%token NUMBER
%token NUMZERO
%token MEM_M
%token CLR_AC
%token RECALL_R
%type<fVal> NUMBER expr

%%
program:	expr_list 
    ;
expr_list:  expr 		
	|	expr expr_list	
	;
expr:   CLR_OP              { total = 0;}
	|   EQL_OP              { printf("%f\n", total); }
	|   ADD_OP NUMBER       { total += $2; }
	| 	SUB_OP NUMBER 		{ total -= $2; }
	| 	MUL_OP NUMBER 		{ total *= $2; }
	|   DIV_OP NUMZERO		{ printf("ERROR: CAN'T DIVIDE BY ZERO\n"); }
	| 	DIV_OP NUMBER 		{ total /= $2; }
	| 	POW_OP NUMBER 		{ total = pow(total, $2);}
	|	MEM_M				{ memory_m = total; }
	|	CLR_AC				{ memory_m = 0; }
	|	ADD_OP RECALL_R		{ total += memory_m; }
	|	SUB_OP RECALL_R		{ total -= memory_m; }
	|	MUL_OP RECALL_R		{ total *= memory_m; }
	|	DIV_OP RECALL_R		{ total /= memory_m; }
	;
%%

void yyerror(const char* msg){
	fprintf(stderr, "Error on line %d.\n%s\n", yylineno, msg);
}

int main(int argc, char** argv){
	yyparse();
}
