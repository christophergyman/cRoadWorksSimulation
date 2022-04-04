#include "queueFunc.c"
#include "numGenerators.c"


void runOneSimulation(int simulateMore, float leftArrivalRate, int leftLightPeroid, float rightArrivalRate, int rightLightPeroid){


    /* default values which will be put into an array */
    float multipleleftNumberOfVehicles = 0;
    float multipleleftAverageWaitingTime = 0;
    float multipleleftMaxWaitingTime = 0;
    float multipleleftClearanceTime = 0;

    float multiplerightNumberOfVehicles = 0;
    float multiplerightAverageWaitingTime = 0;
    float multiplerightMaxWaitingTime = 0;
    float multiplerightClearanceTime = 0;

    /* assigning defualt values after they have been changed to the array */
    float multipleSimulationsData[] = {
        multipleleftNumberOfVehicles,
        multipleleftAverageWaitingTime,
        multipleleftMaxWaitingTime,
        multipleleftClearanceTime,
        multiplerightNumberOfVehicles,
        multiplerightAverageWaitingTime,
        multiplerightMaxWaitingTime,
        multiplerightClearanceTime
    };

    int simulateMoreCounter = 0;


    /* if you just want one simulation being run */
    if(simulateMore == 0){
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

        /* Defulat Variables that are manually set to start the loop */
        int lightChanged = 0;
        int leftCarAdded = 0;
        int rightCarAdded = 0;
        int carAddedCounter = 0;
        int requestCarPass = 0;
        int leftCarPassed = 0;
        int rightCarPassed = 0;
        int totalCarsPassed = 0;
        int iterationCounter = 0;
        int lightsChangeCounter = 0;
        int leftClearanceTime = 0;
        int rightClearanceTime = 0;

        /* Assigned all of those manually set defualt variables to pointers 
        purpose is so that in the future if these values are needed to be passed to 
        other functions they can be, future proofing the program  */
        int *pLightChanged = &lightChanged;
        int *pLeftCarAdded= &leftCarAdded;
        int *pRightCarAdded= &rightCarAdded;
        int *pCarAddedCounter= &carAddedCounter;
        int *pRequestCarPass = &requestCarPass;
        int *pLeftCarpassed = &leftCarPassed;
        int *pRightCarpassed = &rightCarPassed;
        int *pTotalCarsPassed = &totalCarsPassed;
        int *pIterationCounter = &iterationCounter;
        int *pLightsChangeCounter = &lightsChangeCounter;

        int *pLeftClearanceTime = &leftClearanceTime;
        int *pRightClearanceTime = &rightClearanceTime;


        /* Assigning user input to local variable */
        int leftLightPeroidCounter = leftLightPeroid;
        int rightLightPeroidCounter = rightLightPeroid;

        /* current simulation variables being set */
        float leftAverageWaitingTime = 0;
        float leftMaxWaitingTime = 0;
        float rightAverageWaitingTime = 0;
        float rightMaxWaitingTime = 0;


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

        /* a counter for the main while loop, 1 loop = 1 step in time */
        int timeStep = 0;
        int *pTimeStep = &timeStep;

        /* ----------------Main simulation loop -------------------------*/ 
        while(1){

            /* timestep */
            *pTimeStep = *pTimeStep + 1;
            
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
                if (*pTimeStep<= 500){

                    /* zero or one car left queue */
                    *pJoinLeft = randomFloatNum();
                    if (*pJoinLeft < leftArrivalRate){
                        /* add cars with its current time it entered the queue */
                        enqueue(pLeftQueue, *pTimeStep);
                        *pLeftCarAdded = *pLeftCarAdded + 1;
                        *pCarAddedCounter = *pCarAddedCounter + 1;
                    }

                    /* zero or one car right queue */
                    *pJoinRight = randomIntNum();
                    if (*pJoinRight < rightArrivalRate){
                        /* add cars with its current time it entered the queue */
                        enqueue(pRightQueue, *pTimeStep);
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
                            /* left car leaves queue */
                            dequeue(pLeftQueue);
                            *pLeftCarpassed = *pLeftCarpassed + 1;

                            /* calculate time it took car to leave queue and add to variable */
                            int leftCurrentCarWaitingTime = returnCarTime(pLeftQueue->front);
                            int leftDifferenceInleaving = *pTimeStep - leftCurrentCarWaitingTime;
                            leftAverageWaitingTime = leftAverageWaitingTime + leftDifferenceInleaving;
                            if (leftMaxWaitingTime < leftDifferenceInleaving){
                                leftMaxWaitingTime = leftDifferenceInleaving;
                            }

                        }

                        /* Check if the left queue is ont empty */
                        if (leftNotEmpty == 0){
                            /* printf("...Left queue is now empty... \n"); */
                            *pLeftClearanceTime = *pTimeStep;
                        }
                        
                        /* Check if left and right queues are empty, if so break */
                        if ( (leftNotEmpty == 0) && (rightNotEmpty == 0) ){
                            break;
                        }
                    } 
                    /* check lights to see if right car queue can through  */
                    if (*pRightLight == 1){

                        /* Right is not empty dequeue a car */
                        if (rightNotEmpty == 1){
                            *pRightCarpassed = *pRightCarpassed + 1;
                            dequeue(pRightQueue);

                            /* calculate time it took car to leave queue and add to variable */
                            int rightCurrentCarWaitingTime = returnCarTime(pRightQueue->front);
                            int rightDifferenceInleaving = *pTimeStep - rightCurrentCarWaitingTime;
                            rightAverageWaitingTime = rightAverageWaitingTime + rightDifferenceInleaving;
                            if (rightMaxWaitingTime < rightDifferenceInleaving){
                                rightMaxWaitingTime = rightDifferenceInleaving;
                            }
                        }
                        
                        /* Check if right queue is empty, if it is mark down the time it took the queue to finish */
                        if (rightNotEmpty == 0){
                            *pRightClearanceTime = *pTimeStep;
                        }
                        /* Check if left and right queues are empty, if so break */
                        if ( (leftNotEmpty == 0) && (rightNotEmpty == 0) ){
                            break;
                        }

                    }
                }
            } 
            else 
            {

            }
        }
        /* calculate total cars passed that iteration */
        *pTotalCarsPassed = *pLeftCarpassed + *pRightCarpassed;

        /* Calculate average waiting time for left cars */
        leftAverageWaitingTime = leftAverageWaitingTime / *pLeftCarAdded;

        /* Calculate average waiting time for right cars */
        leftAverageWaitingTime = leftAverageWaitingTime / *pLeftCarAdded;
        rightAverageWaitingTime = rightAverageWaitingTime / *pRightCarAdded;


        /* -------------------- This code was meant fo run multiple simulations ----- */
        multipleleftNumberOfVehicles = *pLeftCarAdded;
        multipleleftAverageWaitingTime = leftAverageWaitingTime;
        multipleleftMaxWaitingTime = leftMaxWaitingTime;
        multipleleftClearanceTime = *pLeftClearanceTime;

        multiplerightNumberOfVehicles = *pRightCarAdded;
        multiplerightAverageWaitingTime = rightAverageWaitingTime;
        multiplerightMaxWaitingTime = rightMaxWaitingTime;
        multiplerightClearanceTime = *pRightClearanceTime;


        /* assigning defualt values after they have been changed to the array */
        float multipleSimulationsData[8] = {
            multipleleftNumberOfVehicles,
            multipleleftAverageWaitingTime,
            multipleleftMaxWaitingTime,
            multipleleftClearanceTime,
            multiplerightNumberOfVehicles,
            multiplerightAverageWaitingTime,
            multiplerightMaxWaitingTime,
            multiplerightClearanceTime
        };

        /* --------------------------------------------------------------- */

        printf("Results (from one simulation) \n");
        printf("    from left: \n");
        printf("        number of vehicles: %f \n", multipleSimulationsData[0]);
        printf("        average waiting time: %f, \n", multipleSimulationsData[1]);
        printf("        maximum waiting time: %f \n", multipleSimulationsData[2]);
        printf("        clearance time: %f \n", multipleSimulationsData[3]);
        printf("    from right: \n");
        printf("        number of vehicles: %f \n", multipleSimulationsData[4]);
        printf("        average waiting time: %f \n", multipleSimulationsData[5]);
        printf("        maximum waiting time: %f \n", multipleSimulationsData[6]);
        printf("        clearance time: %f \n", multipleSimulationsData[7]);
        printf(" \n...total time to complete: %d timesteps...\n", *pTimeStep);

        /* Freeing the queues from memory */
        free(pLeftQueue);
        free(pRightQueue);
    }

}


void runSimulations(){
    /* Default input values */
    float leftTrafficArriveRate = 0.5;
    float leftLightPeroid = 0.5;
    float rightTrafficeArriveRate = 0.5;
    float rightLightPeroid = 0.5;

    /* 
    Had a bug in code where could not return a array from function.
    The way I would have implemented this was to have the runOneSimulation return that simulations
    data in an array. Then have a larger while loop with would loop through 500 iterations,
    in which afterwards a calculation would add up all of the total cars on the left,
    total cars on the right, and take the averages of them all. However due to the bug causes lots of time
    I was not able to fully finish up the last bits of code fo runSimulations() function. However 
    I fully understand how the logic works but am un able to implement it due to the time looss
    
    */ 

    runOneSimulation(0 ,leftLightPeroid, leftLightPeroid, rightTrafficeArriveRate, rightLightPeroid);

}


/* Function code: ------------------------------------------ */
int main()
{
    /* Default Hardcoded input */
    float leftTrafficArriveRate = 0.5;
    float leftLightPeroid = 0.5;
    float rightTrafficeArriveRate = 0.5;
    float rightLightPeroid = 0.5;

    /* Take in user input */
    printf("Please input parameters (Reccomended 0.5 for each parameter for even run): \n");
    printf("    leftTrafficArrivalRate: ");
    scanf("%f", &leftTrafficArriveRate);
    printf("    leftLightPeroid: ");
    scanf("%f", &leftLightPeroid);
    printf("    rightTrafficeArriveRate: ");
    scanf("%f", &rightTrafficeArriveRate);
    printf("    rightLightPeroid: ");
    scanf("%f", &rightLightPeroid);
    printf("\n");

    printf("Parameter values: \n");
    printf("    from left: \n");
    printf("        traffic arrival rate: %f \n", leftTrafficArriveRate);
    printf("        traffic light peroid: %f \n", leftLightPeroid);
    printf("    from right: \n");
    printf("        traffic arrival rate: %f \n", rightTrafficeArriveRate);
    printf("        traffic light peroid: %f \n", rightLightPeroid);

    runOneSimulation(0, leftTrafficArriveRate, leftLightPeroid, rightTrafficeArriveRate, rightLightPeroid);

    return 0;
}