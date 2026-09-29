#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"
#include "woody.h"


int load_file(char *path, t_elf *elf)
{
    int     fd;
    off_t   size;
    ssize_t r;
    size_t  off;

    ft_memset(elf, 0, sizeof(*elf));
    fd = open(path, O_RDONLY);

    if (fd < 0)
        fatal(path);
    
    size = lseek(fd, 0, SEEK_END);
    if (size < 0 || lseek(fd, 0, SEEK_SET) < 0)
    {
        close(fd);
        fatal("lseek");
    }

    if (size > (off_t)(1UL << 30))
    {
        close(fd);
        fatal_str("File too large or not a regular file\n");
    }
    
    elf->orig_size = (size_t) size;
    elf->size = (size_t) size;
    elf->capacity = (size_t) size + 2 * PAGE_SIZE + 0x10000;    // 0x10000 == 65536, a very big number
    elf->buf = e_malloc(elf->capacity);
    
    off = 0;
    while (off < elf->size)
    {
        r = read(fd, elf->buf + off, elf->size - off);
		if (r < 0)
		{
			close(fd);
			free(elf->buf);
			fatal("read");
		}
		if (r == 0)
			break ;
		off += (size_t)r;
    }

    close(fd);
    if (off != elf->size)
    {
        free(elf->buf);
        fatal_str("Unexpected end of file.\n");
    }
    return (0);
}