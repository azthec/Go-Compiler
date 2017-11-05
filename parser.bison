//Tokens
%token FMAIN LBRACKET RBRACKET 
%token INT VARIABLE TRUE FALSE
%token IF ELSE ELSEIF FOR
%token LPARENTH RPARENTH DOTCOMA
%token SPRINT SSCAN

// Operator associativity & precedence
%left SUM SUB MUL DIV MODUL
%left GT LT GET LET DIF COMP AND OR NOT ATRIB

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union{
	int INT;
	char* identifier;
	Expr* expr;
	Command* cmd;
	CommandList* cmdLst;
}

%type<INT> INT
%type<identifier> VARIABLE
%type<expr> Expr
%type<expr> BoolExpr
%type<cmd> cmd
%type<cmd> ifs
%type<cmd> atrib
%type<cmdLst> CommandList

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires{
    #include <stdio.h>
    #include <stdlib.h>
    #include "ast.h"
    extern int yylex();
    extern int yyline;
    extern char* yytext;
    extern FILE* yyin;
    extern void yyerror(const char* msg);
    CommandList* root;
}

%%

program: FMAIN LBRACKET CommandList RBRACKET {root = $3;}
	;

CommandList:
	cmd 				{$$ = ast_CommandList($1,NULL);}
	| cmd CommandList 	{$$ = ast_CommandList($1,$2);}
	;

cmd:  atrib
    | IF BoolExpr LBRACKET CommandList ifs                           {$$ = ast_ifs($2,$4,$5);}
    | FOR BoolExpr LBRACKET CommandList RBRACKET                     {$$ = ast_while($2,$4);}
    | SPRINT Expr RPARENTH DOTCOMA                                   {$$ = ast_disp($2);}
    | SSCAN VARIABLE RPARENTH DOTCOMA                                {$$ = ast_inp($2);}
    | FOR atrib BoolExpr DOTCOMA Expr LBRACKET CommandList RBRACKET  {$$ = ast_for($2,$3,$5,$7);}
    ;

atrib: VARIABLE ATRIB Expr DOTCOMA     {$$ = ast_atrib($1,$3);}
    ;

ifs: RBRACKET ELSEIF BoolExpr LBRACKET CommandList ifs    { $$ = ast_ifs($3, $5, $6); }
    | RBRACKET ELSE LBRACKET CommandList RBRACKET         { $$ = ast_elses($4); }
    | RBRACKET                                            { $$ = NULL; }
    ;

Expr: 
    INT                         {$$ = ast_integer($1);}
    | VARIABLE                  {$$ = ast_variable($1);}
    | LPARENTH Expr RPARENTH    {$$ = $2;}
    | Expr SUM Expr             {$$ = ast_operation($1,SUM,$3);} 
    | Expr SUB Expr             {$$ = ast_operation($1,SUB,$3);}
    | Expr MUL Expr             {$$ = ast_operation($1,MUL,$3);}
    | Expr DIV Expr             {$$ = ast_operation($1,DIV,$3);}
    | Expr MODUL Expr           {$$ = ast_operation($1,MODUL,$3);}
    ;

BoolExpr:
    TRUE                          {$$ = ast_integer(1);}
    | FALSE                       {$$ = ast_integer(0);}
    | LPARENTH BoolExpr RPARENTH  {$$ = $2;}
    | Expr GET Expr               {$$ = ast_operation($1,GET,$3);}
    | Expr LET Expr               {$$ = ast_operation($1,LET,$3);}
    | Expr LT Expr                {$$ = ast_operation($1,LT,$3);}
    | Expr GT Expr                {$$ = ast_operation($1,GT,$3);}
    | Expr DIF Expr               {$$ = ast_operation($1,DIF,$3);}
    | Expr COMP Expr              {$$ = ast_operation($1,COMP,$3);}
    | BoolExpr DIF BoolExpr       {$$ = ast_operation($1,DIF,$3);}
    | BoolExpr COMP BoolExpr      {$$ = ast_operation($1,COMP,$3);}
    | BoolExpr AND BoolExpr       {$$ = ast_operation($1,AND,$3);}
    | BoolExpr OR BoolExpr        {$$ = ast_operation($1,OR,$3);}
    | NOT BoolExpr                {$$ = ast_operation($2,NOT,$2);}
    ;

%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
