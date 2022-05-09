#include <stdio.h>
#include <stdlib.h>

int ind = 0;
struct node
{
    int key;
    struct node *left;
    struct node *right;
};

struct node *ROOT = NULL;
struct node **keys;

struct node *CREATE_NODE(int k)
{
    struct node *n = (struct node *)malloc(sizeof(struct node));
    n->key = k;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void GET_KEYS(struct node *n2)
{
    if(n2 != NULL)
    {
        struct node *t1 = n2;
        GET_KEYS(t1->left);
        keys[ind++] = t1;
        GET_KEYS(t1->right);
    }
}

//inserting keys into the BST
void INSERT(struct node *new_node)
{
    struct node *n1 = ROOT;
    int inserted = 0;
    if(n1 == NULL)
    {
        ROOT = new_node;
    }
    else
    {
        do
        {
            if(new_node->key < n1->key)
            {
                if(n1->left == NULL )
                {
                        n1->left = new_node;
                        inserted = 1;
                }
                else
                {
                    n1 = n1->left;
                }
            }
            else if(new_node->key > n1->key)
            {
                if(n1->right == NULL )
                {
                        n1->right = new_node;
                        inserted = 1;
                }
                else
                {
                    n1 = n1->right;
                }
            }
            else
            {
                inserted = 1;
            }
        } while (inserted != 1);
    }

}

struct node *BALANCED_TREE(int start, int end)
{
    if(start > end)
        return NULL;

    int mid = (start + end) / 2;
    struct node *t = keys[mid];

    t->left = BALANCED_TREE(start, mid-1);
    t->right = BALANCED_TREE(mid + 1, end);

    return t;
}

/* -------------------- DISPLAY FUNCTIONS --------------------*/

int GET_HEIGHT(struct node *node)
{
    if (node == NULL)
        return 0;
    else {
        /* compute the height of each subtree */
       int left_h = GET_HEIGHT(node->left);
        int right_h = GET_HEIGHT(node->right);

        /* use the larger one */
       if (left_h > right_h)
            return (left_h + 1);
        else
            return (right_h + 1);
    }
}

//prints level
void DISPLAY(struct node *rt)
{
    int h = GET_HEIGHT(rt);
    int i;
    for (i = 0; i < h; i++)
    {
        printf("Level %d -> ", i);
        PRINT_LVL(rt, i);
        printf("\n");
    }
}

//prints keys on that level
void PRINT_LVL(struct node *root, int level)
{
    if (root == NULL)
        return;
    if (level == 0)
        printf("%d ", root->key);
    else if (level > 0)
    {
        PRINT_LVL(root->left, level - 1);
        PRINT_LVL(root->right, level - 1);
    }
}

/* ------------- SPLITTING FUNCTIONS -------------*/

//gets the index of the splitting point
int GET_SPLIT_INDEX(int index, int k)
{
    int indx = 0;
    for (int i = 0; i < index; i++)
    {
        if (keys[i]->key != k)
        {
            indx++;
        }
        else
        {
            return indx-1;
        }
    }
    return indx-1;

}

//splits the tree at a given point
void SPLIT_POINT(int k)
{
    int split_index = GET_SPLIT_INDEX(ind, k);

    struct node *ROOT1 = NULL;
    struct node *ROOT2 = NULL;

    ROOT1 = BALANCED_TREE(0, split_index);
    ROOT2 = BALANCED_TREE(split_index+1, ind-1);

    printf("\nSplitted BST 1 :: \n--------------------\n");
    if(ROOT1 != NULL)
    {
        DISPLAY(ROOT1);
    }


    printf("\nSplitted BST 2 :: \n--------------------\n");
    if(ROOT2 != NULL)
    {
        DISPLAY(ROOT2);
    }

}

void SPLIT_ROOT(char rt_discard, int choice)
{
    int split_index = GET_SPLIT_INDEX(ind, ROOT->key);

    struct node *ROOT1 = NULL;
    struct node *ROOT2 = NULL;

    //if root is discarded
    if(rt_discard == 'y')
    {
        ROOT1 = BALANCED_TREE(0, split_index);
        ROOT2 = BALANCED_TREE(split_index+2, ind-1);
    }
    else
    {
        //if root's chosen to be kept at leftmost
        if(choice == 1)
        {
            ROOT1 = BALANCED_TREE(0, split_index);
            ROOT2 = BALANCED_TREE(split_index+1, ind-1);
        }
        //if root's chosen to be kept at rightmost
        else
        {
            ROOT1 = BALANCED_TREE(0, split_index+1);
            ROOT2 = BALANCED_TREE(split_index+2, ind-1);
        }
    }

    printf("\nSplitted BST 1 :: \n");
    if(ROOT1 != NULL)
    {
        DISPLAY(ROOT1);
    }

    printf("\nSplitted BST 2 :: \n");
    if(ROOT2 != NULL)
    {
        DISPLAY(ROOT2);
    }

}

//main code
void main()
{
    int no_of_k, key, split_point, choice, rt_loc=0, opt;
    char d_root, ch;

    struct node *nd = (struct node*)malloc(sizeof(struct node));


    printf("\n**************** Practical 5 :: ***********************\n");

    /*This section of code asks key inputs for insertion*/
    printf("\nNumber of keys in Tree ?? :: ");
    scanf("%d",&no_of_k);

    printf("\nEnter keys here under :: \n");
    for(int i=0; i<no_of_k; i++)
    {
        scanf("%d", &key);
        nd = CREATE_NODE(key);
        INSERT(nd);
    }

    printf("\n\nHow do you want to split the Tree?? \n");
    printf("\ni. Split at root (Current root :: %d)\nii. Split at particular node\n",ROOT->key);
    printf("\nWhat's your choice ? :: ");
    scanf("%d", &choice);


    keys = malloc(no_of_k * sizeof(struct node));
    GET_KEYS(ROOT);



    if(choice == 1)
    {
        printf("\nDo you want to KEEP the root? (y/n) :: ");
        scanf(" %c", &d_root);

        if(d_root == 'y')
        {
            printf("\nWhere do you want to insert the root?: \ni. Leftmost\nii. Rightmost\n");
            printf("\nWhat's your choice ? :: ");
            scanf("%d", &rt_loc);

            printf("\nActual BST :: \n");
            DISPLAY(ROOT);

            SPLIT_ROOT(d_root, rt_loc);

        }
        else
        {
            printf("\nActual BST :: \n");
            DISPLAY(ROOT);

            SPLIT_ROOT(d_root, rt_loc);

        }
    }
    else
    {
        printf("\nProvide Key for Splitting :: ");
        scanf(" %d", &split_point);

        printf("\Actual BST :: \n");
        DISPLAY(ROOT);

        SPLIT_POINT(split_point);
    }
}
