#include <stdlib.h> // for malloc
#include "ast.h" // AST header
#include <string.h> // for memcpy


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


Expr* ast_operation(Expr* left, int operator, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->type = E_OPERATION;
  node->c.op.operator = operator;
  node->c.op.left = left;
  node->c.op.right = right;
  return node;
}


Command* ast_atrib(char* id,Expr* e){
    Command* node = (Command*) malloc(sizeof(Command));
    node->type = CMD_ATRIB;
    memcpy(node->c.attrib.identifier, id, VARSIZE);
    node->c.attrib.e = e;
    return node;
}


Command* ast_while(Expr* condition,CommandList* commands){
    Command* node = (Command*) malloc(sizeof(Command));
    node->type = CMD_WHILE;
    node->c.while_exp.condition = condition;
    node->c.while_exp.commands = commands;
    return node;
}


Command* ast_for(Command* atrib, Expr* condition, Expr* increment, CommandList* commands){
  Command* node = (Command*) malloc(sizeof(Command));
  node->type = CMD_FOR;
  node->c.for_exp.right = condition;
  node->c.for_exp.left = atrib;
  node->c.for_exp.increment = increment;
  node->c.for_exp.commands = commands;
  return node;
}


Command* ast_ifs (Expr* e, CommandList* list, Command* elses) {
  Command* node =  (Command*) malloc(sizeof(Command));
  node->type = CMD_IFS;
  node->c.ifs.e = e;
  node->c.ifs.list = list;
  node->c.ifs.elses = elses;  
  return node;
}


Command* ast_elses (CommandList* elses) {
  Command* node = (Command*) malloc(sizeof(Command));
  node->type = CMD_ELSES;
  node->c.elses = elses;  
  return node;
}


Command* ast_disp(Expr* e){
    Command* node = (Command*) malloc(sizeof(Expr));
    node->type = CMD_DIS;
    node->c.condition = e;
    return node;
}


Command* ast_inp(char* id){
    Command* node = (Command*) malloc(sizeof(Command));
    node->type = CMD_INP;
    memcpy(node->c.input.identifier, id, VARSIZE);
    return node;
}


CommandList* ast_CommandList(Command* cmd,CommandList* next) {
  CommandList* node = (CommandList*) malloc(sizeof(CommandList));
  node->cmd = cmd;
  node-> next= next;
}