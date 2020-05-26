#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "uaf.h"

#define handle_error(msg)                               \
    do { perror(msg); exit(EXIT_FAILURE); }  while (0)

void hex_dump(const uint8_t *data, uint32_t size) {
    int32_t remaining = (int32_t) size, offset, i;
    for (offset = 0;
         remaining > 0;
         offset += 8, remaining -= 8) {
        printf("%016x ", data + offset);
        if (remaining < 8) {
            for (i = 0; i < remaining; i++)
                printf("%02x ", *(data + offset + i));
        } else {
            for (i = 0; i < 8; i++)
                printf("%02x ", *(data + offset + i));
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int fd;
    struct stat sb;
    size_t size;
    uint8_t *data;

    if (argc < 2) {
        printf("Usage: %s <arg>\n", argv[0]);
        return 1;
    }

    /////////////////// Do not edit this! ////////////////////////
    // open the input file
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        handle_error("[-] Cannot open the file");

    // get the size of the file
    if (fstat(fd, &sb) == -1)
        handle_error("[-] Cannot fstat the file");

    size = sb.st_size;
    printf("[+] size: %lu\n", size);

    // allocate data buffer
    data = (uint8_t *) malloc(sizeof(uint8_t) * size);

    read(fd, data, size);
    ////////////////////////////////////////////////////////////
    
    uint8_t* buf = nullptr;
    uint8_t* pMax = nullptr;
    uint8_t vMax;

    // invoke vulnarable functions
    if (copyToBuffer(static_cast<const uint8_t*>(data), size,
                     buf, pMax, vMax) != false)
        overrideMax(pMax, vMax, vMax + 1);

    // uncomment this line if you want to dump the content
    // hex_dump(reinterpret_cast<const uint8_t*>(buf), size);

    if (buf)
        free(buf);

    return 0;
}
