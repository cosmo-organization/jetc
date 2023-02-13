#pragma once
/*@autor Sonu Aryan 
*/
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <cstdint>
#include <fstream>
#include "endianness.h"
#define MAGIC 0x6A657463 //jetc
#define MAJVER 1
#define MINVER 0
#define PATCHVER 0

#define MLITTLE_ENDIAN 0
#define MBIG_ENDIAN 1

#if ENDIANNESS_LE == 1
#define MBYTE_ORDER MLITTLE_ENDIAN
#elif ENDIANNESS_BE ==  1
#define MBYTE_ORDER MBIG_ENDIAN
#endif


#if MBYTE_ORDER==MLITTLE_ENDIAN
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


namespace jetc {

    struct SerializedBufferStream {
        std::vector<uint8_t> Buffer;
        int mark = 0;
        void reset() {
            mark = 0;
        }
        void setmark(int mark) {
            this->mark = mark;
        }

        uint8_t next() {
            if (mark == Buffer.size())return -1;
            return Buffer.at(mark++);
        }
    };

    SerializedBufferStream& operator<<(SerializedBufferStream& out, bool objIn) {
        out.Buffer.push_back(objIn);
        return out;
    }

    SerializedBufferStream& operator<<(SerializedBufferStream& out, char objIn) {
        out.Buffer.push_back(objIn);
        return out;
    }



    SerializedBufferStream& operator<<(SerializedBufferStream& out, short objIn) {
        DUALPACK(short, objIn, out)
            return out;
    }




    SerializedBufferStream& operator<<(SerializedBufferStream& out, int objIn) {
        QUADPACK(int, objIn, out)
            return out;
    }




    SerializedBufferStream& operator<<(SerializedBufferStream& out, long objIn) {
        QUADPACK(long, objIn, out)
            return out;
    }




    SerializedBufferStream& operator<<(SerializedBufferStream& out, long long objIn) {

        OCTAPACK(long long, objIn, out)
            return out;
    }





    SerializedBufferStream& operator<<(SerializedBufferStream& out, float objIn) {

        QUADPACK(float, objIn, out)
            return out;
    }



    SerializedBufferStream& operator<<(SerializedBufferStream& out, double objIn) {
        OCTAPACK(double, objIn, out)
            return out;
    }




    SerializedBufferStream& operator<<(SerializedBufferStream& out, std::string objIn) {
        int byteLen = (int)objIn.size();
        byteLen += 1;
        byteLen &= 0xFFFFFFFF;
        out << byteLen;
        for (int i = 0; i < byteLen; i++) {
            out << objIn.c_str()[i];
        }
        return out;
    }


    template<typename T>
    SerializedBufferStream& operator<<(SerializedBufferStream& out, std::vector<T> objIn) {
        int size = objIn.size() & 0xFFFFFFFF;
        out << size;
        for (T t : objIn) {
            out << t;
        }
        return out;
    }

    template<typename T>
    SerializedBufferStream& operator<<(SerializedBufferStream& out, std::list<T> objIn) {
        int size = objIn.size() & 0xFFFFFFFF;
        out << size;
        for (T t : objIn) {
            out << t;
        }
        return out;
    }



    template<typename kT, typename vT>
    SerializedBufferStream& operator<<(SerializedBufferStream& out, std::pair<kT, vT> kvpair) {
        out << kvpair.first << kvpair.second;
        return out;
    }

    template<typename kT, typename vT>
    SerializedBufferStream& operator<<(SerializedBufferStream& out, std::map<kT, vT> objIn) {
        int size = objIn.size() & 0xFFFFFFFF;
        out << size;
        for (std::pair<kT, vT> kvpair : objIn) {
            out << kvpair;
        }
        return out;
    }


    std::ostream& operator<<(std::ostream& out, SerializedBufferStream sbs) {
        for (uint8_t c : sbs.Buffer) {
            printf("%c", c);
        }
        return out;
    }


    std::ofstream& operator<<(std::ofstream& outFile, SerializedBufferStream sbs) {
        for (uint8_t c : sbs.Buffer) {
            outFile << c;
        }
        return outFile;
    }





    SerializedBufferStream& operator>>(SerializedBufferStream& in, char& objOut) {
        objOut = in.next() & 0xFF;
        return in;
    }

    SerializedBufferStream& operator>>(SerializedBufferStream& in, bool& objOut) {
        objOut = in.next() & 0xFF;
        return in;
    }

    SerializedBufferStream& operator>>(SerializedBufferStream& in, int& objOut) {
        QUADUNPACK(int, in, objOut)
            return in;
    }

    SerializedBufferStream& operator>>(SerializedBufferStream& in, short& objOut) {
        DUALUNPACK(short, in, objOut);
        return in;
    }

    SerializedBufferStream& operator>>(SerializedBufferStream& in, float& objOut) {
        QUADUNPACK(float, in, objOut);
        return in;
    }

    SerializedBufferStream& operator>>(SerializedBufferStream& in, double& objOut) {
        OCTAUNPACK(double, in, objOut);
        return in;
    }

    SerializedBufferStream& operator>>(SerializedBufferStream& in, long& objOut) {
        QUADUNPACK(long, in, objOut);
        return in;
    }

    SerializedBufferStream& operator>>(SerializedBufferStream& in, long long& objOut) {
        OCTAUNPACK(long long, in, objOut);
        return in;
    }

    SerializedBufferStream& operator>>(SerializedBufferStream& in, std::string& objOut) {
        int size;
        in >> size;
        char* buff = new char[size];
        for (int i = 0; i < size; i++) {
            in >> buff[i];
        }
        objOut = buff;
        return in;
    }

    template<typename T>
    SerializedBufferStream& operator>>(SerializedBufferStream& in, std::vector<T>& objOut) {
        int size;
        in >> size;
        for (int i = 0; i < size; i++) {
            T value;
            in >> value;
            objOut.emplace_back(value);
        }
        return in;
    }

    template<typename T>
    SerializedBufferStream& operator>>(SerializedBufferStream& in, std::list<T>& objOut) {
        int size;
        in >> size;
        for (int i = 0; i < size; i++) {
            T value;
            in >> value;
            objOut.emplace_back(value);
        }
        return in;
    }

    template<typename kT, typename vT>
    SerializedBufferStream& operator>>(SerializedBufferStream& in, std::pair<kT, vT>& objOut) {
        in >> objOut.first >> objOut.second;
        return in;
    }

    template<typename kT, typename vT>
    SerializedBufferStream& operator>>(SerializedBufferStream& in, std::map<kT, vT>& objOut) {
        int size;
        in >> size;
        for (int i = 0; i < size; i++) {
            std::pair<kT, vT> kvpair;
            in >> kvpair;
            objOut.emplace(kvpair);
        }

        return in;
    }

    template<typename T>
    SerializedBufferStream serialize(T t) {
        SerializedBufferStream sbs;
        sbs << (int)MAGIC << (short)MAJVER << (short)MINVER << (short)PATCHVER << t;
        return sbs;
    }


    template<typename T>

    T deserialize(SerializedBufferStream in) noexcept(false){
        int magic;
        short major;
        short minor;
        short patch;
        in >> magic >> major >> minor >> patch;

        if (magic != MAGIC)throw std::runtime_error("Not a valid jetc format binary!");

        if (major != MAJVER) {
            char msgBuff[100];
            sprintf_s(msgBuff, "Invalid version! expected %d or lower but found %d", MAJVER, major);
            throw std::runtime_error(msgBuff);
        }

        T value;
        in >> value;
        return value;
    }

}