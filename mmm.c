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

struct node *HL[5];

int get_memory_requirements()
{
	int total_buffer_size = 0;
	int i = 0;
	for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
		total_buffer_size = total_buffer_size + (req[i].size * req[i].count);
	return total_buffer_size;
}

int add_node_to_free_pool(struct node *p1,int j1)
{
	struct node *ptr,*ptr1;
		if(HL[j1]==NULL)
			HL[j1]=p1;
		else
		{
			ptr1=HL[j1];
			ptr=HL[j1]->link;
			while( ptr!=NULL)
			{
			ptr1=ptr;
			ptr=ptr->link;
			}
			ptr1->link=p1;
		}

}


void * init_pool_by_size(char *mem_pool, int size, int count,int j)
{
	char *p = mem_pool;
	struct node *np;
	int k=0;
	printf("%d.%s-%s ->size :%d, count :%d\n", __LINE__, __FILE__, __FUNCTION__, size, count);

	for (k = 0; k < count; k++)
	{
		np = (struct node *)p;
		np->flag = 0;
		np->size = size;
		np->buff = p + sizeof(struct node);
		np->link = NULL;

		add_node_to_free_pool(np,j);
		
		p = p + (sizeof(struct node) + size);
	}
	return (void *)p;
}

void init_free_pool(void)
{
	int mem_size = 0,i=0;
	void *mem_chunk, *mc;

	mem_size = get_memory_requirements();
	printf("%d.%s-%s ->mem_size :%d\n", __LINE__, __FILE__, __FUNCTION__, mem_size);

	mem_chunk = (struct node *)malloc(mem_size);

	mc = mem_chunk;
	for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
	{
		mc = init_pool_by_size(mc, req[i].size, req[i].count,i);
	}
}

void *my_malloc(int size)
{
	struct node *p;
	int i;
	for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
	{
	if(size <=128)
		p=HL[0];
	else if (size >(req[i-1].size)&& size <=(req[i].size) )
			p=HL[i];
	}

	if(size >1024)
	{
		printf("requested more than available\n");
		return NULL;
	}
	while(p!=NULL || p!=HL[i+1])
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
	int i=0;
	struct node *p;
			p=HL[i];
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
void who_is_free()
{
struct node *p;
int i,bytes=128;
for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
	{
		int k=1;
		p=HL[i];
		printf("%d--->",req[i].size);

		while( p!=NULL)
		{
			if(p->flag==0)
				printf("block%d is free in %d buffer \n",k,bytes);
			else
				printf("block%d is allocated in %d buffer \n",k,bytes);
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

void display()
{
	struct node *p;
	int i=0;
	for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
	{
		p=HL[i];
		printf("hash list :%p\n",HL[i]);
		while(p!=NULL)
		{
		//	printf("%d\n",p->flag);
		//	printf("%d\n",p->size);
		//	printf("%p\n",p->buff);
			p=p->link;
		}
	}
}

int main()
{
	init_free_pool();
	//initialization();
	//int k;
	//for (k=0;k<10;k++)
	//append();
	test1();
	//display();
}



