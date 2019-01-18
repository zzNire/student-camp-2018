%{
    #define YYSTYPE double
    #include "parser.tab.h"
    #include <stdlib.h>
    /*ADD,SUB,MAL,DIV,
    AND,OR,NOT,
    OP,CP,
    NUMBER,
    EOL*/
%}

digit [0-9]
number {digit}+(\.{digit}+)?(E[+-]{digit}+)?

%option noyywrap
%%
"+" {return ADD;}
"-" {return SUB;}
"*" {return MUL;}
"/" {return DIV;}
"&&" {return AND;}
"||" {return OR;}
"!" {return NOT;}
"(" {return OP;}
")" {return CP;}
{number} {
    yylval = atof(yytext);
    return NUMBER;}
[ \t] {}
\n {return EOL;}
.  yyerror("无效的输入字符");

%%
