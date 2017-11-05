%{
// HEADERS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "parser.h"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)

// variables maintained by the lexical analyser
int yyline = 1;
%}
%option noyywrap

VAR		[a-zA-Z_]
DIGIT	\-?[0-9]+
%%

#.*\n		{ yyline++;}
[ \t]+		{ }
\n 			{ yyline++;}

"func main()" { return FMAIN; }
"{" { return LBRACKET; }
"}" { return RBRACKET; }

"+"         {return SUM;}
"-"         {return SUB;}
"*"         {return MUL;}
"/"         {return DIV;}
"%"         {return MODUL;}

"true"      {return TRUE;}
"false"     {return FALSE;}
"<"         {return LT;}
">"         {return GT;}
"<="        {return LET;}
">="        {return GET;}
"=="        {return COMP;}
"~="        {return DIF;}
"&&"        {return AND;}
"||"        {return OR;}
"!"        {return NOT;}

"if"        {return IF;}
"else"      {return ELSE;}
"elseif"    {return ELSEIF;}
"for"       {return FOR;}

":="         {return ATRIB;}
";"			{return DOTCOMA;}
"("			{return LPARENTH;}
")"			{return RPARENTH;}
"Sprint(\"\%d\","		{return SPRINT;}
"Sscan(\"\%d\"," { return SSCAN; }
{DIGIT}+    {yylval.INT=atoi(yytext);return INT;}
{VAR}+      {yylval.identifier=strdup(yytext);return VARIABLE;} /* nao pode haver palavras (ie: if) abaixo desta regra ou nao encaixam, porque encaixam sempre nesta */

.  { yyerror("unexpected character"); }
%%
