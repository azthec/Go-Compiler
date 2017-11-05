// AST definitions
#ifndef __ast_h__
#define __ast_h__

#define VARSIZE 1024

//Typedefs para identificar tudo
typedef struct _Expr Expr;
typedef struct _Command Command;
typedef struct _CommandSeq CommandSeq;

Expr* ast_integer(int v);
Expr* ast_variable(char* identificador);
Expr* ast_operation(Expr* left, int operator, Expr* right);
Expr* ast_input();
Command* ast_atrib(char* identifier, Expr* e);
Command* ast_ifs(Expr* e, CommandSeq* list, Command* elses);
Command* ast_elses(CommandSeq* liste);
Command* ast_while(Expr* condition, CommandSeq* content); 
Command* ast_for(Command* left, Expr* right, Expr* increment, CommandSeq* content);
//Command* ast_input(char* identifier);
Command* ast_disp(Expr* toShow);
CommandSeq* ast_CommandSeq(Command* cmd,CommandSeq* next);


//Estrutura para programa

struct _CommandSeq{
	Command* cmd;
	CommandSeq* next;
};

//estrutura para expressão aritmética
struct _Expr {
  enum { 
    E_INTEGER,
    E_IDENTIF,
  	E_OPERATION,
  	E_INP //novo
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
		CommandSeq* liste;             // CommandSeq do else
		struct { // if ifs
      		Expr* e;                    // expr do if
      		CommandSeq* list;              // CommandSeq do if
      		struct _Command* elses;     // elseifs
    	} ifs;
		struct{
			Expr* condition;
			CommandSeq* content;
		} while_exp;
		struct{
			Command* left;
			Expr* right;
            Expr* increment;
			CommandSeq* content;
		} for_exp;
		struct{
			char identifier[VARSIZE];
			Expr* e;
		} attrib;
	} c;
};

#endif