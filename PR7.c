//PRACTICAL 7 . Implement heap data structure using linked list structure. The list should retrieve high priority object every time the
//extract operation is performed.

#include<stdio.h>
#include<stdlib.h>


struct node
{
    int key;
    int prior;
    struct node *next;
};

struct node *HEAD = NULL;

struct node *CREATE_NODE(int k, int p)
{
    struct node *temp1 = (struct node*)malloc(sizeof(struct node));
    temp1->key = k;
    temp1->prior = p;
    temp1->next = NULL;

    return temp1;
}

void INSERT(int key, int pri)
{
    struct node *START = HEAD;

    struct node *nd1 = CREATE_NODE(key,pri);

    //if inserting node's priority is more than the head node
    if(HEAD == NULL)
    {
        HEAD = nd1;
    }
    else if(HEAD->prior > pri)
    {
        nd1->next = HEAD;
        HEAD = nd1;
    }
    else
    {
        while(START->next != NULL && START->next->prior <= pri)
        {
            START = START->next;
        }

        nd1->next = START->next;
        START->next = nd1;
    }
}

//removes a node from the list
void REMOVE()
{
    if(HEAD != NULL)
    {
        printf("\n\nKey = %d, Priority = %d\n", HEAD->key, HEAD->prior);
        HEAD = HEAD->next;
    }
    else
    {
        printf("\nLIST IS EMPTY\n\n");
    }
}
void main()
{
    int choice, p, k;
    printf("\n\n********************* PRIORITY HEAP(LINKED LIST) *********************\n");
    printf("\nNote: Lower the No., Higher the Priority\n\n");
    do
    {
        printf("\nChoose an Operation :: \ni. Insertion \nii. Extraction \niii. Exit\n");
        printf("\nEnter you choice: ");
        scanf("%d", &choice);

        if(choice == 1)
        {
            printf("\nEnter Key :: ");
            scanf("%d", &k);
            printf("Enter Priority :: ");
            scanf("%d", &p);
            INSERT(k,p);
        }
        else if(choice == 2)
        {
            printf("\n\n**** EXTRACTING ****");
            REMOVE();
        }
        else
        {
            exit(1);
        }
    } while (1);



}
