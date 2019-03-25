
%x COMMENT

%{
    #include <iostream>
    #include "node.h"
    #include "table.h"
    #include "parser.tab.h"
    using namespace std;


    /*ADD,SUB,MAL,DIV,
    AND,OR,NOT,
    OP,CP,
    NUMBER,
    EOL*/

%}



letter [A-Za-z]
id ([a-zA-Z_][0-9a-zA-Z_]*)
digit [0-9]
integer ([1-9][0-9]*)|([0=9])
float {digit}+(\.{digit}+)?([eE][+-]?{digit}+)?

%option noyywrap
%option yylineno

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
"=" {return EQU;}
";" {return ';';}
"," {return ',';}
double      { return DOUBLE; } 
long        { return LONG; }

{integer} {
    yylval.num = stoll(yytext,0,0);
    return INTEGER;}
{float} {
    yylval.doubleNum = strtod(yytext,0);
    return FLOAT;
}    
{id} {
    
     yylval.str = new string(yytext);
     return ID;
}
[ \t] {}
\n {return EOL;}
. { printf("无效的输入字符");}
"//".* {}    
"/*" {BEGIN COMMENT;}
<COMMENT>"*/" {BEGIN INITIAL;}
<COMMENT>. {}

%%
