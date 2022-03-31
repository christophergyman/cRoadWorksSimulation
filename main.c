/* Library Includes: ---------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define FULL 10

/* Prototypes:  ---------------------------------------------*/

// Node object
struct node
{
    int data;
    struct node *next;
};
typedef struct node node;

//  queue object
struct queue
{
    int count;
    node *front;
    node *rear;
};
typedef struct queue queue;


// Initialize empty queue
void initialize(queue *q)
{
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;
}

// function to check if empty
int isempty(queue *q)
{
    return (q->rear == NULL);
}

// Insert node
void enqueue(queue *q, int value)
{
    if (q->count < FULL)
    {
        node *tmp;
        tmp = malloc(sizeof(node));
        tmp->data = value;
        tmp->next = NULL;
        if(!isempty(q))
        {
            q->rear->next = tmp;
            q->rear = tmp;
        }
        else
        {
            q->front = q->rear = tmp;
        }
        q->count++;
    }
    else
    {
        printf("List is full\n");
    }
}

// Pop node off top of the queue
int dequeue(queue *q)
{
    node *tmp;
    int n = q->front->data;
    tmp = q->front;
    q->front = q->front->next;
    q->count--;
    free(tmp);
    return(n);
}

// Print the head of the queue
void display(node *head)
{
    if(head == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        printf("%d\n", head -> data);
        display(head->next);
    }
}

// Function to generate random number:
void randomNum()
{
    // Initialization, should only be called once.
    srand(time(NULL));   

    // Generate random number < 2
    int r = rand() % 2;    

    //Print random number
    printf("randNum: %d", r);
}

/* Function code: ------------------------------------------ */
int main()
{
    // // Print top of both queues
    // display(leftQueue->front);
    // display(rightQueue->front);

    // //stack element
    // enqueue(rightQueue, 1);

    // //Dequeue 
    // dequeue(leftQueue);

    // Make a left queue and assign dynamic memory to it
    queue *leftQueue;
    leftQueue = malloc(sizeof(queue));
    initialize(leftQueue);

    //Make a right queue
    queue *rightQueue;
    rightQueue = malloc(sizeof(queue));
    initialize(rightQueue);
    
    //Generate Random number:
    randomNum();


    return 0;
}