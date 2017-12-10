#include <stdio.h>
#include "parser.h"
#include "tac.h"
#include <stdlib.h>
#include <string.h>

char** vars;
int var_ctr, label_ctr, endif_ctr;

Address* tac_empty() {
    Address* addr = (Address*) malloc(sizeof(Address));
    addr->operator = Empty;
    return addr;
}

Address* tac_integer(int value) {
    Address* addr = (Address*) malloc(sizeof(Address));
    addr->operator = Int;
    addr->content.value = value;
    return addr;
}

Address* tac_variable(char* c) {
    Address* addr = (Address*) malloc(sizeof(Address));
    addr->operator = Var;
    addr->content.var = strdup(c);

    //storage is done, now add to the array of strings for unique vars
    if(c[0] =='$' || c[0] =='L' || c[0] =='E')
        return addr;
    int i;
    for(i = 0; vars[i]!=NULL; i++ ){
        if(!strcmp(vars[i], c)) 
            return addr;
    }
    vars[i] = strdup(c);
    return addr;
}

Codline* tac_expr(OpKind op, Address* addr1, Address* addr2, Address* addr3) {
    Codline* line = (Codline*) malloc(sizeof(Codline));
    line->op = op;
    line->addr1 = addr1;
    line->addr2 = addr2;
    line->addr3 = addr3;
    return line;
}

ListCL* tac_list(Codline* head, ListCL* tail) {
    ListCL* list = (ListCL*) malloc(sizeof(ListCL));
    list->line = head;
    list->next = tail;
    return list;
}

ListCL* tac_append(ListCL* list1, ListCL* list2) {
    if(list1==NULL) return list2;
    if(list2==NULL) return list1;
    ListCL* p;
    for(p = list1; p->next!=NULL; p=p->next);
    p->next = list2;
    return list1;
}

Pair* tac_pair(Address* addr, ListCL* list) {
    Pair* p = (Pair*) malloc(sizeof(Pair));
    p->address = addr;
    p->list = list;
    return p;
}

char* new_tvariable(){
    char* buf = malloc(sizeof(char)*5);
    sprintf(buf, "$t%d", var_ctr);
    var_ctr++;
    return buf;
}

char* new_label() {
    char* buf = malloc(sizeof(char)*5);
    sprintf(buf, "L%d", label_ctr);
    label_ctr++;
    return buf;
}

char* new_endif_label(){ 
    char* buf = malloc(sizeof(char)*5);
    sprintf(buf, "E%d", endif_ctr);
    endif_ctr++;
    return buf;
}


Pair* compile_exp(Expr* expr) {
    char* auxStr = NULL;
    Address* auxAddr = NULL;
    Codline* auxLine = NULL;
    Pair* auxPar  = NULL;
    Pair* auxA = NULL;
    Pair* auxB = NULL;

    switch(expr->type) {
        case E_INTEGER:
            auxAddr = tac_variable(new_tvariable());
            auxPar = tac_pair(auxAddr, tac_list(tac_expr(TAC_LI, auxAddr, tac_integer(expr->c.value), NULL),NULL));
            return auxPar;
        case E_IDENTIF:
            auxAddr = tac_variable(new_tvariable());
            auxPar = tac_pair(auxAddr, tac_list(tac_expr(TAC_LW, auxAddr, tac_variable(expr->c.string), NULL), NULL));
            return auxPar;
        case E_OPERATION:
            auxA = compile_exp(expr->c.op.left);
            auxB = compile_exp(expr->c.op.right);
            auxAddr = tac_variable(new_tvariable());
            switch(expr->c.op.operator) {
                case SUM:
                    auxLine = tac_expr(TAC_SUM, auxAddr, auxA->address, auxB->address);
                    break;
                case SUB:
                    auxLine = tac_expr(TAC_SUB, auxAddr, auxA->address, auxB->address);
                    break;
                case MUL:
                    auxLine = tac_expr(TAC_MUL, auxAddr, auxA->address, auxB->address);
                    break;
                case DIV:
                    auxLine = tac_expr(TAC_DIV, auxAddr, auxA->address, auxB->address);
                    break;
                //TODO case MODUL:
                case GT:
                    auxLine = tac_expr(TAC_GT, auxAddr, auxA->address, auxB->address);
                    break;
                case LT:
                    auxLine = tac_expr(TAC_LT, auxAddr, auxA->address, auxB->address);
                    break;
                case GET:
                    auxLine = tac_expr(TAC_GET, auxAddr, auxA->address, auxB->address);
                    break;
                case LET:
                    auxLine = tac_expr(TAC_LET, auxAddr, auxA->address, auxB->address);
                    break;
                case DIF:
                    auxLine = tac_expr(TAC_DIF, auxAddr, auxA->address, auxB->address);
                    break;
                case COMP:
                    auxLine = tac_expr(TAC_COMP, auxAddr, auxA->address, auxB->address);
                    break;
                //TODO case AND:
                //TODO case OR:
                //TODO case NOT:
                default: yyerror("Invalid operand received while compiling operation.\n");
            }

            auxPar = tac_pair(auxAddr,tac_append(tac_append(auxA->list,auxB->list), tac_list(auxLine,NULL)));
            return auxPar;

        default:
            yyerror("Invalid expression type received while compiling expression.\n");
    }
}


ListCL* compile_if(Command* cmd, char* endif) {
    ListCL* auxLA = NULL;
    ListCL* auxLB = NULL;
    Pair* auxPar = NULL;
    Address* labelA = NULL;
    Address* labelB = NULL;
    CommandList* help = NULL;

    switch(cmd->type) {
        
        case CMD_IFS: //do if and ifelses stuff
            if(!endif) //we the OG if statement
                endif = new_endif_label();
            labelA = tac_variable(new_label());
            labelB = tac_variable(new_label());

            auxPar = compile_exp(cmd->c.ifs.e);

            auxLA = tac_append(auxPar->list,tac_list(tac_expr(TAC_IF,auxPar->address,labelA,NULL),NULL));
            auxLA = tac_append(auxLA,tac_list(tac_expr(TAC_GOTO,labelB,NULL,NULL),NULL));

            //labelA section
            auxLA = tac_append(auxLA,tac_list(tac_expr(TAC_LABEL,labelA,NULL,NULL),NULL));
            help = cmd->c.ifs.list; //code inside the if
            while(help!=NULL) {
                auxLB = compile_cmd(help->cmd);
                help = help->next;
                auxLA = tac_append(auxLA, auxLB);
            }
            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_GOTO, tac_variable(endif), NULL, NULL),NULL));

            //labelB section
            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_LABEL,labelB,NULL,NULL),NULL));
            if(cmd->c.ifs.elses) {
                auxLA = tac_append(auxLA, compile_if(cmd->c.ifs.elses, endif));
            } else {
                auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_LABEL,tac_variable(endif),NULL,NULL), NULL));
            }

            return auxLA;

        case CMD_ELSES: //do else stuff
            help = cmd->c.elses;
            while(help != NULL) {
                auxLB = compile_cmd(help->cmd);
                help = help->next;
                auxLA = tac_append(auxLA, auxLB);
            }
            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_LABEL,tac_variable(endif),NULL,NULL), NULL));

            return auxLA;

        default:
            yyerror("Invalid command type received while compiling ifs.\n");
    }
}


ListCL* compile_cmd(Command* cmd) {
    ListCL* auxLA = NULL;
    ListCL* auxLB = NULL;
    Pair* auxPar = NULL;
    Pair* incPar = NULL;
    Address* labelA = NULL;
    Address* labelB = NULL;
    Address* labelC = NULL;
    Address* auxReg = NULL;
    Address* auxReg2 = NULL;
    Address* auxVar = NULL;
    Codline* auxLine = NULL;
    CommandList* help = NULL;

    switch(cmd->type) {
        case CMD_ATRIB:
            auxPar = compile_exp(cmd->c.attrib.e);
            auxReg = tac_variable(new_tvariable());
            auxVar = tac_variable(cmd->c.attrib.identifier);

            auxLB = tac_list(tac_expr(TAC_LW, auxReg, auxVar, NULL), auxPar->list);
            auxLA = tac_append(auxLB, tac_list(tac_expr(TAC_ATRIB, auxReg, auxPar->address, NULL), NULL));
            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_SW, auxReg, auxVar,NULL), NULL));

            return auxLA;

        case CMD_WHILE:
            auxPar = compile_exp(cmd->c.while_exp.condition);
            labelA = tac_variable(new_label());
            labelB = tac_variable(new_label());
            labelC = tac_variable(new_label());
            auxLA = tac_append(tac_list(tac_expr(TAC_LABEL,labelA,NULL,NULL),NULL),auxPar->list);
            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_IF,auxPar->address,labelC,NULL),NULL));
            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_GOTO,labelB,NULL,NULL), NULL));
            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_LABEL,labelC,NULL,NULL),NULL));
            help = cmd->c.while_exp.commands;
            while(help != NULL) {
                auxLB = compile_cmd(help->cmd);
                help = help->next;
                auxLA = tac_append(auxLA, auxLB);
            }
            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_GOTO,labelA,NULL,NULL),NULL));

            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_LABEL,labelB,NULL,NULL),NULL));

            return auxLA;

        case CMD_FOR:
            auxPar = compile_exp(cmd->c.for_exp.right);
            labelA = tac_variable(new_label());
            labelB = tac_variable(new_label());
            labelC = tac_variable(new_label());

            auxReg = tac_variable(new_tvariable());
            auxReg2 = tac_variable(new_tvariable());
            auxVar = tac_variable(cmd->c.for_exp.left->c.attrib.identifier);

            //init
            incPar = compile_exp(cmd->c.for_exp.left->c.attrib.e);
            auxLA = tac_append(tac_list(tac_expr(TAC_LW,auxReg,auxVar,NULL),incPar->list),tac_list(tac_expr(TAC_ATRIB,auxReg,incPar->address,NULL),NULL));
            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_SW,auxReg,auxVar,NULL),NULL));

            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_LABEL,labelA,NULL,NULL),NULL));
            auxLA = tac_append(auxLA, auxPar->list);
            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_LW,auxReg,auxVar,NULL), NULL));
            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_LET,auxReg2,auxReg,auxPar->address), NULL));
            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_IF,auxReg2,labelC,NULL), NULL));
            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_GOTO,labelB,NULL,NULL), NULL));
            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_LABEL,labelC,NULL,NULL),NULL));

            //body
            help = cmd->c.for_exp.commands;
            while(help != NULL) {
                auxLB = compile_cmd(help->cmd);
                help = help->next;
                auxLA = tac_append(auxLA, auxLB);
            }

            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_LW, auxReg, auxVar, NULL), NULL));
            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_LI, auxReg2, tac_integer(1), NULL), NULL));
            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_SUM, auxReg, auxReg, auxReg2), NULL));
            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_SW, auxReg, auxVar, NULL), NULL));

            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_GOTO, labelA, NULL, NULL), NULL));

            auxLA = tac_append(auxLA, tac_list(tac_expr(TAC_LABEL, labelB, NULL, NULL), NULL));

            return auxLA;

        case CMD_IFS:
            return compile_if(cmd, NULL);

        case CMD_DIS:
            auxPar = compile_exp(cmd->c.condition);
            auxLA = tac_append(auxPar->list, tac_list(tac_expr(TAC_SPRINT,auxPar->address,NULL,NULL),NULL));
            
            return auxLA;

        case CMD_INP:
            auxLA = tac_list(tac_expr(TAC_SSCAN,tac_variable(cmd->c.input.identifier),tac_variable(new_tvariable()),NULL), NULL);

            return auxLA;

    }
}

ListCL* compile_tac(CommandList* root, char** varsin) {
    ListCL* auxL = NULL;
    vars = varsin;

    while(root != NULL) {
        var_ctr = 0;
        auxL = tac_append(auxL, compile_cmd(root->cmd));
        root = root->next;
    }
    return auxL;
}

