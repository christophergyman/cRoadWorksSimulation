#include "queueFunc.c"
#include "numGenerators.c"



/* Function code: ------------------------------------------ */
int main()
{
    /* Make a queues and assign dynamic memory to it */
    queue leftQueue;
    queue *pLeftQueue = &leftQueue;
    pLeftQueue = malloc(sizeof(queue));
    queue rightQueue;
    queue *pRightQueue = &rightQueue;
    pRightQueue = malloc(sizeof(queue));
    /* initialising the queues with default values */
    initialize(pLeftQueue);
    initialize(pRightQueue);

    /* Initialize starting traffic light left and right variables */
    short leftLight;
    short *pLeftLight = &leftLight;
    short rightLight;
    short *pRightLight = &rightLight;
    int startLightFloat;
    int *pStartLightFloat = &startLightFloat;

    /* Initialise variables checking cars should join left or right queue */
    int joinLeft;
    int *pJoinLeft = &joinLeft; 
    int joinRight;
    int *pJoinRight = &joinRight;

    
    /* Intialise variables, these are used to check if head of queue is null */
    int hasLeftQueueHeadValue;
    int *pHasLeftQueueHeadValue = & hasLeftQueueHeadValue;
    int hasRightQueueHeadValue;
    int *pHasRightQueueHeadValue = & hasRightQueueHeadValue;
    int passThroughLights;
    int *pPassThroughLights = & passThroughLights;

    /* Variables that track the progress of the traffic */
    int lightChanged = 0;
    int *pLightChanged = &lightChanged;

    int leftCarAdded = 0;
    int *pLeftCarAdded= &leftCarAdded;

    int rightCarAdded = 0;
    int *pRightCarAdded= &rightCarAdded;

    int carAddedCounter = 0;
    int *pCarAddedCounter= &carAddedCounter;

    int requestCarPass = 0;
    int *pRequestCarPass = &requestCarPass;

    int leftCarPassed = 0;
    int *pLeftCarpassed = &leftCarPassed;

    int rightCarPassed = 0;
    int *pRightCarpassed = &rightCarPassed;

    int totalCarsPassed = 0;
    int *pTotalCarsPassed = &totalCarsPassed;

    /* ----------------Main simulation loop -------------------------*/ 


    /* Current iteration light change */
    *pStartLightFloat = randomIntNum(); 
    if (*pStartLightFloat == 0){
        *pLeftLight = 0;
        *pRightLight = 1;
        *pLightChanged = *pLightChanged + 1;
    }
    else {
        *pLeftLight = 1;
        *pRightLight = 0;
        *pLightChanged = *pLightChanged + 1;
    }


    /* zero or one car left queue */
    *pJoinLeft = randomIntNum();
    if (*pJoinLeft == 1){
        enqueue(pLeftQueue, 1);
        *pLeftCarAdded = *pLeftCarAdded + 1;
        *pCarAddedCounter = *pCarAddedCounter + 1;
    }

    /* zero or one car right queue */
    *pJoinRight = randomIntNum();
    if (*pJoinRight == 1){
        enqueue(pRightQueue, 1);
        *pRightCarAdded = *pRightCarAdded + 1;
        *pCarAddedCounter = *pCarAddedCounter + 1;
    }


    /* checks if left and right queue are not null */
    *pHasLeftQueueHeadValue = intDisplay(pLeftQueue->front);
    *pHasRightQueueHeadValue = intDisplay(pRightQueue->front);

    /* variables that will be used later to check if queue is not empty */
    int leftNotEmpty = intDisplay(pLeftQueue->front);
    int rightNotEmpty = intDisplay(pRightQueue->front);

    /* Check to see if the cars should pass through the lights */
    *pPassThroughLights = randomIntNum();
    if (*pPassThroughLights == 1){
        *pRequestCarPass = *pRequestCarPass + 1;

        /* check lights to see if left car queue can through  */
        if (*pLeftLight == 1){
            /* Left is not empty... */
            if (leftNotEmpty == 1){
                dequeue(pLeftQueue);
                *pLeftCarpassed = *pLeftCarpassed + 1;
            }
            
            /* Left queue is empty */
            if (leftNotEmpty == 0){
            }
        } 

        /* check lights to see if right car queue can through  */
        if (*pRightLight == 1){

            /* Right is not empty... */
            if (rightNotEmpty == 1){
                *pRightCarpassed = *pRightCarpassed + 1;
                dequeue(pRightQueue);
            }
            
            /* Right queue is empty */
            if (rightNotEmpty == 0){
            }

        }
    } else {
        /* printf("Request not to pass through \n"); */
    }

    /* calculate total cars passed that iteration */
    *pTotalCarsPassed = *pLeftCarpassed + *pRightCarpassed;

    /* Print out the progress of that timestep(iteration) */
    printf("\n Lights Changed: %d \n", *pLightChanged);
    printf("L-Car Added: %d,   R-Car Added: %d  \n",*pLeftCarAdded, *pRightCarAdded);
    printf("CarsAddedCounter: %d \n", *pCarAddedCounter);
    printf("Request that car pass: %d \n \n", *pRequestCarPass);

    /* Break loop if the total cars added 
        to the queue is less than cars requested to pass */

    if (*pCarAddedCounter < *pRequestCarPass){

    }

    /* Freeing the queues from memory */
    free(pLeftQueue);
    free(pRightQueue);

    return 0;
}