#include <stdlib.h>

void	free_elf(t_elf *elf) // dobby
{
	if (elf->buf)
		free(elf->buf);
	elf->buf = NULL;
}