/*this program calculates an infix expression and returns error on wrong input*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"lc.h"
#include"lo.h"
#define OPERATOR	100
#define	OPERAND		200
#define	END			300
#define	ERROR		400
#define MAX			32
#define CHA			0
#define DIG 		1
#define SPA 		2
#define BRACKET 	3
#define ERR 		4
#define ENDB 		5
int infixeval(char *infix);
void correct (char *s, char *p);
int main(){
	int ans, i = 0;
	char str[128], new[512];
	while((str[i++] = getchar()) != '\n');
	str[i-1] = '\0';
	while(i != 1){
	
		correct(str, new);
		ans = infixeval(new);
		if(ans != ERROR){
			printf("%d\n", ans);
		}
		else {
			printf("stderror\n");
		}
		i = 0;
		while((str[i++] = getchar()) != '\n');
		str[i-1] = '\0';
	}
	return 0;
}
/*this function takes a string from main possibly with errors, separate's(operator, operand) with space
and returns corrected string*/
void correct (char *s, char *p){
	int state = SPA, i = 0, j = 0;
	char tmp;
	while(*(s + i) != '\0'){
		tmp = *(s+i);
		i++;
		if(state == ERR){
			p[0] = 'w';
			break;
		}
		switch(state){
			case CHA:
				switch(tmp){
					case '+': case '-': case '*':
					case '/': case '%': case ')':
						state = ERR;
						break;		
					case '0': case '1': case '2': case '3': case '4':
					case '5': case '6': case '7': case '8': case '9': 
						p[j++] = ' ';
						p[j++] = tmp;
						state = DIG;
						break;
					case '(':
						p[j++] = ' ';
						p[j++] = tmp;
						state = BRACKET;
						break;
					case ' ': case '\t':
						p[j++] = ' ';
						state = SPA;
						break;
					default:
						state = ERR;
						break;
					}
				break;
			case DIG:
				switch(tmp){
					case '+': case '-': case '*': case '/': case '%':
						p[j++] = ' ';
						p[j++] = tmp;
						state = CHA;
						break;
					case '0': case '1': case '2': case '3': case '4':
					case '5': case '6': case '7': case '8': case '9':
						p[j++] = tmp;
						state = DIG;
						break;
					case ' ': case '\t':
						p[j++] = ' ';
						state = SPA;
						break;
					case '(':
						state = ERR;
						break;
					case ')':
						p[j++] = ' ';
						p[j++] = tmp;
						state = ENDB;
						break;
					default:
						state = ERR;
						break;
					}
				break;
			case SPA:
				switch(tmp){
					case '+': case '-': case '*': case '/': case '%':
						p[j++] = tmp;
						state = CHA;
						break;
					case '0': case '1': case '2': case '3': case '4':
					case '5': case '6': case '7': case '8': case '9':
						p[j++] = tmp;
						state = DIG;
						break;
					case ' ': case '\t':
						state = SPA;
						break;
					case '(': 
						p[j++] = tmp;
						state = BRACKET;
						break;
					case ')':
						p[j++] = ' ';
						p[j++] = tmp;
						state = ENDB;
						
					default:
						state = ERR;
						break;
					}
				break;
			case BRACKET:
				switch(tmp){
					case '+': case '-': case '*': case '/': case '%': case ')':
						state = ERR;
						break;
					case '0': case '1': case '2': case '3': case '4':
					case '5': case '6': case '7': case '8': case '9':
						p[j++] = ' ';
						p[j++] = tmp;
						state = DIG;
						break;
					case ' ': case '\t':
						p[j++] = ' ';
						state = SPA;
						break;
					case '(':
						state = BRACKET;
						p[j++] = ' ';
						p[j++] = tmp;
						break; 
						
					default:
						state = ERR;
						break;
					}
				break;
			case ENDB:
				switch(tmp){
					case '+': case '-': case '*': case '/': case '%': 
						p[j++] = ' ';
						p[j++] = tmp;
						state = CHA;
						break;
					case '0': case '1': case '2': case '3': case '4':
					case '5': case '6': case '7': case '8': case '9':
						state = ERR;
						break;
					case ' ': case '\t':
						p[j++] = ' ';
						state = SPA;
						break;
					case '(':
						state = ERR;
						break;
					case ')':
						p[j++] = ' ';
						p[j++] = tmp;
						state = ENDB;
						break;
						
					default:
						state = ERR;
						break;
					}
				break;
				
			}			
	}
	p[j] = '\0';	
}
/*this function checks precedence of operators*/
int precedence(char op){
	if(op == '%')
		return 100;
	else if (op == '/' || op == '*')
		return 80;
	else
		return 60;
	}
/*this function takes an infix expression from main with each token saparated by space and
 computes the expression*/
int infixeval(char *infix){
	char *tok, tmpsign = 0;
	stackc operator;/*stack for operators*/
	stacko operand;/*stack for operands*/
	int  state, tmpans,  a, b, in, pre1, pre2;
	tok = strtok(infix, " ");
	initc(&operator);
	inito(&operand);
	while(tok != NULL){
		
		 if(*(tok+0) <= '9' && *(tok+0) >= '0'){
			in = atoi(tok);
			pusho(&operand, in);
			state = OPERAND;
		}
		else if(*tok == '+' || *tok == '*' || *tok == '-' || *tok == '/' || *tok == '%'){
				while(!isemptyc(&operator) && (tmpsign = popc(&operator)) != '('){
					
					/*precedence of operators*/
					pre1 = precedence (*tok);
					pre2 = precedence(tmpsign);
					if(pre2 >= pre1){/*greater than current*/
						b = popo(&operand);
						a = popo(&operand);
						switch(tmpsign){
							case '+':
								tmpans = a + b;
								pusho (&operand, tmpans);
								break;
							case '-':
								tmpans = a - b;
								pusho (&operand, tmpans);
								break;
							case '*':
								tmpans = a * b;
								pusho (&operand, tmpans);
								break;
							case '/':
								if(b == 0)
									return ERROR;
								tmpans = a / b;
								pusho (&operand, tmpans);
								break;
							case '%':
								tmpans = a % b;
								pusho (&operand, tmpans);
								break;
								}
						}
						
						else{
							pushc(&operator, tmpsign);
							break;
						}
					}
					if(tmpsign == '('){
						pushc(&operator, tmpsign);
					}
					pushc(&operator, *tok);
				}
			else if(*tok == '(' ){
				pushc(&operator, *tok);
			}
			else if(*tok == ')' ){
				if(!isemptyc(&operator)){
					tmpsign = popc(&operator);
				}
				while(tmpsign != '('){
						b = popo(&operand);
						a = popo(&operand);
						switch(tmpsign){
							case '+':
								tmpans = a + b;
								pusho (&operand, tmpans);
								break;
							case '-':
								tmpans = a - b;
								pusho (&operand, tmpans);
								break;
							case '*':
								tmpans = a * b;
								pusho (&operand, tmpans);
								break;
							case '/':
								if(b == 0)
									return ERROR;
								tmpans = a / b;
								pusho (&operand, tmpans);
							break;
							case '%':
								tmpans = a % b;
								pusho (&operand, tmpans);
								break;
						}
						if(!isemptyc(&operator)){
							tmpsign = popc(&operator);
							}
						else{
							return ERROR;
							}
					}
					if(tmpsign = '(')
						tmpsign = 0;
				
			}
			else
				return ERROR;
		
			tok = strtok(NULL, " ");
		}
		while(!isemptyc(&operator)){
			tmpsign = popc(&operator);
			b = popo(&operand);
			a = popo(&operand);
			switch(tmpsign){
				case '+':
					tmpans = a + b;
					pusho (&operand, tmpans);
					break;
				case '-':
					tmpans = a - b;
					pusho (&operand, tmpans);
					break;
				case '*':
					tmpans = a * b;
					pusho (&operand, tmpans);
					break;
				case '/':
					if(b == 0)
						return ERROR;
					tmpans = a / b;
					pusho (&operand, tmpans);
					break;
				case '%':
					tmpans = a % b;
					pusho (&operand, tmpans);
					break;
				}
			}
	return popo(&operand);
}	
