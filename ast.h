// AST definitions
#ifndef __ast_h__
#define __ast_h__

#define VARSIZE 64

//Typedefs para identificar tudo
typedef struct _Expr Expr;
typedef struct _Command Command;
typedef struct _CommandList CommandList;

Expr* ast_integer(int v);
Expr* ast_variable(char* identifier);
Expr* ast_operation(Expr* left, int operator, Expr* right);
Command* ast_atrib(char* identifier, Expr* e);
Command* ast_ifs(Expr* e, CommandList* list, Command* elses);
Command* ast_elses(CommandList* liste);
Command* ast_while(Expr* condition, CommandList* content); 
Command* ast_for(Command* left, Expr* right, Expr* increment, CommandList* content);
Command* ast_disp(Expr* toShow);
Command* ast_inp(char* identifier);
CommandList* ast_CommandList(Command* cmd,CommandList* next);


//Estrutura para programa

struct _CommandList{
    Command* cmd;
    CommandList* next;
};

//estrutura para expressão aritmética
struct _Expr {
  enum { 
    E_INTEGER,
    E_IDENTIF,
    E_OPERATION,
  } type;
  union {
    int value; // for integer values
    char string[VARSIZE];
    struct { 
      int operator; // PLUS, MINUS, etc 
      Expr* left;
      Expr* right;
    } op; // for binary expressions
  } c;
};

//estrutura para comando
struct _Command{
    enum{
        CMD_ATRIB, CMD_IFS, CMD_ELSES, CMD_WHILE, CMD_FOR, CMD_DIS, CMD_INP
    } type;
    union{
        char identifier[VARSIZE]; // input
        Expr* condition;
        CommandList* liste;             // CommandList do else
        struct { // if ifs
            Expr* e;                    // expr do if
            CommandList* list;              // CommandList do if
            struct _Command* elses;     // elseifs
        } ifs;
        struct{
            Expr* condition;
            CommandList* content;
        } while_exp;
        struct{
            Command* left;
            Expr* right;
            Expr* increment;
            CommandList* content;
        } for_exp;
        struct{
            char identifier[VARSIZE];
            Expr* e;
        } attrib;
        struct{
            char identifier[VARSIZE];
        } input;
    } c;
};

#endif