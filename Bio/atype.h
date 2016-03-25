#include <stdint.h>
/*
      atype.h   Amber general typedef parameters
      Copyright (c) 1990 Amber Systems
      14MAR03 kbr removed UINT, already defined in UNIX
      24FEB14 kbr add ulong missing for Darwin
      23OCT14 kbr used only types from stdint.h so compiles will work on 
                  64BIT OS specifically Power8
*/
/*SYS dependent, huge not required for 32bit compilers */

#ifndef _ATYPE
   #define _ATYPE
   typedef float *Aadrs;    /* float arrays > 64k */
   typedef char  *Cadrs;    /* char  arrays > 64k */
   typedef float *Fadrs;    /* float arrays > 64k */
   typedef int32_t   *Iadrs;    /* int   arrays > 64k */
   typedef int32_t  *Ladrs;    /* long  arrays > 64k */
   typedef int16_t *Sadrs;    /* short arrays > 64k */

   typedef   int8_t    int8;
   typedef  uint8_t   uint8;
   typedef  int16_t   int16;
   typedef uint16_t  uint16;
   typedef  int32_t   int32;
   typedef uint32_t  uint32;
   typedef  int64_t   int64;
   typedef uint64_t  uint64;

#ifdef _AMB_OSX
   typedef uint32_t ulong;
#endif

  
#endif

#ifdef _AMB_WINDOWS
#ifndef  _UINT
   #define _UINT
   typedef uint32_t uint;
#endif
#endif

