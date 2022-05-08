//20bce519 Practical 2:  Shadow Copying Technique
#include<stdio.h>
#define threshold 0.5

int top=-1;
int size=10;
int count=0;

int main()
{
    FILE *fn,*fp;
    int num,n,i;
    int numbers[500];

    printf("What is the Total Number? :: ");
    scanf("%d",&n);

    fn=fopen("file.txt","w");
    for (i=0;i<n;i++)
    {
        num=rand()%100;
        fprintf(fn,"%d\n",num);
    }
    fclose(fn);

    fn=fopen("file.txt","r");
    for (int i=0;i<n;++i)
    {
        fscanf(fn,"%d",&numbers[i]);
    }

    int *stack = (int *) malloc(sizeof(int) * size);

    int ch;
    while(1)
    {
        printf("\n\nOperations on Stack :: ");
		printf("\n1.Push an element\n2.Pop an element\n3.Show Stack \n4.Terminate Prog...");
		printf("\n\nWhat would you like to do? :: ");
		scanf("%d",&ch);

        switch(ch)
        {
        case 1:
            push_stack(stack,numbers);
            break;

        case 2:
            pop_stack(stack);
            break;

        case 3:

            display(stack);
            break;

        case 4:
            exit(0);
        default:
            printf("/nOops! Wrong Choice!!!\n");
        }
    }
    return 0;
}

void push_stack(int arr[],int numbers[])
{
    int ch;

    if(top == threshold*size -1)
    {
        printf("Threshold Reached.... Want to increase size of stack (Yes Or No?? 1,0): ");
        scanf("%d",&ch);

        if(ch == 1)
        {
            int* new_stack = (int *) malloc(sizeof(int) * size);
            for(int i = 0; i < count; i++)
            {
                new_stack[i] = arr[i];
            }
            if(count != 0)
                size=size*2;
            printf("Stack Size :: %d",size);
            return new_stack;
        }
        else{
            return arr;
        }
    }
    else
    {
        top++;
        arr[top]=numbers[top];
        count+=1;
    }
    return arr;
}

void pop_stack(int stack[])
{
    printf("Element Popped :: %d",stack[top]);
    top--;
}
void display(int stack[])
{
    if(top ==-1)
    {
        printf("\nOops! Stack is Empty !!! ");
        return ;
    }

    for(int i=top;i>=0;i--)
    {
        printf("%d",stack[i]);
        printf("\n");
    }
}
