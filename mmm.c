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
	struct node a;
	//printf("buff size is :%ld\n",sizeof(a.link));
	//printf("%ld\n",sizeof(req));
	//printf("%ld\n",sizeof(struct node));

	int i = 0,j,total_buffer_size=0;
	void *p;
	int *q,x;
	struct node *ptr,*ptr1;

	for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
		total_buffer_size = total_buffer_size + (req[i].size * req[i].count);

	//printf("%d\n",total_buffer_size);
	//return;
	mem_pool = (struct node *)malloc(total_buffer_size);
	printf("%p\n",p);
	for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
	{
		for (j = 0; j < req[i].count; j++)
		{
			q=(int *)p;
			printf("%p\n",q);
			//printf("hello\n");
			p->flag=0;
			p->size=req[i].size;
			x=sizeof(struct node );

			printf("%ld\n",sizeof(struct node));
			p->buff = q + x;
			//return;
			printf("%p\n",p->buff);
			//printf("%d\n",(p->buff)- p);
			return;
			p->link=NULL;
			if(root[i]==NULL)
				root[i]=p;
			else
			{
				printf("hai \n");

				ptr1=root[i];
				ptr=root[i]->link;
				while( ptr!=NULL)
				{
					ptr1=ptr;
					ptr=ptr->link;
				}
				ptr1->link=p;
			}
			p=p+sizeof(struct node) + req[i].size;
		}
		printf("j is %d\n",j);
		printf("i is %d\n",i);
	}
	printf("i is %d\n",i);
}

void display()
{
	struct node *p;
	int i=0;
	for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
	{
		p=root[i];
		while(p!=root[i+1] || p!=NULL)
		{
			printf("%d\n",p->flag);
			printf("%d\n",p->size);
			printf("%p\n",p->buff);
			p=p->link;
		}
	}
}

int main()
{
	//initialization();
	//int k;
	//for (k=0;k<10;k++)
	append();
	//test1();
	display();
}



