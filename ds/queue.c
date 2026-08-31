#include <stdbool.h>

struct Node {
    int val;
    int numChildren;
    struct Node **children;
};

#define MAX_QUEUE_SIZE 1000

struct Queue {
    struct Node *items[MAX_QUEUE_SIZE];
    int front;
    int rear;
};

// Initialize an empty queue
void initQueue(struct Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if the queue is empty
bool isEmpty(struct Queue *q) { return q->front == -1; }

int queueLength(struct Queue *q) {
    if (isEmpty(q)) {
        return 0;
    }
    return q->rear - q->front + 1;
}

// Add a node pointer to the queue
void enqueue(struct Queue *q, struct Node *node) {
    if (q->rear == MAX_QUEUE_SIZE - 1)
        return;
    if (q->front == -1)
        q->front = 0;
    q->rear++;
    q->items[q->rear] = node;
}

// Remove and return a node pointer from the queue
struct Node *dequeue(struct Queue *q) {
    if (isEmpty(q))
        return NULL;
    struct Node *item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1; // Reset queue when empty
    }
    return item;
}
