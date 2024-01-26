NAME = minishell

OBJ_PATH = tmp/

SRC_PATH = SRC/

RDLINE_PATH = readline/

LIBFT_PATH = libft/

SRC = lexer/lexer_utils.c lexer/lexer.c lexer/split.c lexer/lexer_utils1.c \
		parser/parser.c #all *.c here

SRC_PREFIX = $(addprefix $(SRC_PATH),$(SRC))

OBJ = $(addprefix $(OBJ_PATH),$(SRC_PREFIX:.c=.o))

CFLAGS = -Wall -Wextra -Werror -I./Include -I./libft/libft.h

LIB_A		:=	$(RDLINE_PATH)libreadline.a $(RDLINE_PATH)libhistory.a \
				$(LIBFT_PATH)libft.a

LIB_ADD_DIR	:=	-L$(RDLINE_PATH) -L$(LIBFT_PATH)

LIB_SEARCH	:=	-lreadline -lhistory -ltermcap -lft

all: libraries tmp $(NAME)

tmp:
		@mkdir -p $(OBJ_PATH)

$(NAME): $(OBJ)
		cc $(CFLAGS) $(OBJ) $(LIB_ADD_DIR) $(LIB_SEARCH) $(LIB_A) -o $(NAME)
		@echo "Minishell compiled"
rdline:
		@echo "Compiling Readline"
		@cd ./readline/ &> /dev/null && ./configure &> /dev/null
		@make -C ./readline/ &> /dev/null
		@echo "Readline compiled"

libraries:
		$(MAKE) -C $(LIBFT_PATH) bonus --no-print-directory
#@$(MAKE) rdline --no-print-directory

$(OBJ_PATH)%.o: %.c Makefile $(LIB_A) ./Include/minishell.h
		mkdir	-p $(dir $@)
		cc $(CFLAGS) -g -c $< -o $@
		@echo "Compiling obj $@..."

re: fclean all

clean:
		@$(MAKE) -C libft clean --no-print-directory
		@rm -rf $(OBJ_PATH)
		@echo "Objs deleted"

fclean:	clean
		@$(MAKE) -C libft fclean --no-print-directory
		@rm -rf $(NAME)
		@echo "Minishell deleted"
#@$(MAKE) -C readline clean --no-print-directory

.PHONY: all re clean fclean 

#### NEED TO CREATE RULES TO DO MAKES IN SILENCE ####