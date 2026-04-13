#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

// Stack
typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *S);
bool isStackEmpty(Stack *S);
void push(Stack *S, int x);
int pop(Stack *S);
int getTop(Stack *S);

// Queue
typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
} Queue;

void initQueue(Queue *Q);
bool isQueueEmpty(Queue *Q);
void enqueue(Queue *Q, int x);
int dequeue(Queue *Q);

int main() {
    Stack S1, S2;
    Queue merged;
    initStack(&S1);
    initStack(&S2);
    initQueue(&merged);
    
    int val;
    char ch;
    while (scanf("%d", &val) == 1) {
        push(&S1, val);
        ch = getchar();
        if (ch == '\n' || ch == EOF) break;
    }
    while (scanf("%d", &val) == 1) {
        push(&S2, val);
        ch = getchar();
        if (ch == '\n' || ch == EOF) break;
    }
    
    while (!isStackEmpty(&S1) && !isStackEmpty(&S2)) {
        if (getTop(&S1) < getTop(&S2)) {
            enqueue(&merged, pop(&S1));
        } else {
            enqueue(&merged, pop(&S2));
        }
    }
    while (!isStackEmpty(&S1)) {
        enqueue(&merged, pop(&S1));
    }
    while (!isStackEmpty(&S2)) {
        enqueue(&merged, pop(&S2));
    }
    
    while (!isQueueEmpty(&merged)) {
        printf("%d ", dequeue(&merged));
    }

    printf("\n");
    return 0;
}

// Stack
void initStack(Stack *S) {
    S->top = -1;  // empty stack
}

bool isStackEmpty(Stack *S) {
    return S->top == -1; 
}

void push(Stack *S, int x) {
    if (S->top < MAX_SIZE - 1) {
        S->data[++(S->top)] = x;
    } else {
        printf("Stack overflow\n");
        exit(1);
    }
}

int pop(Stack *S) {
    if(isStackEmpty(S)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return S->data[(S->top)--];
}

int getTop(Stack *S) {
    if(isStackEmpty(S)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return S->data[(S->top)];
}

// Queue
void initQueue(Queue *Q) {
    Q->front = 0;
    Q->rear = 0;
}

bool isQueueEmpty(Queue *Q) {
    return Q->front == Q->rear;
}

void enqueue(Queue *Q, int x) {
    if((Q->rear + 1) % MAX_SIZE == Q->front) {
        printf("Queue overflow\n");
        exit(1);
    }
    Q->data[Q->rear] = x;
    Q->rear = (Q->rear + 1) % MAX_SIZE;
}

int dequeue(Queue *Q) {
    if(isQueueEmpty(Q)) {
        printf("Queue underflow\n");
        exit(1);
    }
    int x = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAX_SIZE;
    return x;
}
