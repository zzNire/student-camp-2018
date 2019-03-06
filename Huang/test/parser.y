%{
#include <stdio.h>
#include <math.h>
#include "node.h"

extern int yylex();
extern void yyerror(const char *msg);

%}

%union
{ 
    long num;
    double doubleNum;
    Node * node;
} 

%token ADD SUB MUL DIV AND OR NOT OP CP  EOL EQU 
%token INTEGER FLOAT
%token  ID

%type<num> INTEGER 
%type<doubleNum> FLOAT 
%type<node> NUMBER expr lines 

 //先出现优先级越低
%left OR
%left AND 
%left ADD SUB
%left MUL DIV
%right NOT
%right UNIMUS   // %prec UMIMUS 该操作的优先级与UMINUS相同 UMINUS最高 所以该操作优先级最高

%% 

lines : expr EOL  {$$ = $1; }
    | lines expr EOL  {$$ = $2; }
    | lines EOL
    ;




expr : expr ADD expr    {$$ = new binopNode((constantNode*)$1,"+",(constantNode*)$3);}
    | expr SUB expr    {$$ = new binopNode((constantNode*)$1,"-",(constantNode*)$3);}
    | expr MUL expr    {$$ = new binopNode((constantNode*)$1,"*",(constantNode*)$3);}
    | expr DIV expr    {$$ = new binopNode((constantNode*)$1,"/",(constantNode*)$3);}
    | expr AND expr    {$$ = new binopNode((constantNode*)$1,"&&",(constantNode*)$3);}
    | expr OR expr     {$$ = new binopNode((constantNode*)$1,"||",(constantNode*)$3);}
    | NOT expr         {$$ = NULL; }
    | OP expr CP       {$$ = NULL; }
    | SUB expr  %prec UNIMUS       {$$ = NULL; } 
    | NUMBER {$$ = $1; }
    ;

NUMBER :  INTEGER {$$ = new constantNode("INTEGER",$1);}
    | FLOAT {$$ = new constantNode("FLOAT",$1);}
    ;
%%
void yyerror ( const char * msg) {
    printf("%s\n",msg);
}

int main(void)
{
    printf("A simple calculator.\n");
    yyparse();
    return 0;
}

