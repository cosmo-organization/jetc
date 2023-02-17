#pragma once
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <cstdint>
#include <array>
#include <fstream>
#include "jetcpreprocessor.hpp"
#include "jetcstream.hpp"

namespace jetc {

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

    template<typename T,size_t Size>
    SerializedBufferStream& operator<<(SerializedBufferStream& out, std::array<T, Size> objIn) {
        out << (int)Size;
        for (T element : objIn) {
            out << element;
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




    template<typename T>
    SerializedBufferStream serialize(T t) {
        SerializedBufferStream sbs;
        sbs << (int)MAGIC << (short)MAJVER << (short)MINVER << (short)PATCHVER << t;
        return sbs;
    }
}