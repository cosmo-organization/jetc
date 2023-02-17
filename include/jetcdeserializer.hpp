#pragma once
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <cstdint>
#include <array>
#include <fstream>
#include "jetcstream.hpp"
#include "jetcpreprocessor.hpp"

namespace jetc {
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

    template<typename T,size_t Size>
    SerializedBufferStream& operator>>(SerializedBufferStream& in, std::array<T, Size>& objOut){
        int size;
        in >> size;
        if (Size != size) {
            char errorBuff[100];
            #if defined(_MSC_VER)
            sprintf_s(errorBuff, "expected array size:%zd but found %d\n",Size,size);
            #else
            sprintf(errorBuff,"expected array size:%zd but found %d\n",Size,size);
            #endif
            throw std::runtime_error(errorBuff); 
        }
        for (int i = 0; i < Size; i++) {
            T value;
            in >> value;
            objOut[i] = value;
        }
        return in;
    }

  
    template<typename T>

    T deserialize(SerializedBufferStream in) noexcept(false) {
        int magic;
        short major;
        short minor;
        short patch;
        in >> magic >> major >> minor >> patch;

        if (magic != MAGIC)throw std::runtime_error("Not a valid jetc format binary!");

        if (major != MAJVER) {
            char msgBuff[100];
            #if defined(_MSC_VER)
            sprintf_s(msgBuff, "Invalid version! expected %d or lower but found %d", MAJVER, major);
            #else
            sprintf(msgBuff,"Invalid version! expected %d or lower but found %d",MAJVER,minor);
            #endif
            throw std::runtime_error(msgBuff);
        }

        T value;
        in >> value;
        return value;
    }

}
