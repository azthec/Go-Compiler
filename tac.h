#ifndef __tac_h__
#define __tac_h__

typedef enum {
    Empty, Int, Var
} AddressKind;

//typedef for address structure
struct _Address {
    AddressKind operator;
    union {
        int value;
        char* var;
    } content;
};

typedef enum { 
    TAC_SUM, TAC_SUB, TAC_MUL, TAC_DIV, TAC_MODUL,
    TAC_GT, TAC_LT, TAC_GET, TAC_LET, TAC_DIF, TAC_COMP,
    TAC_AND, TAC_OR, TAC_NOT, 
    TAC_ATRIB, TAC_TRUE, TAC_FALSE,
    TAC_SPRINT, TAC_SSCAN,
    TAC_IF, TAC_GOTO, TAC_LABEL,
    TAC_SW, TAC_LI, TAC_LW
 } OpKind;



struct _Codline{
  OpKind op;
  struct _Address* addr1,* addr2,* addr3;
};

struct _ListCL { 
  struct _Codline * line;
  struct _ListCL* next;
};

struct _Pair{
  struct _Address* address;
  struct _ListCL * list;
};

typedef struct _Address Address;
typedef struct _Codline Codline;
typedef struct _ListCL ListCL;
typedef struct _Pair Pair;

//tac structure and operations
Address* tac_empty();
Address* tac_integer(int a);
Address* tac_variable(char* c);
Codline* tac_expr(OpKind op, Address* t0, Address* t1, Address* t2);
ListCL* tac_list(Codline* node, ListCL* list);
ListCL* tac_append(ListCL* list1, ListCL* list2);
Pair* tac_pair(Address* addr, ListCL* list);

//compilation functions
Pair* compile_exp(Expr* expr);
ListCL* compile_if(Command* cmd, char* endif);
ListCL* compile_cmd(Command* cmd);

//begin compiling
ListCL* compile_tac(CommandList* root, char** varsin);

#endif