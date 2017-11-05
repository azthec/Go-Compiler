%code requires{
    #include <stdio.h>
    #include <stdlib.h>
    #include "ast.h"
    extern int yylex();
    extern int yyline;
    extern char* yytext;
    extern FILE* yyin;
    extern void yyerror(const char* msg);
    CommandSeq* root;
}

%start program;

/* Tokens  */
%token NUM
%token VARIABLE
%token IF ELSE ELSEIF FOR WHILE DOTS END
%token DISP INP OB CB SEMI_COL
%token TRUE FALSE
%token FMAIN LBRACKET RBRACKET SPRINT

%left SUB SUM
%left MUL DIV
%left GT LT GET LET DIF COMP 
%left ATRIB

%union{
	int num;
	char* identificador;
	Expr* expr;
	Command* cmd;
	CommandSeq* cmdSeq;
}

%type<num> NUM
%type<identificador> VARIABLE
%type<expr> Expr
%type<cmdSeq> commandSeq
%type<cmd> cmd
%type<cmd> ifs
%type<cmd> atrib
%type<expr> lim


%%

program: FMAIN LBRACKET commandSeq RBRACKET {root = $3;}
	;

commandSeq:
	cmd 				{$$ = ast_CommandSeq($1,NULL);}
	| cmd commandSeq 	{$$ = ast_CommandSeq($1,$2);}
	;

cmd:  atrib
    | IF Expr LBRACKET commandSeq ifs                    {$$ = ast_ifs($2,$4,$5);}
    | FOR Expr LBRACKET commandSeq RBRACKET     {$$ = ast_while($2,$4);}
    | SPRINT Expr CB SEMI_COL                  {$$ = ast_disp($2);}
    | FOR atrib Expr SEMI_COL Expr LBRACKET commandSeq RBRACKET              {$$ = ast_for($2,$3,$5,$7);}
    ;

atrib: VARIABLE ATRIB Expr SEMI_COL     {$$ = ast_atrib($1,$3);}
    ;

lim: NUM            {$$ = ast_integer($1);}
    |VARIABLE       {$$ = ast_variable($1);}
    ;

ifs: RBRACKET ELSEIF Expr LBRACKET commandSeq ifs            { $$ = ast_ifs($3, $5, $6); }
    | RBRACKET ELSE LBRACKET commandSeq RBRACKET                { $$ = ast_elses($4); }
    | RBRACKET                                   { $$ = NULL; }
    ;

Expr: Expr SUM Expr             {$$ = ast_operation($1,SUM,$3);} 
    | Expr SUB Expr             {$$ = ast_operation($1,SUB,$3);}
    | Expr MUL Expr             {$$ = ast_operation($1,MUL,$3);}
    | Expr DIV Expr             {$$ = ast_operation($1,DIV,$3);}
    | Expr GET Expr             {$$ = ast_operation($1,GET,$3);}
    | Expr LET Expr             {$$ = ast_operation($1,LET,$3);}
    | Expr LT Expr              {$$ = ast_operation($1,LT,$3);}
    | Expr GT Expr              {$$ = ast_operation($1,GT,$3);}
    | Expr DIF Expr             {$$ = ast_operation($1,DIF,$3);}
    | Expr COMP Expr            {$$ = ast_operation($1,COMP,$3);}
    | INP                       {$$ = ast_input();}
    | OB Expr CB                {$$ = $2;}
    | FALSE                     {$$ = ast_integer(0);}
    | TRUE                      {$$ = ast_integer(1);}
    | NUM                       {$$ = ast_integer($1);}
    | VARIABLE                  {$$ = ast_variable($1);}
    ;

%%

void yyerror(const char* err) {
	printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}
