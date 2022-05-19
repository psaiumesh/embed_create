#include<stdio.h>
int f1=0;
int f2=0;
char  b1[100];
char  b2[100];
char *my_malloc(int size)
{
	if((f1==0) && (size <=sizeof(b1)))
	{
		f1=1;
		return(b1);
	}
	if(f2==0 && (size <=sizeof(b2)))
	{
		f2=1;
		return(b2);
	}
	else if(size > sizeof(b1))
	{
		printf("requested memory than avaible  \n");
		
	}
	else
	{
		printf("memory is not there \n");
	}

}
char my_free(char **ptr)
{
	if(f1==1)
	{
		f1=0;
		*ptr=NULL;
	}
	else if(f2==1)
	{
		f2=0;
		*ptr=NULL;
	}

}



int main()
{
	char  *p1=my_malloc(100);
	char  *p2=my_malloc(100);
	my_free(&p1);
	my_free(&p2);
	char *p3=my_malloc(80);
	my_free(&p3);
	char *p4=my_malloc(100);
	my_free(&p4);
	char *p5=my_malloc(100);
	if(p1==b1 || p1==b2)
		printf("p1 is allocated\n");
	if(p2==b2 || p2==b1)
		printf("p2 is allocated\n");
	if(p3==b1 || p3==b2)
		printf("p3 is allocated \n");
	if(p5==b1 || p5==b2)
		printf("p5 is allocated\n");
	}

