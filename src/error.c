#include <stdio.h>
#include <stdlib.h>
#include "woody.h"

void	fatal(const char *msg)
{
	perror(msg);
	exit(1);
}

void	fatal_str(const char *msg)
{
	fputs(msg, stderr);
	exit(1);
}

void	*e_malloc(size_t n)
{
	void	*p;

	p = malloc(n);
	if (!p)
		fatal("malloc");
	return (p);
}
