/* Library Includes: ---------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>
#include <sys/time.h>


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