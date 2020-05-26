#include <cstdint>
#include <cstddef>

bool copyToBuffer(const uint8_t* Data, size_t Size,
                  uint8_t* &dst, uint8_t* &pMax,
                  uint8_t& vMax);

void overrideMax(uint8_t* pMax, uint8_t oldMax, uint8_t newMax);
