#include <string.h>
#include <stdio.h>
#include <conio.h>

#define SIZE 100
typedef struct stack{
	int top;
	char *st[SIZE];
}STACK;

void initialize(STACK *stack){
	stack->top=0;
}

int isEmpty(STACK *stack){
	if(stack->top==0){
		return 1;
	}
	else{
		return 0;
	}
}

int isFull(STACK *stack){
	if(stack->top==SIZE){
		return 1;
	}
	else{
		return 0;
	}
}

void push(STACK *stack, char *val){
	if(!isFull(&stack)){
		stack->st[stack->top]=val;
		stack->top++;		
	}
}

char *pop(STACK *stack){
	char *val;
	if(!isEmpty(&stack)){
		stack->top-=1;
		val=stack->st[stack->top];
		return val;
	}
	else{
		return "!";
	}
	
}
int isContain(char list[50][10], char item[10], int size){
	int i=0;
//	printf("\n\nis conteyyyn.\n");
//	printf("item:%s",item);
//	printf("kkkkkkkkkkkkkkkkkkkkklist:%s\n",list[i]);
//	printf("hhhhhhhhhhhhhhhhh:%d",strcmp(list[i],item));
	
	while(size>i && strcmp(list[i],item)!=0){
//		printf("list:%s\n",list[i]);
		i++;
	}
	if(i>=size){
		return -1;
	}
	else{
		return i;
	}
}
int main(){
	STACK stack;
	char *pop_i;
	initialize(&stack);
	
	//push(&stack,"b");
	//push(&stack,"a");
	
	//pop_i=pop(&stack);
	//printf("pop:%s\n",pop_i);

	//push(&stack,"c");
	//printf("%s",stack.st[1]);
	
	FILE *fp=fopen("input.txt", "r");
	char *split;
	char vars[50][10];
	char line[10];
	char *eqs[100];
	int p=1, index=0,i,s,f,result;
	int size_vars=0;
	int results[50];
	char postfix[50][50];
	int size_post=0;
	
	while(!feof(fp)){
		fscanf(fp,"%s",line);
		if(p){
			size_post=0;
			index=isContain(vars,line,size_vars);
			if(index==-1){
			
				strcpy(vars[size_vars],line);
			//	printf("varlist:%s\n",vars[size_vars]);
				size_vars++;
				index=size_vars-1;
				
			}
			p=0;
			
		}
		else{
			if(!strcmp(line,";")){
				
				while(!isEmpty(&stack)){
					pop_i=pop(&stack);
					strcpy(postfix[size_post],pop_i);
					printf("postfix:%s\n",postfix[size_post]);
					size_post++;
				}
				
				for (i=0;i<size_post;i++){
					if(strcmp(postfix[i],"*") && strcmp(postfix[i],"/") && strcmp(postfix[i],"+") && strcmp(postfix[i],"-")){
						push(&stack,postfix[i]);
					}
					else{
						s=atoi(pop(&stack));
						f=atoi(pop(&stack));
						if(!strcmp(postfix[i],"*")){
							result=s*f;
						}
						else if(!strcmp(postfix[i],"/")){
							result=f/s;	
						}
						else if(!strcmp(postfix[i],"+")){
							result=f+s;
						}
						else if(!strcmp(postfix[i],"-")){
							result=f-s;
						}
						char buffer[20];
						itoa(result,buffer,10);
						push(&stack,buffer);
					}
					
				}
				results[index]=atoi(pop(&stack));
				p=1;
			}
			else if(!strcmp(line,"(")){
				
				push(&stack,line);
			}
			else if(!strcmp(line,")")){
				pop_i=pop(&stack);
				while(strcmp(pop_i,"(")){
					strcpy(postfix[size_post],pop_i);
					
					pop_i=pop(&stack);
					size_post++;
				}
			}
			else if(!strcmp(line,"+") || !strcmp(line,"-")){
				if(stack.top!=0 && strcmp(stack.st[stack.top-1],"(")){
					pop_i=pop(&stack);
					strcpy(postfix[size_post],pop_i);
					size_post++;
					
				}
				push(&stack,line);
				
			}
			else if(!strcmp(line,"*") || !strcmp(line,"/")){
				if(stack.top==0 || !strcmp(stack.st[stack.top-1],"+") || !strcmp(stack.st[stack.top-1],"-") || !strcmp(stack.st[stack.top-1],"(")){
					push(&stack,line);
				}
				else{
					pop_i=pop(&stack);
					strcpy(postfix[size_post],pop_i);
					size_post++;
					push(&stack,line);
				}
			}
			else if(!strcmp(line,"=")){
				//bos
			}
			else if(isContain(vars,line,size_vars)!=-1){
				//variablesa
				
				char buffer[50];
				itoa(results[isContain(vars,line,size_vars)],buffer,10);
				strcpy(postfix[size_post],buffer);
				size_post++;
			}
			else{
				//sayiysa
				strcpy(postfix[size_post],line);
				size_post++;
			}
			
	}
	}
	fclose(fp);
	
	
	return 1;
}

