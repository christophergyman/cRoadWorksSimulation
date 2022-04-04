#include "main.h"

/* Initialize empty queue */
void initialize(queue *q)
{
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;
}

/* function to check if queue is empty */
int isempty(queue *q)
{
    return (q->rear == NULL);
}

/* Insert node */
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

/* Pop node off top of the queue */
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

/* Print the head of the queue */
void display(node *head)
{
    if(head == NULL)
    {
        /* printf("NULL\n"); */
    }
    else
    {
        /* printf("%d\n", head -> data); */
        display(head->next);
    }
}

/* return time it took car to leave queue */
int returnCarTime(node *head)
{
    if(head == NULL)
    {
        /* printf("NULL\n"); */
    }
    else
    {
        /* printf("%d\n", head -> data); */
        return(head->data);

    }
}

/* return if head is null */
int intDisplay(node *head)
{
    if(head == NULL)
    {
        /* printf("NULL\n"); */
        return 0;
    }
    else
    {
        display(head->next);
        return 1;
    }
}