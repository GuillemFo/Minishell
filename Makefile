NAME = minishell

OBJ_PATH = tmp/

SRC_PATH = SRC/

RDLINE_PATH = readline/

SRC = minishell.c #all *.c here

SRC_PREFIX = $(addprefix $(SRC_PATH), $(SRC))

OBJ = $(addprefix $(OBJ_PATH), $(SRC_PREFIX:.c=.o))

CFLAGS = -Wall -Wextra -Werror -I./Include ./libft/

all: makelibft tmp $(NAME)

tmp:
		mkdir -p $(OBJ_PATH)

$(NAME): $(OBJ)
		cc $(CFLAGS) $(OBJ) ./libft/libft.a -o $(NAME)

makelibft:
		$(MAKE) -C ./libft #add command from libft to create the .a

$(OBJ_PATH)%.o: %.c ./libft/libft.h ./Include/minishell.h ./libft/libft.a Makefile
		@mkdir	-p $(dir $@)
		cc $(CFLAGS) -g -c $< -o $@

re: fclean all

libftfclean:
		$(MAKE) -C ./libft fclean

libftclean:
		$(MAKE) -C ./libft clean

clean:	libftclean
		rm -rf $(OBJ_PATH)

fclean:	clean libftfclean
		rm -rf $(NAME)

.PHONY: all re clean fclean 

#### Missing Readline makefile rules ####