//Write a program to implement heap management scheme. Implement the ‘allocate’ and ‘free’ functions. Ensure that adjacent free blocks are merged together.

#include<stdio.h>
#include<string.h>

// Two global counters
int gc = 0, kt = 0;


struct freelist
{
    int tag;
    struct freelist* next;//doubly linked list
    struct freelist* prev;
    int size;
}* list_head = NULL, *prev_list = NULL;


struct allocate
{
    int block_id;
    struct allocate* next;
    struct allocate* prev;
    int tag;
    int size;
}* allocate_head = NULL, *prev_allocate = NULL;



// This function prints free blocks of given sizes
void print_freelist()
{
    struct freelist* p = list_head;
    printf("Tag\tSize\n") ;
    while (p != NULL)
    {
        printf("%d\t",p->tag);
        printf("%d\n",p->size);
        p->prev=p;
        p = p->next;

    }
}

// This function prints allocated blocks and their block ids
void print_allocate()
{
    struct allocate* p = allocate_head;
    printf("Tag\tBlock ID\tSize\n");
    while (p != NULL)
    {
        printf("%d\t", p->tag );
        printf("%d\t\t",p->block_id);
        printf("%d\n", p->size) ;
        p->prev=p;
        p = p->next;
    }
}

// This Function is used to create free list with given sizes
void create_freelist(int c)
{
    struct freelist* p = (struct freelist*)malloc(sizeof(struct freelist));

    p->next = NULL;
    p->prev =NULL;
    p->size = c;
    p->tag = gc;
    if (list_head == NULL)
    {
       list_head = p;
    }
    else
    {
       prev_list->next = p;
    }

    prev_list = p;
    gc++;
}

// This function allocates memory blocks as per First fit algorithm
void create_allocate(int c)//allocate function
{

    struct allocate* q = (struct allocate*)malloc(sizeof(struct allocate));
    q->size = c;
    q->tag = kt;
    q->next = NULL;
    struct freelist* p = list_head;

    // We need to Iterate to find first memory block with appropriate size as per first fit algorithm
    while (p != NULL)
    {
        if (q->size <= p->size)
             break;
        p->prev=p;
        p = p->next;
    }

    // Node is founded to allocate
    if (p != NULL)
    {
        // Adding node to allocated list
        q->block_id = p->tag;
        p->size -= q->size;
        if (allocate_head == NULL)
        {
            allocate_head = q;
        }

        else
        {
            prev_allocate = allocate_head;
            while (prev_allocate->next != NULL)
            {
               prev_allocate = prev_allocate->next;
            }

            prev_allocate->next = q;
        }
        kt++;
    }
    else
        printf("Block of size %d cannot be allocated\n",c);

}

// This Function is used to delete node from allocated list to free some space
void delete_allocate(int t)//free function
{
    // delete function of a linked list node
    struct allocate *p = allocate_head, *q = NULL;

    // find the node according to given tag id
    while (p != NULL)
    {
        if (p->tag == t)
            break;
        q = p;
        p->prev=p;
        p = p->next;
    }
    if (p == NULL)
    {
        printf("Tag does n't exist");
    }

    else if (p == allocate_head)
    {
        allocate_head = allocate_head->next;
    }

    else
    {
        q->next = p->next;
    }
    struct freelist* temp = list_head;
    //merging the adjacent free blocks
    while (temp != NULL)
    {
        if (temp->tag == p->block_id)
        {
            temp->size += p->size;
            break;
        }
        temp = temp->next;
    }

}


int main()
{

    int blockSize[] = { 123, 450, 200, 80, 23 };
    int processSize[] = { 448, 111, 226, 195 };

    int m = sizeof(blockSize)/ sizeof(blockSize[0]);
    int n = sizeof(processSize)/ sizeof(processSize[0]);
    for (int i = 0; i < m; i++)
    {
        create_freelist(blockSize[i]);
    }


    for (int i = 0; i < n; i++)
    {
        create_allocate(processSize[i]);
    }


    print_allocate();

    // Block of tag id 0 deleted
    // to free space for block of size 426
    delete_allocate(0);

    create_allocate(400);

    printf("Deleting block with tag id 0.\n");
    print_allocate();
}
