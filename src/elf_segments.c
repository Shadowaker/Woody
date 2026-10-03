
#include <stdio.h>
#include "woody.h"


/*
    Set up ehdr/phdr pointers and find:
        - code_seg: the first PT_LOAD with PF_X, the code to be encrypted
        - note_seg: the first PT_NOTE, to be repurposed its phdr slot into a PT_LOAD
    Each PT_LOAD's file range is bounds-checked against the buffer so a strange
    p_offset/p_filesz can't read or encrypt out of bounds.
*/
int locate_segments(t_elf *elf)
{
    Elf64_Phdr  *ph;
    uint16_t    i;
    size_t      end;

    elf->ehdr = (Elf64_Ehdr *) elf->buf;
    elf->phdr = (Elf64_Phdr *) (elf->buf + elf->ehdr->e_phoff);
    elf->is_pie = (elf->ehdr->e_type == ET_DYN);

    i = 0;
    while (i < elf->ehdr->e_phnum)
    {
        ph = &elf->phdr[i];
        if (ph->p_type == PT_LOAD)
        {
            end = ph->p_offset + ph->p_filesz;
            if (end > elf->size || end < ph->p_offset)
                return (fputs("Malformed ELF: segment otu of bounds.\n", stderr), 1);
            if ((ph->p_flags & PF_X) && !elf->code_seg && ph->p_filesz > 0)
                elf->code_seg = ph;
        }
        else if (ph->p_type == PT_NOTE && !elf->note_seg)
            elf->note_seg = ph;
        i++;
    }
    if (!elf->code_seg)
        return (fputs("No executable segment found.\n", stderr), 1);
    if (!elf->note_seg)
        return (fputs("No PT_NOTE segment to repurpose.\n", stderr), 1);
    return (0);
}