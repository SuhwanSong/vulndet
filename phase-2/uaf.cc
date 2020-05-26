#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

bool copyToBuffer(const uint8_t* Data, size_t Size,
                  uint8_t* &dst, uint8_t* &pMax,
                  uint8_t& vMax) {
    const static size_t kDefaultBufferSize = 4;

    if (Size < 1)
        return false;

    uint8_t* curBuf;

    if (!dst) {
        // Allocate a buffer with default size
        dst = (uint8_t*) malloc(sizeof(uint8_t) * kDefaultBufferSize);
        curBuf = dst;
    } else {
        return false;
    }

    // Copy Data to buf
    for (size_t i = 0; i < kDefaultBufferSize; i++) {
        // All data is copied
        if (i >= Size)
            return true;

        curBuf[i] = Data[i];
        if (curBuf[i] >= vMax) {
            pMax = (curBuf+ i);
            vMax = curBuf[i];
        }
    }

    // If buf is full, allocate a larger buffer
    if (Size > kDefaultBufferSize) {
        uint8_t *newBuf = (uint8_t*) malloc(sizeof(uint8_t) * Size);
        memcpy(newBuf, curBuf, kDefaultBufferSize);
        free(curBuf);

        dst = newBuf;
        curBuf = dst;
    }

    for (size_t i = kDefaultBufferSize; i < Size; i++) {
        // All data is copied
        if (i >= Size)
            return true;

        curBuf[i] = Data[i];
        if (curBuf[i] >= vMax) {
            pMax = (curBuf+ i);
            vMax = curBuf[i];
        }
    }

    return true;
}

void overrideMax(uint8_t* pMax, uint8_t oldMax, uint8_t newMax) {
    if (pMax == nullptr)
        return;

    if (oldMax >= newMax)
        return;

    *pMax = newMax;
}
