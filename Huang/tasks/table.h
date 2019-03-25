#ifndef _TABLE_H_
#define _TABLE_H_
#include <iostream>
#include <map>
#include <list>
#include "node.h"

using namespace std;

void EnterScope(void);
void ExitScope(void);

class SymbolTable
{
  public:
    SymbolTable() {}
   
    ~SymbolTable() {}
   
    /*put和get表示变量的插入和查找*/
    bool put(string s, idNode *);
    idNode *get(string s);
    
   


  private:
   
    map<string, idNode *> table;
   
   
};

extern SymbolTable sym_table;
#endif
