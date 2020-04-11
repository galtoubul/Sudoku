#include "Solve.h"

/**
 * Stack Summary:
 *
 * Contains the struct for stack of Games and its related functions
 *
 * createStack  - creates a new stack and initializes its fields
 * isFull       - return 1 if the stack full. Otherwise, returns 0.
 * isEmpty      - return 1 if the stack empty. Otherwise, returns 0.
 * push         - inserts a Game into the top of the stack.
 * pop          - returns the Game from the top of the stack and removes it from the stack.
 * top          - returns the Game from the top of the stack without removing it from the stack.
 * remove       - removes the Game from the top of the stack
 *
 */

typedef struct Stack{
    int capacity;
    int*** arr;
    int top;
    int gameRows;
    int gameColumns;
    int gameBoxRow;
    int gameBoxCol;
}Stack;

Stack* createStack (int capacity, Game* game);

int isFull (Stack* stack);

int isEmpty (Stack* stack);

void push (Stack* stack, int** board);

int** pop(Stack* stack);

int** top (Stack* stack);

void removeFromStack(Stack* stack);

void destroyStack(Stack* stack);
