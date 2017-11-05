// AST definitions
#ifndef __ast_h__
#define __ast_h__
#define VARSIZE 64

typedef struct _Expr Expr;
typedef struct _Command Command;
typedef struct _CommandList CommandList;

// AST for expressions
struct _Expr {
  enum { 
    E_INTEGER,
    E_IDENTIF,
    E_OPERATION
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


// for commands
struct _Command{
    enum{
        CMD_ATRIB, CMD_IFS, CMD_ELSES, CMD_WHILE, CMD_FOR, CMD_DIS, CMD_INP
    } type;
    union{
        char identifier[VARSIZE];
        Expr* condition;
        CommandList* elses;
        struct {
            Expr* e;
            CommandList* list;
            struct _Command* elses;
        } ifs;
        struct{
            Expr* condition;
            CommandList* commands;
        } while_exp;
        struct{
            Command* left;
            Expr* right;
            Expr* increment;
            CommandList* commands;
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


// List for commands
struct _CommandList{
    Command* cmd;
    CommandList* next;
};


// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_variable(char* identifier);
Expr* ast_operation(Expr* left, int operator, Expr* right);
Command* ast_atrib(char* identifier, Expr* e);
Command* ast_ifs(Expr* e, CommandList* list, Command* elses);
Command* ast_elses(CommandList* elses);
Command* ast_while(Expr* condition, CommandList* commands); 
Command* ast_for(Command* atrib, Expr* condition, Expr* increment, CommandList* commands);
Command* ast_disp(Expr* e);
Command* ast_inp(char* identifier);
CommandList* ast_CommandList(Command* cmd,CommandList* next);

#endif