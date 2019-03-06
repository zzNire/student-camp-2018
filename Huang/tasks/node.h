#ifndef _NODE_H_
#define _NODE_H_

#include <stdio.h>
#include <string>
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
                result = ! exp->llval;
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
                result = ! exp->dval;
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