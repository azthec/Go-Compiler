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
    printf(".data\n");
    int i = 0;
    while(vars[i]!=NULL) {
        printf("    %s\n",vars[i]);
        i++;
    }
    printf(".text\n");

    //body
    Codline* line = NULL;
    while(list != NULL) {
        line = list->line;
        str1 = get_address_content(line->addr1);
        str2 = get_address_content(line->addr2);
        str3 = get_address_content(line->addr3);

        switch(line->op){

            case TAC_SUM:
                printf("    add %s, %s, %s\n", str1, str2, str3);
                break;
            case TAC_SUB:
                printf("    sub %s, %s, %s\n", str1, str2, str3);
                break;
            case TAC_DIV:
                printf("    div %s, %s\n", str2, str3);
                printf("    mflo %s\n", str1);
                break;
            case TAC_MUL:
                printf("    mult %s, %s\n", str2, str3);
                printf("    mflo %s\n", str1);
                break;
            case TAC_MODUL:
                printf("    div %s, %s\n", str2, str3);
                printf("    mfhi %s\n", str1);
                break;
            case TAC_GT:
                printf("    sgt %s, %s, %s\n", str1, str2, str3);
                break;
            case TAC_LT:
                printf("    slt %s, %s, %s\n", str1, str2, str3);
                break;
            case TAC_GET:
                printf("    sge %s, %s, %s\n", str1, str2, str3);
                break;
            case TAC_LET:
                printf("    sle %s, %s, %s\n", str1, str2, str3);
                break;
            case TAC_DIF:
                printf("    sne %s, %s, %s\n", str1, str2, str3);
                break;
            case TAC_COMP:
                printf("    seq %s, %s, %s\n", str1, str2, str3);
                break;
            case TAC_AND:
                printf("    and %s, %s, %s\n", str1, str2, str3);
                break;
            case TAC_OR:
                printf("    or %s, %s, %s\n", str1, str2, str3);
                break;
            case TAC_NOT:
                printf("    nor %s\n", str1);
                break;
            case TAC_ATRIB:
                printf("    add %s, %s, $0\n", str1, str2);
                break;
            case TAC_SPRINT:
                printf("    li $v0, 1\n");
                printf("    li $a0, %s\n", str1);
                printf("    syscall\n");
                break;
            case TAC_SSCAN:
                printf("    li $v0, 5\n");
                printf("    syscall\n");
                printf("    move %s, $v0\n", str2);
                printf("    sw %s, %s\n", str2, str1);
                break;
            case TAC_IF:
                printf("    beq %s, $0, %s\n", str1, str2);
                break;
            case TAC_GOTO:
                printf("    j %s\n", str1);
                break;
            case TAC_LABEL:
                printf("%s:\n", str1);
                break;
            case TAC_SW:
                printf("    sw %s, %s\n", str1, str2);
                break;
            case TAC_LI:
                printf("    li %s, %s\n", str1, str2);
                break;
            case TAC_LW:
                printf("    lw %s, %s\n", str1, str2);
                break;
            default: 
                yyerror("Invalid operand type received while printing mips.\n");

        }


        list = list->next; 
    }

    //tail
    printf("Exit:\n");
    printf("    li $v0, 10\n");
    printf("    syscall\n");
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
