/** 
 * Definitions for basic kernel types
 **/


typedef uint8_t uuid_t[16];


/**
 * Return Codes
 **/

typedef uint32_t kstatus_t;

#define ENOTFOUND       0x80000001
#define EINSUFFICIENT   0x80000002

#define ERROR(n) ( n != 0 )

