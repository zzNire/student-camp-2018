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
    SymbolTable(SymbolTable *p)
    {
        prev = p;
    }
    ~SymbolTable() {}
    bool LookupSymbol(string name);
    void InsertSymbol(idNode *node);
    /*put和get表示变量的插入和查找*/
    void put(string s, idNode *);
    idNode *get(string s);
    
    SymbolTable *getPrev()
    {
        return prev;
    }
    idNode *operator[](string str);
    map<string, bool> firstScanFuncTable;
    map<string, bool> firstScanCompTable;

  private:
    SymbolTable *prev;
    map<string, idNode *> table;
    map<string, list<idNode *>> idTable;
   
};

extern SymbolTable sym_table;
#endif
