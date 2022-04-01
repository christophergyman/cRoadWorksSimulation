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
        printf("NULL\n");
    }
    else
    {
        printf("%d\n", head -> data);
        display(head->next);
    }
}


/* Function to generate random number: */
void randomDirection()
{
    /* Initialization, should only be called once. */
    srand(time(0));   

    /* Generate random number < 2 */
    int r = rand() % 2;    

    /*Print the isLeft boolean  */
    printf("isLeft: %d \n", r);
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
    queue *leftQueue;
    leftQueue = malloc(sizeof(queue));
    initialize(leftQueue);

    /*Make a right queue assign dynamic memory to it */
    queue *rightQueue;
    rightQueue = malloc(sizeof(queue));
    initialize(rightQueue);

    /* Initialize starting traffic light left and right */
    short leftLight;
    short rightLight;
    int startLightFloat = randomIntNum(); 

    if (startLightFloat == 0){
        leftLight = 0;
        rightLight = 1;
    }
    else {
        leftLight = 1;
        rightLight = 0;
    }

             /* Main simulation loop */ 
    printf("Starting lights:\n L-Light: %d \n R-Light: %d \n", leftLight, rightLight); 

    /* zero or one joins left queue */
    int joinLeft = randomIntNum();
    if (joinLeft == 1){
        enqueue(leftQueue, 1);
    }

    /* zero or one joins right queue */
    int joinRight = randomIntNum();
    if (joinRight == 1){
        enqueue(rightQueue, 1);
    }

            /* Zero or one pass through lights depending on lights */
    
    /* zero or one pass through lights */
    int passThroughLights = randomIntNum();
    if (passThroughLights == 1){
        printf("Pass through lights!");
    } else {
        printf("Dont pass through lights \n");
    }



    return 0;
}