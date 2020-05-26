#include <cstdio>
#include <cstdint>
#include <cstring>

void vuln(const uint8_t* data, size_t size) {
    uint8_t buf[4];

    if (size < 4)
        return;

    if (data[0] == 'T')
        if (data[1] == 'E')
            // maybe out-of-bound access
            memcpy(buf, data, size);

    return;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    vuln(data, size);
    return 0;
}
