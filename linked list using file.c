#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* next;                                     // Define a linked list node
};

void swap(struct node* a, struct node* b)
{
    int temp = a->data;                                   // Swap the values of two nodes
    a->data = b->data;
    b->data = temp;
}

void bubbleSort(struct node** head_ref)
{
    int swapped;                                          // Bubble sort the linked list
    struct node* ptr1;
    struct node* lptr = NULL;

    if (*head_ref == NULL)                                // Check for empty list
        return;

    do {
        swapped = 0;
        ptr1 = *head_ref;

        while (ptr1->next != lptr)
        {
            if (ptr1->data > ptr1->next->data)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void push(struct node** head_ref, int new_data)
{
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = new_data;
    new_node->next = (*head_ref);                                       // Insert a node at the beginning of the linked list
    (*head_ref) = new_node;
}

void printList(struct node* node)
{
    while (node != NULL)                                               // Print the linked list
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void writeFile(struct node* node, char* file1)
{
    FILE* fp = fopen("file1.txt", "w");                                  // Write the linked list to a file

    while (node != NULL)
    {
        fprintf(fp, "%d ", node->data);
        node = node->next;
    }
    fclose(fp);
}

void readFile(struct node** head_ref, char* file1)
{
    FILE* fp = fopen("file1.txt", "r");                                 // Read the linked list from a file
    int data;
    while (fscanf(fp, "%d", &data) != EOF)
    {
        push(head_ref, data);
    }
    fclose(fp);
}

int main()
{
    struct node* head = NULL;

    push(&head, 40);                                                  // Insert some data into the linked list
    push(&head, 2);
    push(&head, 100);
    push(&head, 6);
    push(&head, 9);

    printf("Original List: ");                                       // Print the original list
    printList(head);

    bubbleSort(&head);                                                       // Sort the list

    printf("Sorted List: ");                                         // Print the sorted list
    printList(head);

    writeFile(head, "sorted_list.txt");                            // Write the sorted list to a file

    while (head != NULL)                                                   // Clear the list and read the sorted data from the file
    {
        struct node* temp = head;
        head = head->next;
        free(temp);
    }
    head = NULL;
    readFile(&head, "sorted_list.txt");

    printf("Sorted List from file: ");                                        // Print the sorted list from the file
    printList(head);

    while (head != NULL)                                                   // Clear the list
    {
        struct node* temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}
