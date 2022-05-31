#include <stdio.h>
#include <stdlib.h>

struct mem_req
{
	int size;
	int count;
};

struct mem_req req[] = {
	{128, 10},
	{256, 5},
	{512, 20},
	{1024, 8}
};

struct node
{
	int flag;
	int size;
	void *buff;
	struct node *link;
};
struct node *root[5];
void append(void)
{
	int i = 0,j;
	void *buffer;
	struct node *p,*ptr,*ptr1;
	for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
	{

		//printf("size :%d, count :%d\n", req[i].size, req[i].count);
		for (j = 0; j < req[i].count; j++)
		{
			buffer = malloc(req[i].size);
			p = malloc(sizeof(struct node));
			p->flag = 0;
			p->size = req[i].size;
			p->buff = buffer;
			if(root[i]==NULL)
				root[i]= p;
			else
			{
				//printf("hai \n");
				ptr1=root[i];
				ptr=root[i]->link;
				while(ptr!=NULL)
				{
					ptr1=ptr;
					ptr=ptr->link;
				}
				ptr1->link=p;
			}
		}
	}
}
void display()
{
	struct node *p;
	int i=0;
	for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
	{
		p=root[i];
	while(p!=NULL)
	{
		printf("%d\n",p->flag);
		printf("%d\n",p->size);
		printf("%p\n",p->buff);
		p=p->link;
	}
	}
}
void *my_malloc(int size)
{
	struct node *p;
	int i;
	for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
	{
	if(size <=128)
		p=root[0];
	else if (size >(req[i-1].size)&& size <=(req[i].size) )
			p=root[i];
	}

	if(size >1024)
	{
		printf("requested more than available\n");
		return NULL;
	}
	while(p!=NULL)
	{
		if(p->flag==0)
		{
			p->flag=1;
			return((void *)p->buff);
		}
		p=p->link;
	}
}
void my_free(void *t)
{
	int i;
	struct node *p;
	for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
		{
			p=root[i];
			while(p!=NULL)
			{
				if(t==p->buff)
				{
					if(p->flag==1)
					{
					p->flag=0;
					return;
					}
				}
				p=p->link;
			}
		}
}
void who_is_free()
{
struct node *p;
int i,bytes=128;
for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
	{
		int k=1;
		p=root[i];
		printf("%d--->",req[i].size);
		while(p!=NULL)
		{
		if(p->flag==0)
			printf("FREE      \t");
			//printf("block%d is free in %d buffer \n",k,bytes);
		else
			printf("allocated  \t");
			//printf("block%d is allocated in %d buffer \n",k,bytes);
		p=p->link;
		k=k+1;
	}
	bytes=bytes*2;
	printf("\n");
}
}
void test1()
{
	//who_is_free();
//	return;
	char *a1,*a2,*a3,*a4=NULL;
	a1=my_malloc(100);
	a2=my_malloc(150);
	a3=my_malloc(300);
	a4=my_malloc(600);
	who_is_free();
	return;
	my_free(a2);
	who_is_free();
	a4=my_malloc(100);
	who_is_free();
	my_free(a1);
	who_is_free();
	a1=my_malloc(120);
	a2=my_malloc(100);
	who_is_free();
	return;
}
int main()
{
	//initialization();
	//int k;
	//for (k=0;k<10;k++)
	append();
	test1();
	//display();
}



