#pragma once
#include "endianness.h"

#define MAGIC 0x6A657463 //jetc
#define MAJVER 1
#define MINVER 0
#define PATCHVER 0


#if defined(MLITTLE_ENDIAN)
#define OCTAPACK(type,input,output)\
    union{\
        type objIn;\
        char bytes[8];\
    }convertor;\
    convertor.objIn=input;\
    output << convertor.bytes[7] << convertor.bytes[6] << convertor.bytes[5] <<convertor.bytes[4]<< convertor.bytes[3] << convertor.bytes[2] << convertor.bytes[1] << convertor.bytes[0];

#define OCTAUNPACK(type,input,output)\
   union {\
        char bytesIn[8];\
        type objOut;\
   }convertor;\
   input>>convertor.bytesIn[7]>>convertor.bytesIn[6]>>convertor.bytesIn[5] >>convertor.bytesIn[4]>> convertor.bytesIn[3]>>convertor.bytesIn[2]>>convertor.bytesIn[1]>>convertor.bytesIn[0];\
   output=convertor.objOut;

#define QUADPACK(type,input,output)\
    union{\
        type objIn;\
        char bytes[4];\
    }convertor;\
    convertor.objIn=input;\
    output <<convertor.bytes[3] << convertor.bytes[2] << convertor.bytes[1] << convertor.bytes[0];

#define QUADUNPACK(type,input,output)\
   union {\
        char bytesIn[4];\
        type objOut;\
   }convertor;\
   input>> convertor.bytesIn[3]>>convertor.bytesIn[2]>>convertor.bytesIn[1]>>convertor.bytesIn[0];\
   output=convertor.objOut;

#define DUALPACK(type,input,output)\
    union{\
        type objIn;\
        char bytes[2];\
    }convertor;\
    convertor.objIn=input;\
    output << convertor.bytes[1] << convertor.bytes[0];

#define DUALUNPACK(type,input,output)\
   union {\
        char bytesIn[2];\
        type objOut;\
   }convertor;\
   input>>convertor.bytesIn[1]>>convertor.bytesIn[0];\
   output=convertor.objOut;

#else
#define OCTAPACK(type,input,output)\
    union {\
            type objIn; \
            char bytes[8]; \
    }convertor; \
    convertor.objIn = input;\
    output << convertor.bytes[0] << convertor.bytes[1] << convertor.bytes[2] << convertor.bytes[3] << convertor.bytes[4] << convertor.bytes[5] << convertor.bytes[6] << convertor.bytes[7];

#define OCTAUNPACK(type,input,output)\
   union {\
        char bytesIn[8];\
        type objOut;\
   }convertor;\
   input>>convertor.bytesIn[0]>>convertor.bytesIn[1]>>convertor.bytesIn[2] >>convertor.bytesIn[3]>> convertor.bytesIn[4]>>convertor.bytesIn[5]>>convertor.bytesIn[6]>>convertor.bytesIn[7];\
   output=convertor.objOut;

#define QUADPACK(type,input,output)\
    union {\
        type objIn; \
        char bytes[4]; \
    }convertor; \
    convertor.objIn = input;\
    output << convertor.bytes[0] << convertor.bytes[1] << convertor.bytes[2] << convertor.bytes[3];

#define QUADUNPACK(type,input,output)\
   union {\
        char bytesIn[4];\
        type objOut;\
   }convertor;\
   input>> convertor.bytesIn[0]>>convertor.bytesIn[1]>>convertor.bytesIn[2]>>convertor.bytesIn[3];\
   output=convertor.objOut;


#define DUALPACK(type,input,output)\
    union{\
        type objIn;\
        char bytes[2];\
    }convertor;\
    convertor.objIn=input;\
    output << convertor.bytes[0] << convertor.bytes[1];

#define DUALUNPACK(type,input,output)\
   union {\
        char bytesIn[2];\
        type objOut;\
   }convertor;\
   input>>convertor.bytesIn[0]>>convertor.bytesIn[1];\
   output=convertor.objOut;

#endif