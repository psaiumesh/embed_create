#include <stdio.h>
#include <stdlib.h>
//char ch[100];
int main()
{
	int *p=(int *)malloc(4*sizeof(int));
	int i;
	for(i=0;i<4;i++)
		p[i]=i;
	for(i=0;i<4;i++)
		printf("%d\n",p[i]);
	free(p);
	for(i=0;i<4;i++)
		printf("%d\n",p[i]);
	//printf("%ld\n",sizeof (ch));
}

