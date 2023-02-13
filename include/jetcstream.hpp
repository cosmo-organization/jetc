#pragma once
#include <vector>
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
        void clear() {
            Buffer.clear();
        }
    };
}