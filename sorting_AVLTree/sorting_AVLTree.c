#include <stdio.h>
#include <stdlib.h>

typedef enum{ FALSE,TRUE } bool;

struct Node
{
    int value;
    int balance;
    struct Node *leftChild;
    struct Node *rightChild;
};

struct Node *search(struct Node *ptr, int data)
{
    if (ptr != NULL)
    {
        if (data < ptr->value) return search(ptr->leftChild, data);
        if (data > ptr->value) return search(ptr->rightChild, data);
    }
    return ptr;
}

struct Node *insert(int data, struct Node *ptr, bool *ht_inc)
{
    struct Node *temp1;
    struct Node *temp2;

    if (ptr == NULL)
    {
        ptr = (struct Node *)malloc(sizeof(struct Node));

        ptr->value = data;
        ptr->leftChild = NULL;
        ptr->rightChild = NULL;
        ptr->balance = 0;
        *ht_inc = TRUE;
        return ptr;
    }

    if (data < ptr->value)
    {
        ptr->leftChild = insert(data, ptr->leftChild, ht_inc);

        if (*ht_inc == TRUE)
        {
            if (ptr->balance == 0) ptr->balance = 1;
            else if (ptr->balance == -1)
            {
                ptr->balance = 0;
                *ht_inc = FALSE;
            }
            else if (ptr->balance == 1)
            {
                temp1 = ptr->leftChild;

                if (temp1->balance == 1)
                {
                    ptr->leftChild = temp1->rightChild;
                    temp1->rightChild = ptr;
                    ptr->balance = 0;
                    temp1->balance = 0;
                    ptr = temp1;
                }
                else
                {
                    temp2 = temp1->rightChild;
                    temp1->rightChild = temp2->leftChild;
                    temp2->leftChild = temp1;
                    ptr->leftChild = temp2->rightChild;
                    temp2->rightChild = ptr;

                    if (temp2->balance == 1) ptr->balance = -1;
                    else ptr->balance = 0;

                    if (temp2->balance == -1) temp1->balance = 1;
                    else temp1->balance = 0;

                    temp2->balance = 0;
                    ptr = temp2;
                }
                *ht_inc = FALSE;
            }
        }
    }
    else if (data > ptr->value)
    {
        ptr->rightChild = insert(data, ptr->rightChild, ht_inc);

        if (*ht_inc == TRUE)
        {
            if (ptr->balance == 0) ptr->balance = -1;
            else if (ptr->balance == 1)
            {
                ptr->balance = 0;
                *ht_inc = FALSE;
            }
            else if (ptr->balance == -1)
            {
                temp1 = ptr->rightChild;

                if (temp1->balance == -1)
                {
                    ptr->rightChild = temp1->leftChild;
                    temp1->leftChild = ptr;
                    ptr->balance = 0;
                    temp1->balance = 0;
                    ptr = temp1;
                }
                else
                {
                    temp2 = temp1->leftChild;
                    temp1->leftChild = temp2->rightChild;
                    temp2->rightChild = temp1;
                    ptr->rightChild = temp2->leftChild;
                    temp2->leftChild = ptr;

                    if (temp2->balance == -1) ptr->balance = 1;
                    else ptr->balance = 0;

                    if (temp2->balance == 1) temp1->balance = -1;
                    else temp1->balance = 0;

                    temp2->balance = 0;
                    ptr = temp2;
                }
                *ht_inc = FALSE;
            }
        }
    }
    return ptr;
}

void inorder(struct Node *ptr)
{
    if (ptr != NULL)
    {
        inorder(ptr->leftChild);
        printf("%d\n", ptr->value);
        inorder(ptr->rightChild);
    }
}

int getHeight(struct Node *root)
{
    if (root == NULL) return 0;

    int leftHeight = getHeight(root->leftChild);
    int rightHeight = getHeight(root->rightChild);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void printLevel(struct Node *root, int level, struct Node *parent, char *position)
{
    if (root == NULL) return;

    if (level == 0)
    {
        if (parent == NULL) printf("%d (%d B) ", root->value, root->balance);
        else printf("%d (%d %s) (%d B) ", root->value, parent->value, position, root->balance);
    }
    else
    {
        printLevel(root->leftChild, level - 1, root, "L");
        printLevel(root->rightChild, level - 1, root, "R");
    }
}

void printTree(struct Node *root)
{
    int height = getHeight(root);

    for (int i = 0; i < height; i++)
    {
        printLevel(root, i, NULL, "");
        printf("\n");
    }
}

int main()
{
    bool ht_inc;
    int data;
    struct Node *root = NULL;

    while (1)
    {
        scanf("%d", &data);
        if (data == -1) break;
        root = insert(data, root, &ht_inc);
    }

    inorder(root);
    printf("\n");
    printTree(root);

    return 0;
}
