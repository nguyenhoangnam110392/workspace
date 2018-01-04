#ifndef LT_STM8S_MACRO_H_
#define LT_STM8S_MACRO_H_

typedef  unsigned  char                 u8;  /*  8  bits */
typedef  unsigned  short int            u16; /*  16 bits */
typedef  unsigned  long  int            u32; /*  32 bits */
//typedef  unsigned  long  long         u64; /*  64 bits */ // also the 4Byte

typedef  char                           s8;  /*  8  bits */
typedef  short int                      s16; /*  16 bits */
typedef  long  int                      s32; /*  32 bits */
//typedef  long  long                   s64; /*  64 bits */

typedef  volatile   s8                  vs8;  /*  8 bits */
typedef  volatile   s16                 vs16; /* 16 bits */
typedef  volatile   s32                 vs32; /* 32 bits */
//typedef  volatile   s64               vs64; /* 64 bits */ 

typedef  volatile   u8                  vu8;  /*  8 bits */
typedef  volatile   u16                 vu16; /* 16 bits */
typedef  volatile   u32                 vu32; /* 32 bits */
//typedef  volatile   u64               vu64; /* 64 bits */ 
//QUESTION: long long int  &  long long

#endif
