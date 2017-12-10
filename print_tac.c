#include <stdio.h>
#include "parser.h"
#include "tac.h"
#include <stdlib.h>
#include <string.h>

char* get_address_content(Address* addr) {
    if(addr == NULL)
        return " ";
    else if(addr->operator==Var)
        return addr->content.var;
    else { //itoa is not standard and shouldnt be used
        char* tmp = malloc(sizeof(char)*10);
        sprintf(tmp, "%d", addr->content.value);
        return tmp;
    }
}


void compilers_assemble(ListCL* list, char** vars){
    char *str1, *str2, *str3;

    //head
    printf("main:\n");
    printf("    BeginFunc 24;\n");


    //body
    Codline* line = NULL;
    while(list != NULL) {
        line = list->line;
        str1 = get_address_content(line->addr1);
        str2 = get_address_content(line->addr2);
        str3 = get_address_content(line->addr3);

        switch(line->op){

            case TAC_SUM:
                printf("    %s = %s + %s;\n", str1, str2, str3);
                break;
            case TAC_SUB:
                printf("    %s = %s - %s;\n", str1, str2, str3);
                break;
            case TAC_DIV:
                printf("    %s = %s / %s;\n", str1, str2, str3);
                break;
            case TAC_MUL:
                printf("    %s = %s * %s;\n", str1, str2, str3);
                break;
            case TAC_MODUL:
                printf("    %s = %s % %s;\n", str1, str2, str3);
                break;
            case TAC_GT:
                printf("    %s = %s > %s;\n", str1, str2, str3);
                break;
            case TAC_LT:
                printf("    %s = %s < %s;\n", str1, str2, str3);
                break;
            case TAC_GET:
                printf("    _t0 = %s > %s;\n", str2, str3);
                printf("    _t1 = %s == %s;\n", str2, str3);
                printf("    %s = _t0 || _t1;\n", str1);
                break;
            case TAC_LET:
                printf("    _t0 = %s < %s;\n", str2, str3);
                printf("    _t1 = %s == %s;\n", str2, str3);
                printf("    %s = _t0 || _t1;\n", str1);
                break;
            case TAC_DIF:
                printf("    _t0 = %s == %s;\n", str2, str3);
                printf("    %s = !_t0;\n", str2, str3);
                break;
            case TAC_COMP:
                printf("    %s = %s == %s;\n", str1, str2, str3);
                break;
            case TAC_AND:
                printf("    %s = %s && %s;\n", str1, str2, str3);
                break;
            case TAC_OR:
                printf("    %s = %s || %s;\n", str1, str2, str3);
                break;
            case TAC_NOT:
                printf("    %s = !%s;\n", str1, str2);
                break;
            case TAC_ATRIB:
                printf("    %s = %s;\n", str1, str2);
                break;
            case TAC_SPRINT:
                printf("    PRINT(%s);\n", str1);
                break;
            case TAC_SSCAN:
                printf("    SCAN(%s);\n", str1);
                break;
            case TAC_IF:
                printf("    IfZ %s Goto, %s;\n", str1, str2);
                break;
            case TAC_GOTO:
                printf("    Goto %s;\n", str1);
                break;
            case TAC_LABEL:
                printf("%s:\n", str1);
                break;
            case TAC_SW:
                printf("    %s = %s;\n", str1, str2);
                break;
            case TAC_LI:
                printf("    %s = %s;\n", str1, str2);
                break;
            case TAC_LW:
                printf("    %s = %s;\n", str1, str2);
                break;
            default: 
                yyerror("Invalid operand type received while printing mips.\n");

        }


        list = list->next; 
    }

    //tail
    printf("    EndFunc;\n");
}




int main(int argc, char** argv) {
    ListCL* list = NULL;
    char** vars = (char**)malloc( 512*sizeof(char*));
    --argc; ++argv;
    if (argc != 0) {
        yyin = fopen(*argv, "r");
        if (!yyin) {
            printf("'%s': could not open file\n", *argv);
            return 1;
        }

        if (yyparse() == 0) {
            list = compile_tac(root, vars);
        }

        compilers_assemble(list, vars);
    }
    return 0;
}
