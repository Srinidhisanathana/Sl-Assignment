#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    bool mark;
    int refer_count;
    struct node *next1;
    struct node *next2;
    struct node *next3;


}Node;

 Node *pointer_array[8];

void display_node(int i)
{
	printf("value=%d\t reference count=%d freed size=%d\n",pointer_array[i]->data,pointer_array[i]->refer_count,sizeof(Node));
}


void set_edge(int seto,int destination1,int destination2,int destination3)
{
	if(destination1!=-1)
	{
		pointer_array[seto]->next1=pointer_array[destination1];
		pointer_array[destination1]->refer_count+=1;
	}
	if(destination2!=-1)
	{
		pointer_array[seto]->next2=pointer_array[destination2];
		pointer_array[destination2]->refer_count+=1;
	}
	if(destination3!=-1)
	{
		pointer_array[seto]->next3=pointer_array[destination3];
		pointer_array[destination3]->refer_count+=1;
	}

}

void display_all_nodes(Node* root)
{
	if(root!=NULL)
	{
		printf("value=%d:reference count=%d\n",root->data,root->refer_count);
	}
	if(root==NULL)
	{
		return;
	}
	display_all_nodes(root->next1);
	display_all_nodes(root->next2);
	display_all_nodes(root->next3);
}

void adjacency_list()//Represents graph as array of linked lists
{
	int i=0;
	for(i=0;i<8;i++)
	{
		if(pointer_array[i]!=NULL)
		{
			printf("Value=%d: ",pointer_array[i]->data);
			if(pointer_array[i]->next1!=NULL)
			{
				printf("%d ->",pointer_array[i]->next1->data);
			}
			if(pointer_array[i]->next2!=NULL)
			{
				printf("%d ->",pointer_array[i]->next2->data);
			}
			if(pointer_array[i]->next3!=NULL)
			{
				printf("%d ->",pointer_array[i]->next3->data);
			}
			printf("NULL\n");
		}
	}
}

int root_is_present(Node* root1,Node* temp)
{
	if(root1==NULL)
	{
		return 0;
	}
	if(root1->data==temp->data)
	{
		return 1;
	}

	if(root_is_present(root1->next1,temp))
	{
		return 1;
	}

	if(root_is_present(root1->next2,temp))
	{
		return 1;
	}
	if(root_is_present(root1->next3,temp))
	{
		return 1;
	}
 return 0;
}


void garbage_collection_ref_counting(Node* root)
{
	int i=0;
	while(i<8)
	{
		if(root_is_present(root,pointer_array[i])==0 )
		{
			if(pointer_array[i]->next1!=NULL)
			{
				pointer_array[i]->next1->refer_count-=1;
			}
			if(pointer_array[i]->next2!=NULL)
			{
				pointer_array[i]->next2->refer_count-=1;
			}
			if(pointer_array[i]->next3!=NULL)
			{
				pointer_array[i]->next3->refer_count-=1;
			}
			printf("Garbage:");
			display_node(i);
			free(pointer_array[i]);
			pointer_array[i]=NULL;
		}
		 i++;
	}

}

void adjacency_Matrix()
{
	int adm[8][8];
	int i,j,k;

	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			adm[i][j]=0;
		}
	}

	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{

		if(pointer_array[j]!=NULL&&pointer_array[i]!=NULL)
		{

			if(pointer_array[i]->next1!=NULL)
			{
				if(pointer_array[i]->next1->data==pointer_array[j]->data&&i!=j)
				{
					adm[i][j]=1;
				}
			}
			if(pointer_array[i]->next2!=NULL)
			{
				if(pointer_array[i]->next2->data==pointer_array[j]->data&&i!=j)
				{
					adm[i][j]=1;
				}
			}
			if(pointer_array[i]->next3!=NULL)
			{
				if(pointer_array[i]->next3->data==pointer_array[j]->data&&i!=j)
				{
					adm[i][j]=1;
				}
			}
		}

		}
	}

	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			printf("%d ",adm[i][j]);
		}
		printf("\n");
	}
}

void mark_the_Nodes(Node*root,int i,int j)
{
    Node *current, *pre;

    current = root;

    while (current != NULL)
    {

        if (current->next1== NULL)
        {
            current->mark=true;
            current = current->next2;
        }
        else
        {
            pre = current->next1;
            while ((pre->next2 != NULL) && (pre->next2 != current))
            {
            	pre = pre->next2;
			}

            if (pre->next2 == NULL)
            {
                pre->next2 = current;
                current = current->next1;
            }
            else
            {
                pre->next2 = NULL;
                current->mark=true;
                current = current->next2;
            }
        }
    }

    current = root;

    while (current != NULL)
    {

        if (current->next1== NULL)
        {
            current->mark=true;
            current = current->next3;
        }
        else
        {
            pre = current->next1;
            while ((pre->next3 != NULL) && (pre->next3 != current))
            {
            	pre = pre->next3;
			}

            if (pre->next3 == NULL)
            {
                pre->next3 = current;
                current = current->next1;
            }
            else
            {
                pre->next3 = NULL;
                current->mark=true;
                current = current->next3;
            }
        }
    }

}

void mark_method(Node* root)
{

	if(root!=NULL)
	{
		root->mark=true;
	}
	if(root==NULL)
	{
		return;
	}
	mark_method(root->next1);
	mark_method(root->next2);
	mark_method(root->next3);
}

void sweep_method()
{
	int i;
	for(i=0;i<8;i++)
	{
		if(pointer_array[i]->mark==false)
		{
			if(pointer_array[i]->next1!=NULL)
			{
				pointer_array[i]->next1->refer_count-=1;
			}
			if(pointer_array[i]->next2!=NULL)
			{
				pointer_array[i]->next2->refer_count-=1;
			}
			if(pointer_array[i]->next3!=NULL)
			{
				pointer_array[i]->next3->refer_count-=1;
			}
			printf("Garbage:");
			display_node(i);
			free(pointer_array[i]);
			pointer_array[i]=NULL;
		}
	}
}

int main()
{

	int val[]={1,2,3,5,7,8,9,10};
	int i;
    for( i=0;i<8;i++)
	{
		Node* newNode =(Node*)malloc(sizeof(Node));
		newNode->data=val[i];
		newNode->next1=NULL;
		newNode->next2=NULL;
		newNode->next3=NULL;
		newNode->refer_count=0;
		newNode->mark=false;
		pointer_array[i]=newNode;
	}

	Node*root1=pointer_array[3];
	pointer_array[3]->refer_count+=1;
	Node*root2=pointer_array[0];
	pointer_array[0]->refer_count+=1;

	set_edge(0,1,6,7);
	set_edge(2,5,7,-1);
	set_edge(3,0,-1,-1);
	set_edge(4,0,5,-1);
	set_edge(5,6,-1,-1);

	printf("\nAll nodes through Root-1:\n");
	display_all_nodes(root1);

	printf("\nAll nodes through Root-2:\n");
	display_all_nodes(root2);

	printf("\n\nAdjacency list of the nodes with corresponding value or vertex:\n");
	adjacency_list();

	printf("\n\nAdjacency matrix:\n");
	adjacency_Matrix();

	printf("\nCalling the mark and sweep garbage collector\n");

	mark_method(root1);
	sweep_method();

	//printf("\n\nAdj matrix after removal of garbage:\n");
	//adjacency_Matrix();

	//printf("\nCalling reference count Garbage collector\n");
	//garbage_collection_ref_counting(root1);

	printf("\n\nAdjacency list after removal of garbage:\n");
	adjacency_list();

	printf("\n\nAdjacency matrix after removal of garbage:\n");
	adjacency_Matrix();

}
