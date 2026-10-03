#include <stdio.h>
#include "woody.h"


int main(int argc, char **argv)
{
    t_elf   elf;
    uint8_t	key[WOODY_KEY_LEN];

    if (argc != 2)
        return (fputs("Executable argument missing\n", stderr), 1);

    load_file(argv[1], &elf);
    if (validate_elf(&elf))
        return (free_elf(&elf), 1);
    
    if (locate_segments(&elf))
        return (free_elf(&elf), 1);

    gen_key(key, WOODY_KEY_LEN);

    // Imagine the injection here
    // Imagine the encryption here
    // Image the binary creation here
    // Print the key here
    free_elf(&elf);
    return (0); 
}