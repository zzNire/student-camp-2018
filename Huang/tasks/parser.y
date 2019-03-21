%{
#include <stdio.h>
#include <math.h>
#include "node.h"
#include "NodeType.h"
#include "table.h"


extern list<Node*> *Program; 

extern int yylex();
extern void yyerror(const char *msg);


%}

%union
{ 
    long num;
    double doubleNum;
    std::string *str;
    Node * node;
    std::list<Node*> *list;
} 

%token ADD SUB MUL DIV AND OR NOT OP CP  EOL EQU 
%token INTEGER FLOAT DOUBLE LONG
%token  ID

%type<num> INTEGER 
%type<doubleNum> FLOAT 
%type<str> ID
%type<node> NUMBER expr  

%type<list> translation.unit 
%type<node> external.definition
%type<node> declaration declaring.list
%type<node> initializer.opt initializer
%type<list> statement.list 
%type<node> statement
%type<node>type.specifier basic.type.name idNode


 //先出现优先级越低
%right EQU 
%left OR
%left AND 
%left ADD SUB
%left MUL DIV
%right NOT
%right UNIMUS   // %prec UMIMUS 该操作的优先级与UMINUS相同 UMINUS最高 所以该操作优先级最高

%start prog.start
%locations

%% 
prog.start: translation.unit {printf("start\n") ;};

translation.unit:
            external.definition EOL {
                                    printf(" external.definition\n");
                                    
                                     $$ = new list<Node*>({$1});
                                  }
        | translation.unit external.definition EOL {
                                                      $$->push_back($2);
                                                       printf(" translation.unit external.definition\n");
                                                }
        ;



external.definition:
            declaration         {
                                    printf(" declaration\n");
                                    $$ = $1;
                                }
            | statement.list    {
                                    printf(" statement.list\n");
                                    $$ = new funcBodyNode({$1});
                                    //$$ = $1;
                                }
        ;
        
statement.list:
          statement                   {   $$ = new list<Node*> ({$1});  }
        | statement.list statement    {   $$->push_back($2);            }
        ;

statement:
        expr ';' { $$ = $1; }


declaration:
      declaring.list ';'        {
                                    printf(" declaring.list\n");
                                    $$ = $1 ;
                                }

    ;
declaring.list:
          type.specifier      idNode       initializer.opt  {
            printf(" type.specifier      idNode       initializer.opt \n");
            (static_cast<idNode*>$2)->init = $3;
           // if(S[*($2)]==NULL) S.InsertSymbol(id);
            $$ = new declareNode((primNode*)$1,(static_cast<idNode*>$2)) ;
           
          }
        | declaring.list 	',' idNode        initializer.opt{
              (static_cast<idNode*>$3)->init = $4;
              //if(S[*($3)]==NULL) S.InsertSymbol(id);
              ((declareNode*)$1)->id_list.push_back((static_cast<idNode*>$3));
              $$=$1;
          }
        ;

initializer.opt:
          /* nothing */         {
                                    $$ = NULL ;
                                }
        | EQU initializer       {
                                    printf("= initializer\n");
                                    $$ = $2 ;
                                }
        ;
initializer:
        expr                           { $$ = $1 ;}
        ;


//lines : expr EOL  {$$ = $1;  $1->print(); printf("expr EOL\n");}
//    | lines expr EOL  {$$ = $2; $2->print(); printf("lines expr EOL\n");}
//    | lines EOL {printf("lines EOL\n");}
//   ;

expr: expr ADD expr   {$$ = new binopNode((constantNode*)$1,"+",(constantNode*)$3); $$ = $$->toString(); }
    | expr SUB expr    {$$ = new binopNode((constantNode*)$1,"-",(constantNode*)$3); $$ = $$->toString();}
    | expr MUL expr    {$$ = new binopNode((constantNode*)$1,"*",(constantNode*)$3); $$ = $$->toString();}
    | expr DIV expr    {$$ = new binopNode((constantNode*)$1,"/",(constantNode*)$3); $$ = $$->toString();}
    | expr AND expr    {$$ = new binopNode((constantNode*)$1,"&&",(constantNode*)$3); $$ = $$->toString();}
    | expr OR expr     {$$ = new binopNode((constantNode*)$1,"||",(constantNode*)$3); $$ = $$->toString();}
    | NOT expr         {$$ = $$ = new unaryNode("!",(constantNode*)$2); $$ = $$->toString();}
    | OP expr CP       {$$ = $2; }
    | SUB expr  %prec UNIMUS       {$$ = $$ = new unaryNode("-",(constantNode*)$2); $$ = $$->toString(); } 
    | NUMBER    {$$ = $1; }
    | idNode    {$$ = $1; $$ = $$->toString();}
    | idNode EQU expr {
                        idNode* id = static_cast<idNode*>($1);
                        bool result = sym_table.LookupSymbol(id->name);
                        if(result == true){
                        //id->init = $3;
                        }else{
                            //printf("%s is not defined",id->name.data());
                        }
        }
    ;

NUMBER:  INTEGER {$$ = new constantNode("INTEGER",$1);printf("%ld\n",$1);}
    | FLOAT {$$ = new constantNode("FLOAT",$1);}
    ;


type.specifier:
          basic.type.name       { 
              printf("basic.type.name ");
              $$ = $1 ;}
        ;


basic.type.name:
         
          LONG        { 
                        printf("long\n");
                        $$ = new primNode("long");
              }
        | DOUBLE       { $$ = new primNode("double");}
        ;

idNode:
          ID  { 
                    printf("%s\n",$1->data());
                    idNode* id = new idNode($1);
                    $$ = id;
                    sym_table.InsertSymbol(id);
            }
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

