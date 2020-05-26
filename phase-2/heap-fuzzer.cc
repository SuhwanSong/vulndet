#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

bool vuln(const uint8_t* data, size_t size) {
    if (size < 4)
        return false;

    if (data[0] == 'T')
        if (data[1] == 'E')
            if (data[2] == 'S')
                if (data[3] == 'T')
                    if (data[4] == '\n')
                        return true;

    return false;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    vuln(data, size);
    return 0;
}
