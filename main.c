#include "queueFunc.c"
#include "numGenerators.c"


void runOneSimulation(float leftArrivalRate, int leftLightPeroid, float rightArrivalRate, int rightLightPeroid){
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
    int leftLight;
    int *pLeftLight = &leftLight;
    int rightLight;
    int *pRightLight = &rightLight;
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
    float passThroughLights;
    float *pPassThroughLights = & passThroughLights;

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

    int iterationCounter = 0;
    int *pIterationCounter = &iterationCounter;

    int lightsChangeCounter = 0;
    int *pLightsChangeCounter = &lightsChangeCounter;

    int leftLightPeroidCounter = leftLightPeroid;
    int rightLightPeroidCounter = rightLightPeroid;


    /* Initially set the lights randomly  */
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

    /* ----------------Main simulation loop -------------------------*/ 
    while(1){

        /* On each iteration either the lights change or cars arrive/leave */
        int lightsChangeOrMainLoop = randomIntNum();

        /* Possibility that lights could change */
        if (lightsChangeOrMainLoop == 0){
            *pIterationCounter = *pIterationCounter + 1;

            /* If the light peroid is zero, change the lights*/
            if (leftLightPeroidCounter == 0){

                /* change left light */
                if (*pLeftLight == 0){
                    *pLeftLight= 1;
                }
                if (*pLeftLight == 1){
                    *pLeftLight= 0;
                }

                /* reset counter */
                leftLightPeroidCounter = leftLightPeroid;
            }

            if (rightLightPeroidCounter== 0){
                /* change right light */
                if (*pRightLight == 0){
                    *pRightLight= 1;
                }
                if (*pRightLight == 1){
                    *pRightLight= 0;
                }

                /* reset counter */
                rightLightPeroidCounter = rightLightPeroid;
            }

            /* If the light peroids are not zero keep going*/
            if (leftLightPeroidCounter != 0){
                leftLightPeroidCounter = leftLightPeroidCounter - 1;
            }

            if (rightLightPeroid != 0){
                rightLightPeroid = rightLightPeroid - 1;
            }


            

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
        }

        /* Possibility that main loop happens */
        if (lightsChangeOrMainLoop == 1){
            /* Only add cars if less then 500 iterations */
            if (*pIterationCounter <= 500){

                /* zero or one car left queue */
                *pJoinLeft = randomFloatNum();
                if (*pJoinLeft > leftArrivalRate){
                    enqueue(pLeftQueue, 1);
                    *pLeftCarAdded = *pLeftCarAdded + 1;
                    *pCarAddedCounter = *pCarAddedCounter + 1;
                }

                /* zero or one car right queue */
                *pJoinRight = randomIntNum();
                if (*pJoinRight > rightArrivalRate){
                    enqueue(pRightQueue, 1);
                    *pRightCarAdded = *pRightCarAdded + 1;
                    *pCarAddedCounter = *pCarAddedCounter + 1;
                }
            }


            /* checks if left and right queue are not null */
            *pHasLeftQueueHeadValue = intDisplay(pLeftQueue->front);
            *pHasRightQueueHeadValue = intDisplay(pRightQueue->front);
            int leftNotEmpty = intDisplay(pLeftQueue->front);
            int rightNotEmpty = intDisplay(pRightQueue->front);


            /* Check to see if the cars should pass through the lights */
            *pPassThroughLights = randomIntNum();
            if (*pPassThroughLights == 0 ){
                *pRequestCarPass = *pRequestCarPass + 1;

                /* check lights to see if left car queue can through  */
                if (*pLeftLight == 1){
                    /* Left is not empty dequeue a car */
                    if (leftNotEmpty == 1){
                        dequeue(pLeftQueue);
                        *pLeftCarpassed = *pLeftCarpassed + 1;
                    }

                    if (leftNotEmpty == 0){
                        printf("...Left queue is now empty... \n");
                    }
                    
                    /* Check if left and right queues are empty, if so break */
                    if ( (leftNotEmpty == 0) && (rightNotEmpty == 0) ){
                        /* printf("left queue: %d,    right queue: %d \n", leftNotEmpty, rightNotEmpty); */
                        printf("Left and right is empty \n");
                        break;
                    }
                } 
                /* check lights to see if right car queue can through  */
                if (*pRightLight == 1){

                    /* Right is not empty dequeue a car */
                    if (rightNotEmpty == 1){
                        *pRightCarpassed = *pRightCarpassed + 1;
                        dequeue(pRightQueue);
                    }
                    
                    if (rightNotEmpty == 0){
                        printf("...Right queue is now empty... \n");
                    }
                    /* Check if left and right queues are empty, if so break */
                    if ( (leftNotEmpty == 0) && (rightNotEmpty == 0) ){
                        /* printf("left queue: %d,    right queue: %d \n", leftNotEmpty, rightNotEmpty); */
                        printf("Right and left queue is empty \n");
                        break;
                    }

                }
            }
        } 
        else 
        {
            /* printf("Request not to pass through \n"); */
        }

        /* calculate total cars passed that iteration */
        *pTotalCarsPassed = *pLeftCarpassed + *pRightCarpassed;

        /* Print out the progress of that timestep(iteration) */
        printf("\n===================================\n");
        printf("Left light is: %d     Right light is: %d  \n", *pLeftLight, *pRightLight);
        printf("Current Iteration: %d \n", *pIterationCounter);
        /* printf("Lights Changed: %d \n", *pLightChanged); */
        printf("L-Car Added: %d,   R-Car Added: %d  \n",*pLeftCarAdded, *pRightCarAdded);
        printf("L-Car Passed %d,   R-Car Passed %d  \n", *pLeftCarpassed, *pRightCarpassed);
        printf("Car allowed to go through: %d \n ", *pRequestCarPass);

    }

    /* Freeing the queues from memory */
    free(pLeftQueue);
    free(pRightQueue);

}


/* Function code: ------------------------------------------ */
int main()
{
    /* Inputs for run One Simulation
        1) Traffic arrival rate left on left side
        2) Traffic arrival rate right on left side
        3) Traffice arrival rate on right side
        4) Traffce light peroid 
    */

    /* Hardcoded input */
    float leftTrafficArriveRate = 0.5;
    float leftLightPeroid = 0.5;
    float rightTrafficeArriveRate = 0.5;
    float rightLightPeroid = 0.5;

    /* Run one simulation */
    runOneSimulation(leftLightPeroid, leftLightPeroid, rightTrafficeArriveRate, rightLightPeroid);

    return 0;
}