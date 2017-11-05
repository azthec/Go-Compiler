#include <stdlib.h> // for malloc
#include <string.h> // memcpy
#include "ast.h" // AST header

// Operação para inteiro
Expr* ast_integer(int v) {
  Expr* node = (Expr*)malloc(sizeof(Expr));
  node->type = E_INTEGER;
  node->c.value = v;
  return node;
}

Expr* ast_variable(char* id){
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->type = E_IDENTIF;
  memcpy(node->c.string, id, VARSIZE);
  return node;
}

Expr* ast_input(){
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->type = E_INP;
  return node;
}

//Operação para operações(soma,subtração,multiplicação e divisão)
Expr* ast_operation(Expr* left, int operator, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->type = E_OPERATION;
  node->c.op.operator = operator;
  node->c.op.left = left;
  node->c.op.right = right;
  return node;
}

//Atribuição
Command* ast_atrib(char* id,Expr* e){
    Command* node = (Command*) malloc(sizeof(Command));
    node->type = CMD_ATRIB;
    memcpy(node->c.attrib.identifier, id, VARSIZE);
    node->c.attrib.e = e;
    return node;
}

Command* ast_while(Expr* condition,CommandSeq* content){
    Command* node = (Command*) malloc(sizeof(Command));
    node->type = CMD_WHILE;
    node->c.while_exp.condition = condition;
    node->c.while_exp.content = content;
    return node;
}

Command* ast_for(Command* left, Expr* right, Expr* increment, CommandSeq* content){
  Command* node = (Command*) malloc(sizeof(Command));
  node->type = CMD_FOR;
  node->c.for_exp.right = right;
  node->c.for_exp.left = left;
  node->c.for_exp.increment = increment;
  node->c.for_exp.content = content;
  return node;
}

Command* ast_ifs (Expr* e, CommandSeq* list, Command* elses) {
  Command* node =  (Command*) malloc(sizeof(Command));
  node->type = CMD_IFS;
  node->c.ifs.e = e;
  node->c.ifs.list = list;
  node->c.ifs.elses = elses;  
  return node;
}

Command* ast_elses (CommandSeq* elses) {
  Command* node = (Command*) malloc(sizeof(Command));
  node->type = CMD_ELSES;
  node->c.liste = elses;  
  return node;
}

Command* ast_disp(Expr* toShow){
    Command* node = (Command*) malloc(sizeof(Expr));
    node->type = CMD_DIS;
    node->c.condition = toShow;
    return node;
}

Command* ast_inp(char* id){
    Command* node = (Command*) malloc(sizeof(Command));
    node->type = CMD_INP;
    memcpy(node->c.input.identifier, id, VARSIZE);
    return node;
}

CommandSeq* ast_CommandSeq(Command* cmd,CommandSeq* next) {
  CommandSeq* node = (CommandSeq*) malloc(sizeof(CommandSeq));
  node->cmd = cmd;
  node-> next= next;
}