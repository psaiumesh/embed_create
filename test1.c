#include <stdio.h>
char  b1[100];
char  b2[100];
char  b3[100];
char *ptr[3];
//ptr[0]=b1;
//ptr[1]=b2;
//ptr[2]=b3;
//ptr[0]=b1;
//ptr=[b1,b2,b3]
int main()
{
	printf("%p %p %p\n",b1,b2,b3);
	//int *p;
	ptr[0]=b1;
	ptr[1]=b2;
	ptr[2]=b3;
	printf("%p %p %p \n",ptr[0],ptr[1],ptr[2]);
	//for (int i=0;i<3;i++)
	//	ptr[i];
}

