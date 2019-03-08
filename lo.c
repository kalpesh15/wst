/*stack using link list*/
#include <stdio.h>
#include <stdlib.h>
#include"lo.h"

int isemptyo(stacko *s){
	if(*s == NULL)
		return 1;
	return 0;
}
void pusho(stacko *s, int x){
	node1 *ptr;
	ptr = (node1*) malloc (1*sizeof(node1));
	ptr -> p = *s;
	ptr -> a = x;
	*s = ptr;
}
int popo(stacko *s){
	node1 *pointer;
	int tmp;
	pointer = *s;
	tmp = pointer -> a;
	(*s) = (*s) -> p;
	free(pointer);
	return tmp;
}
void inito(stacko *s){
	*s = NULL;
}
