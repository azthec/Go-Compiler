#ifndef __tac_h__
#define __tac_h__
#define VARSIZE 64

typedef struct _Address Address;
typedef struct _Codline Codline;
typedef struct _ListCL ListCL;
typedef struct _Pair Pair;


typedef enum {
    EMPTY, INT, VAR
} AddressKind;

typedef enum { 
    TAC_SUM, TAC_SUB, TAC_MUL, TAC_DIV, TAC_MODUL,
    TAC_GT, TAC_LT, TAC_GET, TAC_LET, TAC_DIF, TAC_COMP,
    TAC_AND, TAC_OR, TAC_NOT, 
    TAC_ATRIB, TAC_TRUE, TAC_FALSE,
    TAC_SPRINT, TAC_SSCAN,
    TAC_IF, TAC_GOTO, TAC_LABEL,
    TAC_SW, TAC_LI, TAC_LW
 } OpKind;

//typedef for address structure
struct _Address {
    AddressKind operator;
    union {
        int value;
        char* var;
    } content;
};

struct _Codline{
  Opkind op;
  struct Adress* addr1,* addr2,* addr3;
};

struct _ListCL { 
  struct Codline * line;
  struct ListCL* next;
};

struct _Pair{
  struct Adress* address;
  struct ListCL * list;
};


Address* tac_empty();
Address* tac_integer(int a);
Address* tac_variable(char* c);
Codline* tac_expr(OpKind op, Address* t0, Address* t1, Address* t2);
ListCL* tac_list(Codline* node, ListCL* list);
ListCL* tac_append(Codline* list1, Codline* list2);
Pair* tac_pair(Address* addr, ListCL* list);

/*
TODO

Pair* CompileExpr(Expr* e);
IList* CompileCom(Command* c);
IList* CompileIfs(Command* c,char* E);
IList* compile_tac(CommandList* root, char** vars);
*/
#endif