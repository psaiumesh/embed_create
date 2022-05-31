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

int add_node_to_free_pool(struct node *p)
{
}

void * init_pool_by_size(char *mem_pool, int size, int count)
{
	char *p = mem_pool;
	struct node *np;
	printf("%d.%s-%s ->size :%d, count :%d\n", __LINE__, __FILE__, __FUNCTION__, size, count);

	for (i = 0; i < count; i++)
	{
		np = p;
		np->flag = 0;
		np->size = size;
		np->buffer = p + sizeof(struct node);
		np->link = NULL;

		add_node_to_free_pool(np)
		
		p = p + (sizeof(struct node) + size);
	}
	return (void *)p;
}

void init_free_pool(void)
{
	int mem_size = 0;
	void *mem_chunk, *mc;

	mem_size = get_memory_requirements();
	printf("%d.%s-%s ->mem_size :%d\n", __LINE__, __FILE__, __FUNCTION__, mem_size);

	mem_chunk = (struct node *)malloc(total_buffer_size);

	mc = mem_chunk;
	for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
	{
		mc = init_pool_by_size(mc, req[i].size, req[i].count);
	}
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
	init_free_pool();
	//initialization();
	//int k;
	//for (k=0;k<10;k++)
	//append();
	//test1();
	//display();
}



