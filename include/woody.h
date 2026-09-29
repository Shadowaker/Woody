#ifndef WOODY_H
# define WOODY_H

# include <stddef.h>
# include <stdint.h>
# include <elf.h>

# define WOODY_OUTPUT   "woody"
# define PAGE_SIZE      0x1000UL	// 4096	

/* 
	t_elf holds the working copy of the target binary. `buf` is a heap copy of the
	whole input file, oversized to leave room for the appended stub segment.
*/
typedef struct s_elf
{
	uint8_t		*buf;       // copy of the file
	size_t		size;       // current logical size of buf
	size_t		capacity;   // allocated bytes
	size_t		orig_size;  // original file size before any appending

	Elf64_Ehdr	*ehdr;      // -> buf[0]
	Elf64_Phdr	*phdr;      // -> buf[e_phoff]

	Elf64_Phdr	*code_seg;	// stored encrypted code
	Elf64_Phdr	*note_seg;	// pt note header repurposed
	/*
	From the elf(5)
	PT_LOAD
                        The array element specifies a loadable segment,
                        described by p_filesz and p_memsz.  The bytes
                        from the file are mapped to the beginning of the
                        memory segment.  If the segment's memory size
                        p_memsz is larger than the file size p_filesz,
                        the "extra" bytes are defined to hold the value 0
                        and to follow the segment's initialized area.
                        The file size may not be larger than the memory
                        size.  Loadable segment entries in the program
                        header table appear in ascending order, sorted on
                        the p_vaddr member.
	*/

	int			is_pie;     // ET_DYN
}	t_elf;


#endif
