/* Library Includes: ---------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>
#include <sys/time.h>

/* Defines --------------------------------------------------*/
#define TRUE 1
#define FALSE 0
#define FULL 10

/* Struct and Objects --------------------------------------*/

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

/* Prototypes ------------------------------------------------*/