#include <stdio.h>
#include "woody.h"

int validate_elf(const t_elf *elf)
{
    const Elf64_Ehdr    *e;
    size_t              ph_end;

    if (elf->size < sizeof(Elf64_Ehdr))
        return (fputs("Not an ELF file\n", stderr), 1);

    e = (const Elf64_Ehdr *) elf->buf;

    // According to man elf(5) every EI_MAG* must be filled with ELFMAG* to be valid
    if (e->e_ident[EI_MAG0] != ELFMAG0 || e->e_ident[EI_MAG1] != ELFMAG1
        || e->e_ident[EI_MAG2] != ELFMAG2 || e->e_ident[EI_MAG3] != ELFMAG3)
        return (fputs("Not an ELF file\n", stderr), 1);
    
    // Check if the ELF is x86
    if (e->e_ident[EI_CLASS] != ELFCLASS64 
        || e->e_ident[EI_DATA] != ELFDATA2LSB 
        || e->e_machine != EM_X86_64)
        return (fputs("File architecture not supported.\n", stderr), 1);
    
    // Accepted only executables and linkable libraries
    if (e->e_type != ET_EXEC && e->e_type != ET_DYN)
        return (fputs("Only ET_EXEC and ET_DYN supported.\n", stderr), 1);

    // Bad header check
    if (e->e_phentsize != sizeof(Elf64_Phdr) || e->e_phnum == 0)
        return (fputs("Malformed ELF: bad program header table\n", stderr), 1);

    ph_end = e->e_phoff + (size_t)e->e_phnum * e->e_phentsize;
    if (e->e_phoff >= elf->size || ph_end > elf->size || ph_end < e->e_phoff)
        return (fputs("Malformed ELF: program headers out of bounds\n", stderr), 1);

    return (0);
}