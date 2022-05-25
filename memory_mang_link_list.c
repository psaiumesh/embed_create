#include <stdio.h>
#include <stdlib.h>
struct node
{
	int flag;
	char b[100];
	struct node *link;
};
struct node* root;
void append()
{
	struct node *p;
	struct node *ptr,*ptr1;
	p=(struct node *)malloc(sizeof(struct node));
	p->flag=0;
	p->link=NULL;
	if(root == NULL)
		root=p;
	else
	{
		ptr1=root;
		ptr=root->link;
		while(ptr!=NULL)
		{
			ptr1=ptr;
			ptr=ptr->link;
		}
		ptr1->link=p;
	}
}
void display()
{
	struct node *p;
	p=root;
	while(p!=NULL)
	{
		printf("%d\n",p->flag);
		printf("%p\n",&p->b[100]);
		p=p->link;
	}
}
void *my_malloc(int size)
{
	struct node *p;
	p=root;
	while(p!=NULL)
	{

	if(p->flag ==0 && size <=100)
	{
		p->flag=1;
		return((void *)&p->b);
	}
	p=p->link;
	}

	if(size>100)
	{
		printf("requested more than available \n");
		return NULL;
	}
}
void my_free(void *t)
{
	struct node *p;
	p=root;
	while(p!=NULL)
	{
		if(t==p->b)
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
void who_is_free()
{
	struct node *p;
	p=root;
	while(p!=NULL)
	{
		int i=1;
		if(p->flag==0)
			printf("block%d is free \n",i);
		else
			printf("block%d is allocated \n",i);
		p=p->link;
		i=i+1;
	}
	printf("\n");
}

void test1()
{
	who_is_free();
	char *a1,*a2,*a3,*a4=NULL;
	a1=my_malloc(100);
	a2=my_malloc(100);
	a3=my_malloc(100);
	who_is_free();
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
	int i;
	struct node n;
	for (i=0;i<3;i++)
		append();
	test1();
}

