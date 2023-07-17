#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define MAX_SIZE 100

// Text Editor Stack
struct txtstack
{
    char* text[MAX_SIZE];
    int top;
};

// Function to create a new text stack
struct txtstack* createtxtstack()
{
    struct txtstack* stack = (struct txtstack*)malloc(sizeof(struct txtstack)); // Creating a new node (text stack)
    stack->top = -1;
    return stack;
}

// Function to check if the text stack is empty
int istxtstackEmpty(struct txtstack* stack)
{
    return stack->top == -1;
}

// Function to check if the text stack is full
int istxtstackFull(struct txtstack* stack)
{
    return stack->top == MAX_SIZE - 1;
}

// Function to push text onto the stack
void pushText(struct txtstack* stack, char* text)
{
    if (istxtstackFull(stack))
    {
        printf("Text Stack Overflow\n");
        return;
    }
    stack->text[++stack->top] = text;
}

// Function to pop text from the stack
char* popText(struct txtstack* stack)
{
    if (istxtstackEmpty(stack))
    {
        printf("Text Stack Underflow\n");
        return NULL;
    }
    return stack->text[stack->top--];
}

// Text Editor Functions

// Function to edit text
void editText(struct txtstack* undoStack, struct txtstack* redoStack, char* newText)
{
    char* currentText = popText(undoStack); // Pop the current text from the undo stack
    pushText(redoStack, currentText); // Push the current text to the redo stack
    pushText(undoStack, newText); // Push the new text to the undo stack
    printf("Text edited to: %s\n", newText);
}

// Function to undo the last text edit
void undoText(struct txtstack* undoStack, struct txtstack* redoStack)
{
    if (istxtstackEmpty(undoStack))
    {
        printf("No text to undo.\n");
        return;
    }
    char* previousText = popText(undoStack); // Pop the previous text from the undo stack
    pushText(redoStack, previousText); // Push the previous text to the redo stack
    printf("Undo: Text reverted to: %s\n", previousText);
}

// Function to redo the last text edit
void redoText(struct txtstack* undoStack, struct txtstack* redoStack)
{
    if (istxtstackEmpty(redoStack))
    {
        printf("No text to redo.\n");
        return;
    }
    char* nextText = popText(redoStack); // Pop the next text from the redo stack
    pushText(undoStack, nextText); // Push the next text to the undo stack
    printf("Redo: Text changed to: %s\n", nextText);
}

int main()
{
    struct txtstack* textUndoStack = createtxtstack(); // Create an undo stack for texts
    struct txtstack* textRedoStack = createtxtstack(); // Create a redo stack for texts
    time_t s;
    srand((unsigned)time(&s));
    double time;
    clock_t start,end;
    FILE* file = fopen("text.txt", "w"); // Open the file for writing
     start=clock();
    // Simulating text editing
    pushText(textUndoStack, "DSA Evaluation"); // Push "DSA Evaluation" onto the undo stack
    fprintf(file, "%s\n", "DSA Evaluation"); // Write "DSA Evaluation" to the file
    editText(textUndoStack, textRedoStack, "DSA Evaluation is Saturday"); // Edit the text to "DSA Evaluation is Saturday"
    fprintf(file, "%s\n", "DSA Evaluation is Saturday"); // Write "DSA Evaluation is Saturday" to the file
    undoText(textUndoStack, textRedoStack); // Undo the last edit
    redoText(textUndoStack, textRedoStack); // Redo the undone edit
    end=clock();
    time=(double)(end-start)/CLOCKS_PER_SEC;
    printf("time delay=%lf\n",time);
    fclose(file); // Close the file

    return 0;
}
