/* Analise Sintática  */
%{
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "parser.h"
int yyline = 1;
%}
%option noyywrap

VAR		[a-zA-Z]
DIGIT	\-?[0-9]+
%%

{DIGIT}+	{yylval.num=atoi(yytext);return NUM;}
#.*\n		{ yyline++;}
[ \t]+		{ }
\n 			{ yyline++;}
"func main()" { return FMAIN; }
"{" { return LBRACKET; }
"}" { return RBRACKET; }
";"			{return SEMI_COL;}
"true"		{return TRUE;}
"false"		{return FALSE;}
"if"		{return IF;}
"else"		{return ELSE;}
"elseif"	{return ELSEIF;}
"for"		{return FOR;}
"end"		{return END;}
"while"		{return WHILE;}
":"			{return DOTS;}
"("			{return OB;}	/*Open Brackets*/
")"			{return CB;}	/*Close Brackets*/	
"+"			{return SUM;}
"-"			{return SUB;}
"*"			{return MUL;}
"/"			{return DIV;}
":="			{return ATRIB;}
"<"			{return LT;} 	/*Lower than*/
">"			{return GT;} 	/*Greater than*/
"<=" 		{return LET;}	/*Lower or Equal Than*/ 
">="		{return GET;}	/*Greater or Equal Than*/ 
"=="		{return COMP;}
"~="		{return DIF;}
"Sprint(\"\%d\","		{return SPRINT;}
{VAR}+		{yylval.identificador=strdup(yytext);return VARIABLE;}
.			{yyerror("Caracter inválido\n");}
%%
