//Practical 8
#include<stdio.h>
#include<stdlib.h>

int *par;

void makeSet(int no)
{
    int i;
    for(i=0; i<no;i++)
        par[i] = i;
}

int find(int v)
{
    if(par[v] == v)
        return v;
    else
        return find(par[v]);
}

int unionSet(int ar_v1, int ar_v2)
{
   if(ar_v1 != ar_v2)
   {
       int x_root = find(ar_v1);
       int y_root = find(ar_v2);
       par[x_root] = y_root;
   }
   else
    return 0;
}

void main()
{
    int n,ch,v1,v2,v,i,j;
    printf("\nHow many numbers would you like to enter ? :: ");
    scanf("%d", &n);

    int visited[n];
    for(int i=0; i<n; i++)
    {
       visited[i] = -1;
    }
    par = (int*)malloc(n*sizeof(int));
    printf("\n\nFollowing are the structure with one element per set..\n");
    for(int i=0; i<n; i++)
    {
        printf("%d\t", i+1);
    }
    makeSet(n);
    while(1)
    {
        printf("\n\nChoose an option :: \n");
        printf("i. Union\nii. Find \niii. Show all the sets\niv. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);


        if(ch == 1)
        {
            printf("\nPerform union between :: ");
            printf("\nEnter first value :: ");
            scanf("%d", &v1);
            printf("Enter second value :: ");
            scanf("%d", &v2);
            unionSet((v1-1),(v2-1));
            v1 = v2 = 0;
        }
        else if(ch == 2)
        {
            printf("\nEnter element whose parent is to be found :: ");
            scanf("%d", &v);
            printf("\npar of %d is :: %d",v,(find((v-1)))+1);
            v = 0;
        }
        else if(ch == 3)
        {
            printf("\n***********************\n\n");
            int count = 1,open=0;
            for(i=0; i<n; i++)
            {
                if(visited[i] == -1)
                {
                    printf("Set-%d :: { ", count);
                    open = 1;
                    count++;
                }
                int p = find(i);
                for(j=0; j<n; j++)
                {
                    if(find(j) == p && visited[j] != 0)
                    {
                        visited[j] = 0;
                        printf("%d ", j+1);
                    }
                }
                if(open == 1)
                {
                    printf("}");
                    printf("\n");
                    open = 0;
                }
            }
            printf("\n\n***********************\n");
        }
        else
        {
            exit(1);
        }
    }

}
