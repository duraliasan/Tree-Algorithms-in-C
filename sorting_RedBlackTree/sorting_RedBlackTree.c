#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

struct Node
{
    int data;
    int colour;
    struct Node *left, *right, *parent;
};

struct Node *root = NULL;

struct Node *create(int data);
void inorder(struct Node *root);
struct Node *insert(struct Node *root, struct Node *newNode);
void printTree(struct Node *root);
void printLevel(struct Node *root, int level, struct Node *parent, char *position);
int getHeight(struct Node *root);
void rotateLeft(struct Node *node);
void rotateRight(struct Node *node);
struct Node *grandParent(struct Node *node);
struct Node *uncle(struct Node *node);
void case1(struct Node *node);
void case2(struct Node *node);
void case3(struct Node *node);
void case4(struct Node *node);
void case5(struct Node *node);

struct Node *create(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->colour = RED;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

struct Node *insert(struct Node *root, struct Node *newNode)
{
    if (root == NULL) return newNode;

    if (newNode->data < root->data)
    {
        root->left = insert(root->left, newNode);
        root->left->parent = root;
    }
    else if (newNode->data > root->data)
    {
        root->right = insert(root->right, newNode);
        root->right->parent = root;
    }
    return root;
}

void rotateLeft(struct Node *node)
{
    struct Node *r = node->right;
    node->right = r->left;

    if (r->left != NULL) r->left->parent = node;

    r->parent = node->parent;

    if (node->parent == NULL) root = r;
    else if (node == node->parent->left) node->parent->left = r;
    else node->parent->right = r;

    r->left = node;
    node->parent = r;
}

void rotateRight(struct Node *node)
{
    struct Node *l = node->left;
    node->left = l->right;

    if (l->right != NULL) l->right->parent = node;

    l->parent = node->parent;

    if (node->parent == NULL) root = l;
    else if (node == node->parent->left) node->parent->left = l;
    else node->parent->right = l;

    l->right = node;
    node->parent = l;
}

struct Node *grandParent(struct Node *node)
{
    if ((node != NULL) && (node->parent != NULL)) return node->parent->parent;
    else return NULL;
}

struct Node *uncle(struct Node *node)
{
    struct Node *g = grandParent(node);

    if (g == NULL) return NULL;

    if (node->parent == g->left) return g->right;
    else return g->left;
}

void case1(struct Node *node)
{
    if (node->parent == NULL) node->colour = BLACK;
    else case2(node);
}

void case2(struct Node *node)
{
    if (node->parent->colour == BLACK) return;
    else case3(node);
}

void case3(struct Node *node)
{
    struct Node *u = uncle(node);
    struct Node *g = grandParent(node);

    if ((u != NULL) && (u->colour == RED))
    {
        node->parent->colour = BLACK;
        u->colour = BLACK;
        g->colour = RED;
        case1(g);
    }
    else case4(node);
}

void case4(struct Node *node)
{
    struct Node *g = grandParent(node);

    if ((node == node->parent->right) && (node->parent == g->left))
    {
        rotateLeft(node->parent);
        node = node->left;
    }
    else if ((node == node->parent->left) && (node->parent == g->right))
    {
        rotateRight(node->parent);
        node = node->right;
    }
    case5(node);
}

void case5(struct Node *node)
{
    struct Node *g = grandParent(node);

    if ((node == node->parent->left) && (node->parent == g->left)) rotateRight(g);
    else if ((node == node->parent->right) && (node->parent == g->right)) rotateLeft(g);

    node->parent->colour = BLACK;
    g->colour = RED;
}

void inorder(struct Node *root)
{
    if (root == NULL) return;

    inorder(root->left);
    printf("%d\n", root->data);
    inorder(root->right);
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
        if (parent == NULL) printf("%d %c", root->data, root->colour == RED ? 'R' : 'B');
        else printf("%d %c (%d %s) ", root->data, root->colour == RED ? 'R' : 'B', parent->data, position);
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
    int value;

    while (1)
    {
        scanf("%d", &value);
        if (value == -1) break;
        struct Node *newNode = create(value);
        root = insert(root, newNode);
        case1(newNode);
    }

    inorder(root);
    printf("\n");
    printTree(root);

    return 0;
}