#include <stdio.h>
#include "parser.h"

void printTree(CommandList* root, int level);
void print_expr(Expr* expr, int depth);
void printCommand(Command* cmd, int depth, int flag);

int main(int argc, char *argv[]){
	--argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } 
  if (yyparse() == 0) {
    printf("func main() {\n");
    printTree(root,1);
    printf("}\n");
  }
  return 0;
}

void returnSymbol(int operator){
	switch(operator){
		case SUM: printf(" + "); break;
		case SUB: printf(" - "); break;
		case MUL: printf(" * "); break;
		case DIV: printf(" / "); break;
		case GT: printf(" > "); break;
		case LT: printf(" < "); break;
		case GET: printf(" >= "); break;
		case LET: printf(" <= "); break;
		case DIF: printf(" ~= "); break;
		case COMP: printf(" == "); break;
		case MODUL: printf(" % "); break;
		case AND: printf(" && "); break;
		case OR: printf(" || "); break;
        case NOT: printf("! "); break;
	}
}

void printCommand(Command* cmd, int depth,int flag){
	printf("%d| ", depth);
	switch(cmd->type){
			case CMD_ATRIB:{
				printf("%s := ",cmd->c.attrib.identifier);
				print_expr(cmd->c.attrib.e, depth+1);
				printf(";\n");
				break;
			}
			case CMD_FOR:{
				printf("for ");
				Command* cmdd = cmd->c.for_exp.left;
				printf("%s:=",cmdd->c.attrib.identifier);
				print_expr(cmdd->c.attrib.e, depth+1);	
				printf("; ");
				print_expr(cmd->c.for_exp.right, depth+1);
				printf("; ");
				print_expr(cmd->c.for_exp.increment, depth+1);
				printf(" {\n");
				printTree(cmd->c.for_exp.commands,depth+1);			
				printf("%d| }\n", depth);
				break;
			}
			case CMD_WHILE:{
				printf("for ");
				print_expr(cmd->c.while_exp.condition, depth+1);
				printf(" {\n");
				printTree(cmd->c.while_exp.commands,depth+1);
				printf("%d| }\n", depth);
				break;
			}
			case CMD_IFS:{
			    if(!flag)
			      printf("if ");                        
			    else
			      printf("} elseif ");
			    print_expr(cmd->c.ifs.e, depth+1);
			    printf("{\n");
			    printTree(cmd->c.ifs.list,depth+1);
			    if(cmd->c.ifs.elses) {              
			      printCommand(cmd->c.ifs.elses,depth, 1);
			    }
			    if(!flag)
			    	printf("%d| }\n", depth);
			    break;
			}
			case CMD_ELSES: {
		    	printf("} else\n");
			    printTree(cmd->c.elses,depth+1);  
				break;
			}
			case CMD_DIS:{
				printf("Sprint(");
				print_expr(cmd->c.condition, depth+1);
				printf(");\n");
				break;
			}
			case CMD_INP:{
				printf("Sscan(%s);\n",cmd->c.input.identifier);
				break;
			}
			default: yyerror("Unkown Command");
	}
}

void printTree(CommandList* root, int depth)
{
	while(root!=NULL)
	{
		printCommand(root->cmd,depth,0);
		root=root->next;
	}
}

void print_expr(Expr* expr, int depth){
	switch(expr->type){
		case E_INTEGER:{
			printf("%d ",expr->c.value);
			break;
		}
		case E_OPERATION:{
			if(expr->c.op.operator != NOT)
				print_expr(expr->c.op.left, depth+1);
            returnSymbol(expr->c.op.operator);			
            print_expr(expr->c.op.right, depth+1);
			break;
		}
		case E_IDENTIF:{
			printf("%s",expr->c.string);
			break;
		}
	}
}
