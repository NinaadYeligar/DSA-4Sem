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
    if(a > b)
        return a;
    else
        return b;
    //return (a > b) ? a : b;
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

//right rotate a subtree rooted with y
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

//left rotate a subtree rooted with x
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

/*void Display(struct Node* node, int space)
{
    if (node == NULL)
        return;
    space +=10;
    Display(node->right, space);

    printf("\n");
    for(int i=10; i< space; i++)
        printf("  ");
    printf("%d\n",node->element);

    Display(node->left, space);
}
*/

int main()
{
    clock_t start,end;
    double totalT;
    int j;
    printf("Enter Number of elements to be Generated: ");
    scanf("%d",&j);


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


    if (inputFile == NULL)
    {
        printf("No files found\n");
        return 1;
    }

    while (fscanf(inputFile, "%d", &element) != EOF)         // Insertion of elements from the inputF to the AVL tree.
    {
        root = insert(root, element);
    }

    printf("\n  inOrder of the AVL tree: ");
    inOrder(root);
    inOrderFile(root, inFile);

    printf("\n preOrder of the AVL tree: ");
    preOrder(root);
    preOrderFile(root, preFile);

    printf("\npostOrder of the AVL tree: ");
    postOrder(root);
    postOrderFile(root, postFile);
    printf("\n");

    //Display(Node,0);


    fclose(inputFile);
    fclose(inFile);
    fclose(preFile);
    fclose(postFile);


    return 0;
}

