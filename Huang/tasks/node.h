#ifndef _NODE_H_
#define _NODE_H_

#include <stdio.h>
#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include "NodeType.h"

using namespace std;




class constantNode;
class Node 
{
    public:
        NodeType type;
        
    Node()
    {
       
    }
    ~Node()
    {
       
    }
    virtual void print() = 0;
    virtual constantNode* toString() = 0;
};
class constantNode : public Node{
    public:
        string valueType;
        double dval;
        long  llval;
        constantNode(string type, long  l) : valueType(type), llval(l)
        { 
            this->type = constant;
            //printf("%ld",l);
        }
        constantNode(string type, double d) : valueType(type), dval(d)
        {   
            this->type = constant;
           // printf("%lf",d);
        }
        ~constantNode() {}
        constantNode *toString(){
            return 0;
        }
        
        void print(){
            if(this->valueType.compare("INTEGER")==0){
                printf("%ld\n",llval);
            }
            else if(this->valueType.compare("FLOAT")==0){
                printf("%lf\n",dval);
            }
        }
};

class idNode : public Node
{
  public:
    string name;
    string valType;
    list<Node *> arg_list;
    Node *init;
    int level;
    int version;
    int isArray;  //是否为数组, 主要用于 int a[] 这种 arg_list 为空的场景
    int isStream; //是否为 Stream 复杂类型.后续待处理
    int isParam;  //是否为function 或 composite 的输入参数
    idNode(string name) : name(name), isArray(0), isStream(0), isParam(0)
    {
        this->type = Id;
       // this->level = Level;
        //this->version = current_version[Level];
        //this->valType = "int";
       
    }
    idNode(string *name)
    {
        new (this) idNode(*name);
    }
    ~idNode() {}
    void print() {}
    constantNode* toString(){
        return dynamic_cast<constantNode*>(init);
        
    }
};

class primNode : public Node
{
  public:
    string name;
    bool isConst;
    primNode(string str) : name(str), isConst(false)
    {
        this->type = primary;
       
    }
    ~primNode() {}
    void print() { cout << "primNodeType :" << name << endl; }
    constantNode* toString(){
        return 0;
    }
};



class declareNode : public Node
{
  public:
    primNode *prim;
    list<idNode *> id_list;
    declareNode(primNode *prim, idNode *id)
    {
        
        this->type = Decl;
        this->prim = prim;
        if (id)
            this->id_list.push_back(id);
    }
    ~declareNode() {}
    void print() {}
    constantNode* toString() {
        printf("%s",prim->name.data());
        list<idNode *>::iterator  var_iterator;
        for(var_iterator = id_list.begin();var_iterator!=id_list.end();var_iterator++){
            idNode* right_node =  *var_iterator;
            printf("%s",right_node->name.data());
            constantNode* value = dynamic_cast<constantNode*>(right_node->init);
            if(value->valueType.compare("INTEGER")==0 ){
                printf("%ld",value->llval);
            }
            else{
                printf("lf",value->dval);
            }
        }
        printf("\n");
        return 0;
    }
};

class funcBodyNode : public Node
{
  public:
    list<Node *> *stmt_list;
    funcBodyNode(list<Node *> *stmt_list)
    {
        this->stmt_list = stmt_list;
    }
    ~funcBodyNode() {}
    void print() {}
    constantNode* toString() {
        return 0;
    }
};

class binopNode : public Node
{
  public:
    constantNode *left;
    constantNode *right;
    string op;
    binopNode(constantNode *left, string op, constantNode *right)
    {
       this->type = Binop;
        this->left = left;
        this->right = right;
        this->op = op;
        //printf("%s",op.data());
    }
    ~binopNode() {};
    void print() {};

    constantNode *toString(){ 
        //printf("binopNode");
        //printf("%s",left->valueType.data());
        
        if(left->valueType.compare("INTEGER") == 0 && right->valueType.compare("INTEGER") == 0){
            printf("%ld %s %ld\n",left->llval ,op.data(), right->llval);
            long result = 0 ;
            if(this->op.compare("+")==0){
                result = left->llval + right->llval;
            }
            if(this->op.compare("-")==0){
                result = left->llval - right->llval;
            }
            if(this->op.compare("*")==0){
                result = left->llval * right->llval;
            }
            if(this->op.compare("/")==0){
                result = left->llval / right->llval;
            }
            if(this->op.compare("&&")==0){
                result = left->llval && right->llval;
            }
            if(this->op.compare("||")==0){
                result = left->llval || right->llval;
            }
            
         
            return new constantNode("INTEGER",result);
                
        }
        else if(left->valueType.compare("FLOAT") == 0 || right->valueType.compare("FLOAT") == 0){
            double result = 0 ;
            printf("%lf %s %lf\n",left->dval ,op.data(), right->dval);
            if(this->op.compare("+")==0){
                result = left->dval + right->dval;
            }
            if(this->op.compare("-")==0){
                result = left->dval - right->dval;
            }
            if(this->op.compare("*")==0){
                result = left->dval * right->dval;
            }
            if(this->op.compare("/")==0){
                result = left->dval / right->dval;
            }
            if(this->op.compare("&&")==0){
                result = left->dval && right->dval;
            }
            if(this->op.compare("||")==0){
                result = left->dval || right->dval;
            }
            return new constantNode("FLOAT",result);
        }
        else{
            return 0;
        }
    }
};

class unaryNode : public Node
{
  public:
    constantNode *exp;
    string op;
    unaryNode(string op, constantNode *exp)
    {
       
        this->exp = exp;
        this->op = op;
    }
    ~unaryNode() {}
    void print() {}
    constantNode* toString(){
        if(exp->valueType.compare("INTEGER")==0){
            printf("%s %ld\n",op.data(), exp->llval);
            long result = 0 ;
            if(this->op.compare("!")==0){
                result = ! (exp->llval);
            }
            if(this->op.compare("-")==0){
                result = - exp->llval;
            }
            return new constantNode("INTEGER",result);
        }
            
        else if(exp->valueType.compare("FLOAT")==0){
            double result = 0 ;
            printf("%s %lf\n ",op.data(), exp->dval);
             if(this->op.compare("!")==0){
                result = !(exp->dval);
            }
            if(this->op.compare("-")==0){
                result = - exp->dval;
            }
            return new constantNode("FLOAT",result);
        }
        else{
            return 0;
        }
    }
};


#endif