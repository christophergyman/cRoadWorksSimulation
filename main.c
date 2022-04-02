/* Library Includes: ---------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>
#include <sys/time.h>

#define TRUE 1
#define FALSE 0
#define FULL 10

/* Prototypes:  ---------------------------------------------*/

/*Node object*/
struct node
{
    int data;
    struct node *next;
};
typedef struct node node;

/*  queue object */
struct queue
{
    int count;
    node *front;
    node *rear;
};
typedef struct queue queue;


/* Initialize empty queue */
void initialize(queue *q)
{
    q->count = 0;
    q->front = NULL;
    q->rear = NULL;
}

/* function to check if empty */
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


/* GSL random number generator */
float randomFloatNum() {

    /* Random number function based on the GNU Scientific Library */
    /* Returns a random float between 0 and 1, exclusive; e.g., (0,1) */
    const gsl_rng_type * T;
    gsl_rng * r;
    gsl_rng_env_setup();

    /* Seed generation based on time */
    struct timeval tv; 
    gettimeofday(&tv,0);
    unsigned long mySeed = tv.tv_sec + tv.tv_usec;

    /* Generator setup */
    T = gsl_rng_default; 
    r = gsl_rng_alloc (T);
    gsl_rng_set(r, mySeed);

    /* Generate it! */
    double u = gsl_rng_uniform(r); 
    gsl_rng_free (r);
    return (float)u;
}

/* Returns an integer thats either 0 or 1 */
int randomIntNum();
int randomIntNum(){
    short randomInteger = 0;
    float x = randomFloatNum();
    if (x >= 0.5)
    {
        randomInteger = 0;
    } 
    else 
    {
        randomInteger = 1;
    }

    return randomInteger;
}


/* Function code: ------------------------------------------ */
int main()
{
    /* Make a left queue and assign dynamic memory to it */

    queue leftQueue;
    queue *pLeftQueue = &leftQueue;
    pLeftQueue = malloc(sizeof(queue));
    initialize(pLeftQueue);

    queue rightQueue;
    queue *pRightQueue = &rightQueue;
    pRightQueue = malloc(sizeof(queue));
    initialize(pRightQueue);


    /* Initialize starting traffic light left and right */
    short leftLight;
    short *pLeftLight = &leftLight;

    short rightLight;
    short *pRightLight = &rightLight;

    int startLightFloat;
    int *pStartLightFloat = &startLightFloat;
    *pStartLightFloat = randomIntNum(); 

    if (*pStartLightFloat == 0){
        *pLeftLight = 0;
        *pRightLight = 1;
        printf("right light: green\n");
    }
    else {
        *pLeftLight = 1;
        *pRightLight = 0;
        printf("left light: green\n");
    }

             /* Main simulation loop */ 

    /* zero or one joins left queue */
    int joinLeft;
    int *pJoinLeft = &joinLeft; 
    *pJoinLeft = randomIntNum();




    if (*pJoinLeft == 1){
        enqueue(pLeftQueue, 1);
        printf("car joins left queue \n");
    }

    /* zero or one joins right queue */
    int joinRight;
    int *pJoinRight = &joinRight;
    *pJoinRight = randomIntNum();

    if (*pJoinRight == 1){
        enqueue(pRightQueue, 1);
        printf("car joins right queue \n");
    }

            /* Zero or one pass through lights depending on lights */
    
    /* Returns 1 if queue is not empty */
    int hasLeftQueueHeadValue;
    int *pHasLeftQueueHeadValue = & hasLeftQueueHeadValue;
    *pHasLeftQueueHeadValue = intDisplay(pLeftQueue->front);

    int hasRightQueueHeadValue;
    int *pHasRightQueueHeadValue = & hasRightQueueHeadValue;
    *pHasRightQueueHeadValue = intDisplay(pRightQueue->front);

    /* zero or one pass through lights */
    int passThroughLights;
    int *pPassThroughLights = & passThroughLights;
    *pPassThroughLights = randomIntNum();

    /* check to see if both of the queues are not empty */
    int leftNotEmpty = intDisplay(pLeftQueue->front);
    int rightNotEmpty = intDisplay(pRightQueue->front);

    /* Check to see if the cars should pass through the lights */
    if (*pPassThroughLights == 1){
        printf("Pass through lights requested...  \n");

        /* check lights to see if left car goes through  */
        if (*pLeftLight == 1){
            printf("Please pass through left light... \n");

            /* Left is not empty... */
            if (leftNotEmpty == 1){
                dequeue(pLeftQueue);
                printf("Left car passes through... %d \n", leftNotEmpty);
            }
            
            /* Left queue is empty */
            if (leftNotEmpty == 0){
                printf("Left is empty: %d \n", leftNotEmpty);
            }
        } 

        /* check lights to see if right car goes through  */
        if (*pRightLight == 1){
            printf("Please pass through right light... \n");

            /* Right is not empty... */
            if (rightNotEmpty == 1){
                printf("Right car passes through... %d \n", rightNotEmpty);
                dequeue(pRightQueue);
            }
            
            /* Right queue is empty */
            if (rightNotEmpty == 0){
                printf("Right is empty: %d \n", rightNotEmpty);
            }

        }
    } else {
        printf("Request not to pass through \n");
    }


    /* Freeing the queues from memory */
    free(pLeftQueue);
    free(pRightQueue);

    return 0;
}