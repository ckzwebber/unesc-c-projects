#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *newNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

struct Node *insert(struct Node *node, int data)
{

    if (node == NULL)
    {
        return newNode(data);
    }

    if (data < node->data)
    {
        node->left = insert(node->left, data);
    }

    else
    {
        node->right = insert(node->right, data);
    }

    return node;
}

void preOrder(struct Node *node)
{
    if (node != NULL)
    {
        printf("%d ", node->data);
        preOrder(node->left);
        preOrder(node->right);
    }
}

void freeTree(struct Node *node)
{
    if (node == NULL)
        return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main(void)
{

    struct Node *root = NULL;
    root = insert(root, 4);
    root = insert(root, 1);
    root = insert(root, 3);
    root = insert(root, 8);
    root = insert(root, 6);
    root = insert(root, 2);

    printf("Percurso em pré-ordem: ");
    preOrder(root);
    printf("\n");

    freeTree(root);
    return 0;
}