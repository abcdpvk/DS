#include <stdio.h>
#include<conio.h>
#include <stdlib.h>
#define TABLE_SIZE 10

struct node

{
    int data;
    struct node *next;
};

struct node *head[TABLE_SIZE]={NULL},*c;

void INSERT()
{
    int i,key;
    printf("Enter a value to insert into hash table :: ");
    scanf("%d",&key);
    i=key%TABLE_SIZE;
    struct node * newnode=(struct node *)malloc(sizeof(struct node));
    newnode->data=key;
    newnode->next = NULL;
    if(head[i] == NULL)
		head[i] = newnode;
    else
    {
		c=head[i];
		while(c->next != NULL)
		{
   			c=c->next;
		}
		c->next=newnode;

    }

}

void DELETE()
{
    int key,index;
    printf("Enter the element to be deleted :: ");
    scanf("%d",&key);
    index=key%TABLE_SIZE;
    if(head[index] == NULL)
		printf("\nElement not found!!! ");
    else
    {
		for(c=head[index]; c!=NULL; c=c->next)
		{
			if(head[index]->data == key)
			{
				head[index] = head[index]->next;
				break;
			}
			else if(c->next->data == key)
			{
				if(c->next->next == NULL)
				{
					c->next = NULL;
					break;
				}
				else
				{
					c->next = c->next->next;
					break;
				}
			}
		}
		if(c==NULL)
			printf("\nElement not found!!!");
    }
}

void DISPLAY()
{
    int i;
    for(i=0;i<TABLE_SIZE;i++)
  	{
		printf("\nEntries at index :: %d: ",i);
		if(head[i] == NULL)
		{
			printf("No Hash Entry!!!");
		}
		else
		{
      		for(c=head[i];c!=NULL;c=c->next)
      		printf("%d->",c->data);
        }
    }

}

void main()
{
    int opt,key,i;
	printf("\n\n******** Collision Resolution Using Separate Chaining ********\n\n");
    while(1)
    {
		printf("\n\ni.Insert\nii.Display\niii.Delete\niv.Exit\n\nEnter choice:");
		scanf("%d",&opt);
		switch(opt)
		{
			case 1:
				INSERT();
				break;
    		case 2:
				DISPLAY();
				break;
    		case 3:
				DELETE();
				break;
    		case 4:
				exit(0);
    		default:
    			printf("Enter Valid Choice!!!");
		}

	}

}
