#include<stdio.h>
int f1=0;
int f2=0;
char  b1[100];
char  b2[100];

void * my_malloc(int size)
{
	if((f1==0) && (size <=sizeof(b1)))
	{
		f1=1;
		return((void *)b1);
	}

	if(f2==0 && (size <=sizeof(b2)))
	{
		f2=1;
		return((void *)b2);
	}

	if(size > sizeof(b1))
	{
		printf("requested memory more than avaible\n");
		return NULL;
	}

	printf("memory is not there \n");
	return NULL;

}

void my_free(void *ptr)
{
	if(f1==1)
	{
		f1=0;
	}
	else if(f2==1)
	{
		f2=0;
	}
}


void who_is_free()
{
	if(!f1)
		printf("B1 is FREE\n");
	else
		printf("B1 is ALLOCED\n");

	if(!f2)
		printf("B2 is FREE\n");
	else
		printf("B2 is ALLOCED\n");
	printf("\n");
}

void test1()
{
	char *p1, *p2, *p3, *p4, *p5;;
	p1 = p2 = p3 = p4 = NULL;

	p1=my_malloc(100);
	p2=my_malloc(100);
	my_free(p1);
	p1 = NULL;

	my_free(p2);
	p2 = NULL;

	p1=my_malloc(80);
	my_free(p1);
	p1 = NULL;

	p2=my_malloc(100);
	my_free(p2);
	p2 = NULL;

	p3=my_malloc(100);
}

void test2()
{
	char *p1, *p2, *p3, *p4, *p5;;
	p1 = p2 = p3 = p4 = NULL;
	who_is_free();
	p1=my_malloc(100);
	who_is_free();
	p2=my_malloc(100);
	who_is_free();
	my_free(p2);
	who_is_free();
	return;

	p1=my_malloc(100);
	p2=my_malloc(100);
	my_free(p1);
}

int main()
{
	test2();
}
