//20BCE519 Practical 2 : Implement a balanced binary search tree ( AVL) using model 2 ( Node tree) structure

#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    int object;
    int height;
    struct node *right;
    struct node *left;
};

struct node *create(int data,int object)
{
    struct node *newNode;
    newNode=(struct node*)malloc(sizeof(struct node));
    newNode->data=data;
    newNode->object=object;
    newNode->left=newNode->right=NULL;
    newNode->height=1;
    return newNode;
}

int getHeight(struct node *n)
{
    if(n == NULL)
    {
        return 0;
    }
    return n->height;
}

struct node * minValNode(struct node* root)
{
    struct node* current = root;
    while (current->left != NULL)
        current = current->left;
    return current;
}


int getBalFactor(struct node *n)
{
    if(n==NULL)
        return 0;
    return getHeight(n->left) - getHeight(n->right);
}


struct node *rightRotate(struct node *y)
{
    struct node *x=y->left;
    struct node *T2=x->right;

    x->right=y;
    y->left=T2;

    y->height= max(getHeight(y->right),getHeight(y->left)) +1;
    x->height= max(getHeight(x->right),getHeight(x->left)) +1;

    return x;
}


struct node *leftRotate(struct node *x)
{
    struct node *y=x->right;
    struct node *T2=y->left;

    y->left=x;
    x->right=T2;

    y->height= max(getHeight(y->right),getHeight(y->left)) +1;
    x->height= max(getHeight(x->right),getHeight(x->left)) +1;

    return y;
}


struct node *insert(struct node *root,int data,int object)
{
    if(root == NULL)
    {
        return create(data,object);
    }

    if(data < root->data)
    {
        root->left=insert(root->left,data,object);
    }
    else if(data > root->data)
    {
        root->right=insert(root->right,data,object);

    }
    else
    {
        return root;
    }
    root->height=1 + max(getHeight(root->left),getHeight(root->right));
    int balfac=getBalFactor(root);

    //Left Left Rotation
    if(balfac > 1 && data < root->left->data)
    {
        return rightRotate(root);
    }

    //Right Right Rotation
    if(balfac < -1 && data > root->right->data)
    {
        return leftRotate(root);
    }

    //Left Right Rot.
    if(balfac > 1 && data > root->left->data)
    {
        root->left=leftRotate(root->left);
        return rightRotate(root);
    }

    //Right Left Rot.
    if(balfac < -1 && data < root->right->data)
    {
        root->right=leftRotate(root->right);
        return leftRotate(root);
    }
    return root;
}


struct node* deleteNode(struct node* root, int data)
{
    if (root == NULL)
        return root;

    if ( data < root->data )
        root->left = deleteNode(root->left, data);

    else if( data > root->data )
        root->right = deleteNode(root->right, data);

    else
    {
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct node *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                *root = *temp;
                free(temp);
            }
        }
        else
        {
            struct node* temp = minValNode(root->right);
            root->data = temp->data;
            root->object=temp->object;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    if (root == NULL)
        return root;

    root->height = 1 + max(getHeight(root->left),getHeight(root->right));

    int balance = getBalFactor(root);

    if (balance > 1 && getBalFactor(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalFactor(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalFactor(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalFactor(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}


void preorder_tra(struct node *root)
{
    if(root != NULL)
    {
        printf("%d ",root->data);
        preorder_tra(root->left);
        preorder_tra(root->right);
    }
}

void postorder_tra(struct node *root)
{
    if(root != NULL)
    {
        postorder_tra(root->left);
        postorder_tra(root->right);
        printf("%d ",root->data);
    }
}

void inorder_tra(struct node *root)
{
    if(root != NULL)
    {
        inorder_tra(root->left);
        printf("%d ",root->data);
        inorder_tra(root->right);
    }
}

int max(int a,int b)
{
    return a>b?a:b;
}

int main()
{
    struct node *root=NULL;
    printf("\n****************************** Practical 2 : AVL *********************************\n");
    FILE *fn;
    int i,n,num,total,key;
    int a1[100],a2[100];

    fn=fopen("file.txt","w");

    printf("\nEnter Total Numbers :: ");
    scanf("%d",&total);

    for (i=0;i<total;i++)
    {
        num=rand()%100;
        n=rand()%100;
        fprintf(fn,"%d\t%d\n",num,n);
    }
    fclose(fn);

    fn=fopen("file.txt","r");
    for(i=0;i<total;i++)
    {
        fscanf(fn,"%d%2d",&a1[i],&a2[i]);
    }

    int ch;

    while(1)
    {
        printf("\nWhat is to be done ??\n");
        printf("\n  I.Insert Element ");
        printf("\n  ii. Delete Element ");
        printf("\n  iii. Exit The Program ...\n");

        printf("\nEnter your choice in number (1,2, or 3) :: ");
        scanf("%d",&ch);

        switch (ch)
        {
        case 1:
            for(i=0;i<total;i++)
            {
                root=insert(root,a1[i],a2[i]);
            }
            printf("\nPreorder Traversal :: ");
            preorder_tra(root);

            printf("\n---------------------\nInOrder Traversal :: ");
            inorder_tra(root);

            printf("\n---------------------\nPostOrder Traversal :: ");
            postorder_tra(root);
            break;

        case 2:
            printf("\nEnter Element to delete :: ");
            scanf("%d",&key);
            root=deleteNode(root,key);
            printf("\nPreorder Traversal :: ");
            preorder_tra(root);

            printf("\n\nInOrder Traversal :: ");
            inorder_tra(root);

            printf("\n\nPostOrder Traversal :: ");
            postorder_tra(root);
            break;

        case 3:
            printf("\nGoodBye!!!\n\n ");
            return 0;

        default :
            printf("Oops! Invalid Option !!!...!!! \n ");
            break;
        }
        printf("\n");
    }
    return 0;
}
