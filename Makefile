NAME = minishell

OBJ_PATH = tmp/

INC = Include/

SRC_PATH = SRC/

TMP_DIR = $(CURDIR)/tmp/

RDLINE_PATH = readline/

LIBFT_PATH = libft/


SRC = minishell.c signals.c builtins/builtins.c tools.c builtins/load_env.c \
	expansor/expansor.c quotes/quotes.c lexer/lexer_utils.c lexer/lexer.c lexer/split.c \
	lexer/lexer_utils1.c parser/parser.c parser/parser_utils.c \
	parser/parser_utils1.c executor/execute.c executor/execute_utils.c \
	executor/path.c executor/redir_handle.c executor/execute_utils1.c errors.c \
	executor/execute_utils2.c parser/parser_utils2.c heredock.c	builtins/exit.c \
	shell_lvl/shell_level.c builtins/env_prints.c builtins/env_tools.c \
	builtins/env_tools_extra.c utils.c expansor/expansor_extra.c free_tools.c \
	builtins/export.c builtins/pwd.c errors_2.c quotes/quotes_support_extra.c \
	quotes/quotes_support.c clean_input_support.c minishell_help.c

SRC_PREFIX = $(addprefix $(SRC_PATH),$(SRC))

OBJ = $(addprefix $(OBJ_PATH), $(SRC_PREFIX:.c=.o))

CFLAGS = -I./Include -I./libft -I./$(RDLINE_PATH)  -Wall -Wextra -Werror -g -fsanitize=address


LIB_A		:=	$(RDLINE_PATH)libreadline.a $(RDLINE_PATH)libhistory.a $(LIBFT_PATH)libft.a

LIB_ADD_DIR	:=	-L$(RDLINE_PATH) -L$(LIBFT_PATH)

LIB_SEARCH	:=	-lreadline -lhistory -ltermcap -lft
#############################################################################

# Regular Colors
BLACK := \033[0;30m
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
BLUE := \033[0;34m
MAGENTA := \033[0;35m
CYAN := \033[0;36m
WHITE := \033[0;37m

# Reset
RESET := \033[0m

#############################################################################

all: tmp libraries $(NAME)

tmp:
		@mkdir -p $(OBJ_PATH)

$(NAME): $(OBJ) libraries
		@gcc $(CFLAGS) $(OBJ) $(LIB_ADD_DIR) $(LIB_SEARCH) $(LIB_A) -o $(NAME)
		@echo "$(GREEN)Minishell compiled$(RESET)"

rdline:
		@echo "$(CYAN)Compiling Readline$(RESET)"
		@cd ./readline/ && ./configure
		@make -C ./readline
		@echo "$(GREEN)Readline compiled$(RESET)"

libraries:
		@$(MAKE) -C $(LIBFT_PATH) bonus --no-print-directory
		@$(MAKE) rdline --no-print-directory

$(OBJ_PATH)%.o:%.c Makefile $(LIB_A) $(INC)minishell.h
		@mkdir	-p $(dir $@)
		@gcc $(CFLAGS) -DREADLINE_LIBRARY=1 -I./Include -I./readline -c $< -o $@
		@echo "$(CYAN)Compiling Minishell:$(YELLOW) $@$(RESET)"

re: fclean all

clean:
		@$(MAKE) -C libft clean --no-print-directory
		@echo "$(CYAN)Libft $(YELLOW)- $(RED)Objs deleted$(RESET)"
		@rm -rf $(OBJ_PATH)
		@echo "$(CYAN)Minishell $(YELLOW)- $(RED)Objs deleted$(RESET)"

fclean:	clean
		@$(MAKE) -C libft fclean --no-print-directory
		@echo "$(CYAN)Libft $(RED)deleted$(RESET)"
		@rm -rf $(NAME)

		@echo "$(CYAN)Minishell $(RED)deleted$(RESET)"
		@$(MAKE) -s -C readline clean --no-print-directory
		@echo "$(CYAN)Readline $(RED)deleted$(RESET)"

.PHONY: all re clean fclean 