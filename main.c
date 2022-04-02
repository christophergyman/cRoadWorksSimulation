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




    /* ----------------Main simulation loop -------------------------*/ 

    /* Current iteration light change */
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


    /* zero or one car left queue */
    *pJoinLeft = randomIntNum();
    if (*pJoinLeft == 1){
        enqueue(pLeftQueue, 1);
        printf("car joins left queue \n");
    }


    /* zero or one car right queue */
    *pJoinRight = randomIntNum();
    if (*pJoinRight == 1){
        enqueue(pRightQueue, 1);
        printf("car joins right queue \n");
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
                printf("Left queue is empty...: %d \n", leftNotEmpty);
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
                printf("Right queue is empty...: %d \n", rightNotEmpty);
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