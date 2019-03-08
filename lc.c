/*stack implementation using link list*/
#include <stdio.h>
#include <stdlib.h>
#include"lc.h"

int isemptyc(stackc *s){
	if(*s == NULL)
		return 1;
	return 0;
}
void pushc(stackc *s, char x){
	node2 *ptr;
	ptr = (node2*) malloc (1*sizeof(node2));
	ptr -> p = *s;
	ptr -> a = x;
	*s = ptr;
}
char popc(stackc *s){
	node2 *pointer;
	char tmp;
	pointer = *s;
	tmp = pointer -> a;
	(*s) = (*s) -> p;
	free(pointer);
	return tmp;
}
void initc(stackc *s){
	*s = NULL;
}
