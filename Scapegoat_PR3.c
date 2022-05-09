//20BCE519 Practical 3 : Implement scapegoat tree to demonstrate the partial rebuilding operation.

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int q,n=0;

struct node
{
    float key;
    struct node *right;
    struct node *left;
    struct node *parent;
};
struct node *root=NULL;

struct node *create(float key)
{
    struct node *newNode;
    newNode=(struct node*)malloc(sizeof(struct node));
    newNode->key=key;
    newNode->left=newNode->right=newNode->parent=NULL;
    return newNode;
}

struct node * minValueNode(struct node* root)
{
    if(root == NULL)
        return NULL;
    else if(root->left != NULL)
        return minValueNode(root->left);
    return root;
}


int size(struct node *node)
{
    if(node == NULL)
        return 0;
    return 1 + size(node->left) + size(node->right);
}

static int const logvalue32(int n)
{

    return log10(n)/log10(1.5);

}


int store_inorder(struct node *ptr,struct node *arr[],int i)
{
    if(ptr==NULL)
        return i;

    i=store_inorder(ptr->left,arr,i);
    arr[i++]=ptr;
    return store_inorder(ptr->right,arr,i);
}


struct node *buildBalancedFromArray(struct node *a[],int i,int n)
{
    if(n==0)
        return NULL;

    int m=n/2;

    //Left sub-tree
    a[i+m]->left = buildBalancedFromArray(a, i, m);

    if (a[i+m]->left != NULL)
        a[i+m]->left->parent = a[i+m];

    //Right sub-tree
    a[i+m]->right = buildBalancedFromArray(a, i+m+1, n-m-1);

    if (a[i+m]->right != NULL)
        a[i+m]->right->parent = a[i+m];

    return a[i+m];
}

struct node *rebuild(struct node *n)
{
    int size1= size(n);

    struct node *p=n->parent;
    struct node *a[size1];
    store_inorder(n,a,0);
    if (p == NULL)
    {
        root = buildBalancedFromArray(a, 0, size1);
        root->parent = NULL;
    }
    else if (p->right == n)
    {
        p->right = buildBalancedFromArray(a, 0, size1);
        p->right->parent = p;
    }
    else
    {
        p->left = buildBalancedFromArray(a, 0, size1);
        p->left->parent = p;
    }
}


struct node *insert(float key)
{
    struct node *newNode = create(key);

    int depth=insert_find_depth(newNode);

    printf("\nDepth :: %d",depth);

    if(depth > logvalue32(n))
    {
        struct node *p = newNode->parent;
        while(3 * size(p) <= 2 * size(p->parent))
        {
            p=p->parent;
        }
        rebuild(p->parent);
        printf("\n\n !!!!!! Threshold Reached !!!!!! \n");
    }
    return depth >= 0;
}

int insert_find_depth(struct node *newNode)
{
    struct node *w=root;
    if(w == NULL)
    {
        root=newNode;
        n++;
        q++;
        return 0;
    }

    int d=0;

    int done = 0;
    do
    {
        if(newNode->key <  w->key)
        {
            if (w->left == NULL)
            {
                w->left = newNode;
                newNode->parent = w;
                done=1;
            }
            else
            {
                w = w->left;
            }
        }
        else if (newNode->key > w->key)
        {
            if (w->right == NULL)
            {
                w->right = newNode;
                newNode->parent = w;
                done=1;
            }
            else
            {
                w = w->right;
            }
        }
        else
        {
            return -1;
        }
        d++;
    }
    while(done!=1);

    n++;
    q++;

    return d;
}

struct node *inorderPred(struct node *r)
{
    r=r->right;
    while(r->left)
    {
        r=r->left;
    }
    return r;
}

struct node *BSTdelete(struct node *root, float key)
{
    if (root == NULL)
        return root;

    if ( key < root->key )
        root->left = BSTdelete(root->left, key);

    else if( key > root->key )
        root->right = BSTdelete(root->right, key);

    else
    {
        if(!root->left)
        {
            struct node* temp=root->right;
            return temp;
        }
        else if(!root->right)
        {
            struct node* temp=root->left;
            return temp;
        }
        struct node *temp = inorderPred(root);
        root->key=temp->key;
        root->left=BSTdelete(root->left,temp->key);
    }
    return root;
}

void deleteNode(struct node *root,float key)
{
    root=BSTdelete(root,key);
    n--;

    if(q>2*n)
    {
        rebuild(root);
        q=n;
    }

    printf("\nDeleted Key :: %.1f \n",key);
}
void preorder_tra(struct node *root)
{
    if(root != NULL)
    {
        printf("%.1f ",root->key);
        preorder_tra(root->left);
        preorder_tra(root->right);
    }
}


int main()
{
    float key;
    int ch;
    printf("\n******************************Practical 3*********************************\n");

    while(1)
    {   printf("\n\nWhat would you like to do ?? \n ");
        printf("\n i. Insertion");
        printf("\n ii. Deletion");
        printf("\n iii. Count The Nodes");
        printf("\n iv. Exit\n");

        printf("\nEnter choice :: ");
        scanf("%d",&ch);

        switch (ch)
        {
        case 1:
            printf("\nEnter Element for insertion :: ");
            scanf("%f",&key);
            insert(key);
            break;

        case 2:
            printf("\nEnter Element for deletion :: ");
            scanf("%f",&key);
            deleteNode(root,key);
            break;

        case 3 :
            printf("\nNumber of Nodes :: %d",size(root));
            break;

        case 4:
            printf("\nGoodBye!!!\n\n ");
            return 0;

        default :
            printf("Oops! Invalid Option !!!...!!! \n ");printf("Invalid\n ");
            break;
        }

        printf("\nPreorder Traversal  :: ");
        preorder_tra(root);
    }
    return 0;
}
