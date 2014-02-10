#ifndef _GENERAL_TYPES_H_
#define _GENERAL_TYPES_H_

typedef double capital;
typedef long shares;

#include <string.h>
#ifndef savestring /* eventually clean this up */
/*
 * macro: savestring()
 * preconditions:  +x is null-terminated string
 *                 +memory of size strlen(x) + 1 is available
 * postconditions: +memory is allocated the size of x
 *                 +the string in x is copied to the new memory
 * parameters:     +x : string to be copied
 * returns:        +pointer to new memory where x was copied
 * notes: does not handle malloc failing to allocate memory
 */
#define savestring(x) (strcpy( malloc( strlen(x) + 1 ), (x) ))
#endif

#endif
