typedef struct node1{
	int a;
	struct node1 *p;
}node1;
typedef node1* stacko;
int isemptyo(stacko *s);
void pusho(stacko *s,int x);
int popo(stacko *s);
void inito(stacko *s);

