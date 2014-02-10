#ifndef _GENERAL_TYPES_H_
#define _GENERAL_TYPES_H_

#include <string.h>

/**
 * macro: savestring()
 * parameters:     +x : string to be copied
 * preconditions:  +x is null-terminated string
 *                 +memory of size strlen(x) + 1 is available
 * postconditions: +memory is allocated the size of x
 *                 +the string in x is copied to the new memory
 * returns:        +pointer to new memory where x was copied
 * notes: does not handle malloc failing to allocate memory
 */
#ifndef savestring /* eventually clean this up */
#define savestring(x) (strcpy( malloc( strlen(x) + 1 ), (x) ))
#endif

typedef double capital;
typedef long shares;

#ifndef NULL
#define NULL 0
#endif

#endif
