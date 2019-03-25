#include "table.h"

bool SymbolTable::put(string s, idNode *id)
{
    auto iter = table.find(s);
    if (iter == table.end())
    {
         table.insert((make_pair(s, id)));
         return true;
    }else{
        return false;
    }
   
}

idNode *SymbolTable::get(string s)
{
        auto found = table.find(s);
        if (found != table.end())
            return found->second;
        else
        {
             return NULL;
        }
}



/*
long a = 1;
a+2;
*/
