#include<stdio.h>
#define BUFFER_SIZE 3
char *ptr[3];
char b3[100];
char  b1[100];
char  b2[100];
int f[10];
int i=0;
char *p1, *p2,*p3,*p4,*p5=NULL;
void initialization()
{
		ptr[0]=b1;
	ptr[1]=b2;
	ptr[2]=b3;
	int k;
	for (k=0;k<BUFFER_SIZE;k++)
		f[k]=0;
}
void * my_malloc(int size)
{
	int k;
	for(k=0;k<BUFFER_SIZE;k++)
	{
		if((f[k]==0) && (size <=100))
		{
			f[k]=1;
			return((void *)ptr[k]);
    	}
		if(size > 100)
		{
			printf("requested memory more than avaible\n");
			return NULL;
		}
	}
}
void my_free(void *t)
{
	for(i=0;i<BUFFER_SIZE;i++)
	{
		if(t==ptr[i])
		{
			if(f[i]==1)
			{
				f[i]=0;
				return;
	 	    }
     	}
	}

}
void who_is_free()
{
	 for(i=0;i<BUFFER_SIZE;i++)
	 {
		if(f[i]==0)
			printf(" block%d is free \n",(i+1));
		else
			printf(" block%d is allocated \n",(i+1));
	}
	printf("\n");
}
void test1()
{
	initialization();
	who_is_free();
	p1=my_malloc(100);
	p2=my_malloc(100);
	p3=my_malloc(100);
	who_is_free();
	my_free(p2);
	who_is_free();
	p4=my_malloc(100);
	who_is_free();
	my_free(p1);
	who_is_free();
	p1=my_malloc(120);
	p2=my_malloc(100);
	who_is_free();
	return;
}

int main()
{
	test1();
}
