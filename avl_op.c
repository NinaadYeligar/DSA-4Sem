#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node
{
    int element;
    struct Node* left;
    struct Node* right;
    int height;
};

int height(struct Node* node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

struct Node* newNode(int element)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->element = element;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Right rotate a subtree rooted with y
struct Node* rightRotate(struct Node* y)
{
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotate a subtree rooted with x
struct Node* leftRotate(struct Node* x)
{
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(struct Node* node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

struct Node* insert(struct Node* node, int element)
{
    if (node == NULL)
        return newNode(element);

    if (element < node->element)
        node->left = insert(node->left, element);
    else if (element > node->element)
        node->right = insert(node->right, element);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && element < node->left->element)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && element > node->right->element)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && element > node->left->element)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && element < node->right->element)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inOrder(struct Node* node)
{
    if (node != NULL)
    {
        inOrder(node->left);
        printf("%d ", node->element);
        inOrder(node->right);
    }
}

void inOrderFile(struct Node* node, FILE* inFile)
{
    if (node != NULL)
    {
        inOrderFile(node->left, inFile);
        fprintf(inFile, "%d ", node->element);
        inOrderFile(node->right, inFile);
    }
}

void preOrder(struct Node* node)
{
    if (node != NULL)
    {
        printf("%d ", node->element);
        preOrder(node->left);
        preOrder(node->right);
    }
}

void preOrderFile(struct Node* node, FILE* preFile)
{
    if (node != NULL)
    {
        fprintf(preFile, "%d ", node->element);
        preOrderFile(node->left, preFile);
        preOrderFile(node->right, preFile);
    }
}

void postOrder(struct Node* node)
{
    if (node != NULL)
    {
        postOrder(node->left);
        postOrder(node->right);
        printf("%d ", node->element);
    }
}

void postOrderFile(struct Node* node, FILE* postFile)
{
    if (node != NULL)
    {
        postOrderFile(node->left, postFile);
        postOrderFile(node->right, postFile);
        fprintf(postFile, "%d ", node->element);
    }
}

void Display(struct Node* node, int space, FILE* displayFile)
{
    if (node == NULL)
        return;

    space += 10;

    Display(node->right, space, displayFile);

    fprintf(displayFile, "\n");
    for (int i = 10; i < space; i++)
        fprintf(displayFile, " ");

    fprintf(displayFile, "%d\n", node->element);

    Display(node->left, space, displayFile);
}

int NodesAtLevel(struct Node* node, int level)
{
        if(node==NULL)
                return 0;
        if(level==0)
                return 1;

        return (NodesAtLevel(node->left,level-1) + NodesAtLevel(node->right,level-1));
}
int main()
{
    clock_t start, end;
    double totalT;
    int j,level;
    printf("Enter the number of elements to be generated: ");
    scanf("%d", &j);

    struct Node* root = NULL;
    int element;

    FILE* inputFile = fopen("randomN.txt", "w");
    if (inputFile == NULL)
    {
        printf("Error opening file.");
        return 1;
    }
    srand(time(NULL));

    for (int i = 0; i < j; i++)
    {
        int randomNumber = rand() % 100;
        fprintf(inputFile, "%d ", randomNumber);
    }
    fclose(inputFile);

    // Reading generated random numbers from the file.
    FILE* inputFileRead = fopen("randomN.txt", "r");
    if (inputFileRead == NULL)
    {
        printf("Error opening file.");
        return 1;
    }

    FILE* inFile = fopen("inOrderF.txt", "w");
    FILE* preFile = fopen("preOrderF.txt", "w");
    FILE* postFile = fopen("postOrderF.txt", "w");
    FILE* displayFile = fopen("treeStructure.txt", "w");

    if (inputFile == NULL || inFile == NULL || preFile == NULL || postFile == NULL || displayFile == NULL)
    {
        printf("Error opening files.\n");
        return 1;
    }

    while (fscanf(inputFileRead, "%d", &element) != EOF)
    {
        root = insert(root, element);
    }

    printf("\nInOrder of the AVL tree: ");
    inOrder(root);
    inOrderFile(root, inFile);

    printf("\nPreOrder of the AVL tree: ");
    preOrder(root);
    preOrderFile(root, preFile);

    printf("\nPostOrder of the AVL tree: ");
    postOrder(root);
    postOrderFile(root, postFile);

    printf("\n");

    printf("\nAVL Tree Structure:\n");
    Display(root, 0, stdout);                              // Display tree structure on console


    Display(root, 0, displayFile);                         // Write tree structure to file


    while(1)
    {
         printf("Enter Level Number : ");
         scanf("%d",&level);
         printf("\nNumber of nodes at %d Level : %d node(s)\n",level,NodesAtLevel(root,level));
    }

    fclose(inputFileRead);
    fclose(inFile);
    fclose(preFile);
    fclose(postFile);
    fclose(displayFile);

    return 0;
}
