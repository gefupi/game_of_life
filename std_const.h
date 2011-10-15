#ifndef _STD_CONST_H_
#define _STD_CONST_H_

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE !FALSE
#endif

#define LIFE 1
#define DEAD 0
#define INVALID -1

#define NO_RESIZE (1<<1)
#define UP (1<<2)
#define RIGHT (1<<3)
#define DOWN (1<<4)
#define LEFT (1<<5)

#define DEF_RESIZE_ADDITION 10

#define MAX_THREADS 2

#ifndef LIFE_CHAR
#define LIFE_CHAR 1
#endif

#ifndef DEAD_CHAR
#define DEAD_CHAR !LIFE_CHAR
#endif

#ifndef DEFAULT_MAX_GENERATION
//                             10.000.000
#define DEFAULT_MAX_GENERATION 10000000
#endif

#ifndef LIVE
#define LIVE 1
#endif

/* #ifndef DEBUG_VERBOSE_VARS */
/* #define DEBUG_VERBOSE_VARS */
/* int debug = FALSE; */
/* int verbose = FALSE; */
/* #endif */


#endif // _STD_CONST_H_
