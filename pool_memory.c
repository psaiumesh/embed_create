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
	struct node *next;
};

void dump_mem_requirements(void)
{
	int i = 0;
	for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
	{
		printf("size :%d, count :%d\n", req[i].size, req[i].count);
	}
}

void init_free_pool(void)
{
	int i = 0;
	void *buff;
	struct node *pnode;
	for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
	{
		printf("size :%d, count :%d\n", req[i].size, req[i].count);
		for (j = 0; j < req[i].count; j++)
		{
			buff = malloc(req[i].size);
			pnode = malloc(sizeof(struct node));
			pnode->flag = 1;
			pnode->size = req[i].size;
			pnode->buff = buff;
			pnode->next = NULL;
		}
	}
}


#if 0
struct node *H[5];
void append()
{
	struct node *p,*ptr,*ptr1;
	if(i<=4)
	{
		p=(struct node *)malloc(sizeof(struct node));
		p->flag=0;
		p->size=128;
		p->q=(struct node *)a[i];
		if(root1==NULL)
			root1=p;
		else
		{
			ptr1=root1;
			ptr=root1->link;
			while(ptr!=NULL)
			{
			ptr1=ptr;
			ptr=ptr->link;
			}	
			ptr1->link=p;
		}
	}
	else if (i>4 && i<=9)
	{
		p=(struct node  *)malloc(sizeof(struct node));
		p->flag=0;
		p->size=256;
		p->q=(struct node *)a[i];
		if(root2==NULL)
			root2=p;
		else
		{
			ptr1=root2;
			ptr=root2->link;
			while(ptr!=NULL)
			{
				ptr1=ptr;
				ptr=ptr->link;
			}
			ptr1->link=p;
		}
	}
	i=i+1;
}
void display()
{
	struct node *p;
	p=root1;
	while(p!=NULL)
	{
		printf("%d\n",p->flag);
		printf("%d\n",p->size);
		printf("%p\n",p->q);
		p=p->link;
	}
	p=root2;
	while(p!=NULL)
	{
		printf("%d\n",p->flag);
		printf("%d\n",p->size);
		printf("%p\n",p->q);
		p=p->link;
	}

}
void *my_malloc(int size)
{
	struct node *p;
	if(size <=128)
		p=root1;
	else if (size >128 && size <=256)
		p=root2;
	if(size <=256)
	{
		while(p!=NULL)
	{
		if(p->flag==0)
		{
			p->flag=1;
			return((void *)p->q);
		}
		p=p->link;
	}
	}

	if(size > 256)
	{
		printf("requested more than available \n");
		return NULL;
	}
}
void my_free(void *t)
{
	struct node *p;
	char *root[2];
	int j;
	root[0]=(char *)root1;
	root[1]=(char *)root2;
	for(j=0;j<2;j++)
	{
		p=(struct node *)root[j];
		while(p!=NULL)
		{
			if(t==p->q)
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
	int i,j,bytes=128;
	char *root[2];
	root[0]=(char *)root1;
	root[1]=(char *)root2;
	for(j=0;j<2;j++)
	{
		i=1;
		p=(struct node *)root[j];
	while(p!=NULL)
	{
		if(p->flag==0)
			printf("block%d is free in %d buffer \n",i,bytes);
		else
			printf("block%d is allocated in %d buffer \n",i,bytes);
		p=p->link;
		i=i+1;
	}
	bytes=bytes+128;
	printf("\n");
}
}
void test1()
{
	who_is_free();
	char *a1,*a2,*a3,*a4=NULL;
	a1=my_malloc(100);
	a2=my_malloc(100);
	a3=my_malloc(130);
	a4=my_malloc(156);
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
#endif

int main()
{
	dump_mem_requirements();
#if 0
	initialization();
	int k;
	for (k=0;k<10;k++)
		append();
	test1();
#endif
}


