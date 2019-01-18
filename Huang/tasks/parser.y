%{
#include <stdio.h>
#include <math.h>
#define YYSTYPE double

extern int yylex();
extern void yyerror(const char *msg);
%}

%token ADD SUB MUL DIV AND OR NOT OP CP NUMBER EOL

 //先出现优先级越低
%left OR
%left AND 
%left ADD SUB
%left MUL DIV
%right NOT
%right UNIMUS   // %prec UMIMUS 该操作的优先级与UMINUS相同 UMINUS最高 所以该操作优先级最高

%% 
lines : lines expr EOL  {printf("%lf\n",$2);}
    | lines EOL
    |
    ;

expr : expr ADD expr    {$$ = $1 + $3; printf("%lf = %lf + %lf\n",$$,$1,$3);}
    | expr SUB expr    {$$ = $1 - $3;printf("%lf = %lf - %lf\n",$$,$1,$3);}
    | expr MUL expr    {$$ = $1 * $3;printf("%lf = %lf * %lf\n",$$,$1,$3);}
    | expr DIV expr    {$$ = $1 / $3;printf("%lf = %lf / %lf\n",$$,$1,$3);}
    | expr AND expr    {$$ = $1 && $3;printf("%lf = %lf && %lf\n",$$,$1,$3);}
    | expr OR expr     {$$ = $1 || $3;printf("%lf = %lf || %lf\n",$$,$1,$3);}
    | NOT expr         {$$ = ! $2; printf("%lf = !%lf\n",$$,$2);}
    | OP expr CP       {$$ = $2; printf("%lf = (%lf)\n",$$,$2);}
    | SUB expr  %prec UNIMUS       {$$ = - $2; printf("%lf = - %lf\n",$$,$2);} 
    | NUMBER
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

