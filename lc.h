typedef struct node2{
	char a;
	struct node2 *p;
}node2;
typedef node2* stackc;
int isemptyc(stackc *s);
void pushc(stackc *s,char x);
char popc(stackc *s);
void initc(stackc *s);

