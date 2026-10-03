NAME      = woody_woodpacker

CC        = gcc
CFLAGS    = -Wall -Wextra -Werror -I include -I libft

SRC_DIR   = src
SRCS      = main.c error.c elf_load.c elf_validate.c free_elf.c elf_segments.c
OBJS      = $(addprefix $(SRC_DIR)/, $(SRCS:.c=.o))

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

all: $(NAME)

# Build libft.a via its own Makefile.
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Objects first, then the archive, so static linking resolves symbols.
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
