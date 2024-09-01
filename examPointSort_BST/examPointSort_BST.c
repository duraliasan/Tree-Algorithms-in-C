#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int studentID;
    int grade;
    struct Node *left;
    struct Node *right;
};

struct Node *create(int studentID, int grade)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->studentID = studentID;
    newNode->grade = grade;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node *insert(struct Node *root, int studentID, int grade)
{
    if (root == NULL) return create(studentID, grade);
    if (grade < root->grade) root->left = insert(root->left, studentID, grade);
    else root->right = insert(root->right, studentID, grade);
    return root;
}

void inOrder(struct Node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%d %d\n", root->studentID, root->grade);
        inOrder(root->right);
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

void printLevel(struct Node *root, int level, struct Node *parent, char *position)
{
    if (root == NULL) return;

    if (level == 0)
    {
        if (parent == NULL) printf("%d %d", root->studentID, root->grade);
        else printf("%d %d (%d %s) ", root->studentID, root->grade, parent->grade, position);
    }
    else
    {
        printLevel(root->left, level - 1, root, "L");
        printLevel(root->right, level - 1, root, "R");
    }
}

int getHeight(struct Node *root)
{
    if (root == NULL) return 0;

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int main()
{
    struct Node *root = NULL;
    int id, grade;

    while (1)
    {
        scanf("%d", &id);
        if (id == -1) break;
        scanf("%d", &grade);
        root = insert(root, id, grade);
    }

    inOrder(root);
    printf("\n");

    printTree(root);

    return 0;
}