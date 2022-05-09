#include<stdio.h>
#include<stdlib.h>

int *parent;

void make_set(int no)
{
    int i;
    for(i=0; i<no;i++)
        parent[i] = i;
}

int find(int v)
{
    if(parent[v] == v)
        return v;
    else
        return find(parent[v]);
}

int union_set(int ar_v1, int ar_v2)
{
   if(ar_v1 != ar_v2)
   {
       int x_root = find(ar_v1);
       int y_root = find(ar_v2);
       parent[x_root] = y_root;
   }
   else
    return 0;
}

void main()
{
    int n,ch,v1,v2,v,i,j;
    printf("\nHow many numbers would you like to enter?: ");
    scanf("%d", &n);

    int visited[n];
    for(int i=0; i<n; i++)
    {
       visited[i] = -1;
    }
    parent = (int*)malloc(n*sizeof(int));
    printf("\n\nFollowing are the with one element per set..\n");
    for(int i=0; i<n; i++)
    {
        printf("%d\t", i+1);
    }
    make_set(n);
    while(1)
    {
        printf("\n\nChoose an option: \n");
        printf("1. Union\n2. Find \n3. Show all the sets\n4. Quit");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);


        if(ch == 1)
        {
            printf("\nPerform union between..");
            printf("\nEnter first value: ");
            scanf("%d", &v1);
            printf("Enter second value: ");
            scanf("%d", &v2);
            union_set((v1-1),(v2-1));
            v1 = v2 = 0;
        }
        else if(ch == 2)
        {
            printf("\nEnter element whose parent to be found: ");
            scanf("%d", &v);
            printf("\nParent of %d is %d",v,(find((v-1)))+1);
            v = 0;
        }
        else if(ch == 3)
        {
            int count=0;
            printf("\n----------------------------------------------------------\n\n");
            for(int  i=0;i<n;i++){
                if(visited[i]==-1){
                    printf("\nSet - %d : ",++count);
                    for(int j=0;j<n;j++){
                        if(find(j)==find(i)){
                            printf(" %d ",j+1);
                            visited[j]=1;
                        }
                    }
                }
            }
            printf("\n\n----------------------------------------------------------\n");
        }
        else
        {
            exit(1);
        }
    }

}
