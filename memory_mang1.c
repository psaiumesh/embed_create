#include<stdio.h>
int f1=0;
int f2=0;
int f3=0;
char b3[100];
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
	if(f3==0 && (size <=sizeof(b2)))
	{
		f3=1;
		return((void *)b3);
	}


	if(size > sizeof(b1))
	{
		printf("requested memory more than avaible\n");
		f1=0;
		return NULL;
	}
	if(size >sizeof(b2))
	{
		printf("requested memory more than available\n");
		f2=0;
		return NULL;
	}
	if(size > sizeof(b3))
	{
		printf("requested memory more than avialable\n");
		f3=0;
	}

	else
	{

		printf("memory is not there \n");
		return NULL;
	}


}

void my_free(void *ptr)
{
	if(ptr==b1)
	{
		if(f1==1)
		{
			f1=0;
			return;
		}
	}



	
	if (ptr==b2)
	{

		if(f2==1)
		{
			f2=0;
			//return;
		}
	}
	if(ptr==b3)
	{
		if (f3==1)
		{
			f3=0;
			return;
		}
	}

}



void who_is_free()
{
	//printf("f1 is %d\n",f1);
	//printf("f2 is %d\n",f2);
	if(f1==0)
		printf("B1 is FREE\n");
	else
		printf("B1 is ALLOCED\n");

	if(f2==0)
		printf("B2 is FREE\n");
	else
		printf("B2 is ALLOCED\n");
	if(f3==0)
		printf("b3 is free \n");
	else
		printf("b3 is allotted \n");
	printf("\n");
}


void test2()
{
	char *p1, *p2,*p3,*p4,*p5;
	p1 = p2 = p3 = p4 = NULL;
	who_is_free();
	p1=my_malloc(100);
	p2=my_malloc(100);
	p3=my_malloc(100);
	who_is_free();
	//return;
	my_free(p2);
	p2=NULL;
	who_is_free();
	//return;
	p3=my_malloc(100);
	who_is_free();
	return;
	//p3=my_malloc(100);
	//who_is_free();
	//return;

	//my_free(p2);
	//p2=NULL;
	//who_is_free();
	//return;
	my_free(p1);
	p1=NULL;
	who_is_free();
	//return;
	p1=my_malloc(120);
	p2=my_malloc(100);
	who_is_free();
	my_free(p1);
	//return;


	who_is_free();
	return;
}

int main()
{
	test2();
}
