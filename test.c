#include <stdio.h>
int my_func(int **p)
{
	*p=NULL;
}

int main()
{
	int a=10;
	int *p=&a;
	printf("%d\n",*p);
	my_func(&p);
	//p=NULL;
	printf("%d\n",*p);
}

