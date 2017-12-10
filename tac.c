#include <stdio.h>
#include "parser.h"
#include "tac.h"
#include <stdlib.h>
#include <string.h>

char** vars;
int var_ctr, label_ctr, endif_ctr;

Address* tac_empty() {
    Address* addr = (Address*) malloc(sizeof(Address));
    addr->AddressKind = EMPTY;
    return addr;
}

Address* tac_integer(int value) {
    Address* addr = (Address*) malloc(sizeof(Address));
    addr->AddressKind = INT;
    addr->content.value = value;
    return addr;
}

Address* tac_variable(char* c) {
    Address* addr = (Address*) malloc(sizeof(Address));
    addr->AddressKind = VAR;
    addr->content.var = strdup(c);

    //storage is done, now add to the array of strings for unique vars
    if(c[0] =='$' || c[0] =='L' || c[0] =='E')
        return addr;
    for(int i = 0; vars[i]!=NULL; i++ ){
        if(!strcmp(vars[i], c)) 
            return addr;
    }
    vars[i] = strdup(c);
    return addr;
}

Codline* tac_expr(OpKind op, Address* t0, Address* t1, Address* t2) {
    Codline* line = (Codline*) malloc(sizeof(Codline));
    line->op = op;
    line->addr1 = t0;
    line->addr2 = t1;
    line->addr3 = t2;
    return line;
}

ListCL* tac_list(Codline* head, ListCL* tail) {
    ListCL* list = (ListCL*) malloc(sizeof(ListCL));
    list->line = head;
    list->next = tail;
    return list;
}

ListCL* tac_append(Codline* list1, Codline* list2) {
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

