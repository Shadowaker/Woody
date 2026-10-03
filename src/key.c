#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "woody.h"

int gen_key(uint8_t *key, size_t len)
{
    int         fd;
    ssize_t     r;
    size_t      off;

    fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0)
        fatal("/dev/urandom");

    off = 0;
    while (off < len)
    {
        r = read(fd, key + off, len - off);
        if (r <= 0)
        {
            close(fd);
            fatal("read /dev/urandom");
        }
        off += (size_t) r;
    }
    close(fd);
    return (0);
}