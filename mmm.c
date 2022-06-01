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
    {1024, 8},
};

struct node
{
    int flag;
    int size;
    void *buff;
    struct node *link;
};

struct mem_pool
{
    int total_available;
    int free;
    int allocation;
    int total_malloc_called;
    int total_free_called;
    int total_misses;
    int double_free;
    struct node *l;
};

struct mem_pool HL[4];

void initialization()
{
    int i;
    for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
    {
        HL[i].total_available = req[i].count;
        HL[i].free = req[i].count;
        HL[i].allocation=0;
        HL[i].total_malloc_called=0;
        HL[i].total_free_called=0;
        HL[i].total_misses=0;
    }
}

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

    if(HL[j1].l == NULL)
    {
        HL[j1].l=p1;
        return 0;
    }

    //TODO: Why to insert at the end, why not at beginning?
    ptr1=HL[j1].l;
    ptr=(HL[j1].l)->link;
    while( ptr!=NULL)
    {
        ptr1=ptr;
        ptr=ptr->link;
    }
    ptr1->link=p1;
}


void * init_pool_by_size(char *mem_pool, int size, int count,int j)
{
    char *p = mem_pool;
    struct node *np;
    int k=0;
    //printf("%d.%s-%s ->size :%d, count :%d\n", __LINE__, __FILE__, __FUNCTION__, size, count);
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

    initialization();

    mem_size = get_memory_requirements();
    //printf("%d.%s-%s ->mem_size :%d\n", __LINE__, __FILE__, __FUNCTION__, mem_size);

    mem_chunk = (struct node *)malloc(mem_size);

    mc = mem_chunk;
    for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
    {
        mc = init_pool_by_size(mc, req[i].size, req[i].count,i);
    }
}

void count(int i)
{
    HL[i].free = HL[i].free - 1;
    HL[i].allocation = HL[i].allocation + 1;
    HL[i].total_malloc_called=HL[i].total_malloc_called + 1;
}

void count_free(int i)
{
    HL[i].free=HL[i].free +1 ;
    HL[i].total_free_called=HL[i].total_free_called + 1;
    HL[i].allocation = HL[i].allocation - 1;

}


void *my_malloc(int size)
{
    struct node *p;
    int i,count_nodes=0;
    for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
    {
        if(size <=128)
        {
            p=HL[0].l;
            break;
        }

        else if (size >(req[i-1].size)&& size <=(req[i].size) )
        {
            p=HL[i].l;
            break;
        }
    }
    if(size >1024)
    {
        printf("requested more than available\n");
        return (void *)NULL;
    }
    while(p!=NULL )
    {
        if(p->flag==0)
        {
            count(i);
            p->flag=1;
            return((void *)p->buff);
        }
        count_nodes=count_nodes+1;

        p=p->link;

    }
    if(count_nodes==req[i].count)
        HL[i].total_misses=HL[i].total_misses+1;

}

void my_free(void *t)
{
    int i=0;
    struct node *p;
    for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
    {
        p=HL[i].l;
        while(p!=NULL)
        {
            if(t==p->buff)
            {
                if(p->flag==1)
                {
                    count_free(i);
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
    printf("\t\tpool_count, free_count, avbl_count, tot_malloc_count, tot_free_count, total_miss\n");
    for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
    {
        int k=1;
        p=HL[i].l;
        printf("%5d-->",req[i].size);
        printf("(%2d %2d %2d %2d %2d %2d)>",
                HL[i].total_available,
                HL[i].free,
                HL[i].allocation,
                HL[i].total_malloc_called,
                HL[i].total_free_called,
                HL[i].total_misses);
 
        while( p!=NULL)
        {
            printf("%3s", (p->flag==0 ? "F" : "A"));
            p=p->link;
            k=k+1;
        }
        bytes=bytes*2;
        printf("\n");
    }
    printf("\n");
}

void count_check()
{
    int i;

    for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
    {
        printf("%d--->",req[i].size);
        printf("total avaialable :%d \t",HL[i].total_available);
        printf("free :%d \t",HL[i].free);
        printf("allocated ; %d \t",HL[i].allocation);
        printf("total_malloc _called :%d \t",HL[i].total_malloc_called);
        printf("total_free_called :%d \t",HL[i].total_free_called);
        printf("total misses : %d \t",HL[i].total_misses );
        printf("\n");
    }
}


void test1()
{
    char *a1,*a2,*a3,*a4,*a5,*a6,*a7=NULL;
    who_is_free();
    a1=my_malloc(150);
    a2=my_malloc(180);
    a3=my_malloc(200);
    a4=my_malloc(220);
    my_free(a2);
    my_free(a2);
    who_is_free();
    return;
    //who_is_free();
    //count_check();
    //return;
    a5=my_malloc(240);
    //who_is_free();
    //my_free(a1);
    //	who_is_free();
    a6=my_malloc(230);
    a7=my_malloc(210);
    //my_free(a3);
    //my_free(a4);
    who_is_free();
    count_check();
    return;
}

void display()
{
    struct node *p;
    int i=0;
    for (i = 0; i < sizeof(req)/sizeof(struct mem_req); i++)
    {
        //	p=HL[i].l;
        //	printf("hash list :%p\n",HL[i].l);
        //	while(p!=NULL)
        //	{
        printf("%p\n",HL[i].l);
        //	printf("%d\n",p->size);
    }
}

int main()
{
    init_free_pool();
    test1();
}



