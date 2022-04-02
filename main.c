#include "queueFunc.c"
#include "numGenerators.c"



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