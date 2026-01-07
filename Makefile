NAME := Minishell

CC := cc
CFLAGS := -g -Wall -Wextra # -Werror
CPPFLAGS = $(addprefix -I,$(INCLUDES))

LIB_DIRS = $(PATH_LIBFT)/bin

LIBFT := ./libs/libft/bin/libft.a
SRCS_LIBFT := ./libs/libft/build/

PATH_LIBFT := ./libs/libft/
PATH_BIN := ./bin/
PATH_OBJT := ./build/
PATH_BUILD := build/


INCLUDES := include libs/libft/include
PATH_MANDATORY := ./srcs
EXEC_SRC_DIR   := exec
PARSER_SRC_DIR := parser

SRCS_MANDATORY_COMMON := \
	main.c \
	error.c

SRCS_MANDATORY_EXEC := \
	ft_main_loop.c \
	ft_export.c \
	ft_env.c \
	ft_unset.c \
	ft_hashadd_back.c \
	ft_hashnew.c \
	var_exp.c \
	print_export.c \
	env_utils.c \
	hashpop.c \
	heredoc.c \
	hash_table.c
SRCS_MANDATORY_PARSER := \
	ast.c \
	ast_aux.c \
	expand.c \
	expand_aux.c \
	expand_split_join.c \
	expand_utils.c \
	lexer.c \
	lexer_handle_word.c \
	lexer_utils.c \
	log_tree.c \
	parser.c \
	parser_utils.c \
	segment.c \
	token.c

SRCS_MANDATORY := $(addprefix $(PATH_MANDATORY)/,$(SRCS_MANDATORY_COMMON))
SRCS_MANDATORY := $(SRCS_MANDATORY) $(addprefix $(PATH_MANDATORY)/$(EXEC_SRC_DIR)/,$(SRCS_MANDATORY_EXEC))
SRCS_MANDATORY := $(SRCS_MANDATORY) $(addprefix $(PATH_MANDATORY)/$(PARSER_SRC_DIR)/,$(SRCS_MANDATORY_PARSER))

OBJTS := $(addprefix $(PATH_OBJT),$(SRCS_MANDATORY_COMMON))
OBJTS := $(OBJTS) $(addprefix $(PATH_OBJT),$(SRCS_MANDATORY_EXEC))
OBJTS := $(OBJTS) $(addprefix $(PATH_OBJT),$(SRCS_MANDATORY_PARSER))

OBJTS             := $(OBJTS:.c=.o)
OBJTS_LIBFT = $(shell $(MAKE) -s -C $(PATH_LIBFT) get_var)
OBJTS_LIBFT := $(subst ./build/,$(SRCS_LIBFT),$(OBJTS_LIBFT))

LDLIBS := -lft -lreadline
LDFLAGS := $(addprefix -L, $(LIB_DIRS))


# Cores ANSI
GREEN   = \033[0;32m
RED     = \033[0;31m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
MAGENTA = \033[0;35m
CYAN    = \033[0;36m
L_GREEN = \033[1;32m
L_RED   = \033[1;31m
GRAY    = \033[0;90m
NC      = \033[0m

all: $(addprefix $(PATH_BIN),$(NAME))

# $(NAME)
$(addprefix $(PATH_BIN),$(NAME)): $(LIBFT) $(subst $(PATH_MANDATORY),$(PATH_OBJT),$(OBJTS))
		@echo "$(YELLOW)+==========================================+"
		@echo "          Build $(NAME)          "
		@echo "+==========================================+$(NC)"

		@mkdir -p bin
		@printf "$(L_GREEN)Build...$(NC) %-40s\n" $(NAME)
		@sleep 0.01
		@$(CC) $(CFLAGS) $(CPPFLAGS) $(subst $(PATH_MANDATORY),$(PATH_OBJT),$(OBJTS)) -o $(addprefix $(PATH_BIN),$(NAME)) $(LDLIBS) $(LDFLAGS)


$(LIBFT): $(OBJTS_LIBFT)
		@echo "$(MAGENTA)+==========================================+"
		@echo "         Github: Breno-S | Norethx        "
		@echo "+==========================================+\n\n$(NC)"
		@echo "$(GREEN)	⢀⡴⠑⡄⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠸⡇⠀⠿⡀⠀⠀⠀⣀⡴⢿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠑⢄⣠⠾⠁⣀⣄⡈⠙⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⢀⡀⠁⠀⠀⠈⠙⠛⠂⠈⣿⣿⣿⣿⣿⠿⡿⢿⣆⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⢀⡾⣁⣀⠀⠴⠂⠙⣗⡀⠀⢻⣿⣿⠭⢤⣴⣦⣤⣹⠀⠀⠀⢀⢴⣶⣆"
		@echo "	⠀⠀⢀⣾⣿⣿⣿⣷⣮⣽⣾⣿⣥⣴⣿⣿⡿⢂⠔⢚⡿⢿⣿⣦⣴⣾⠁⠸⣼⡿"
		@echo "	⠀⢀⡞⠁⠙⠻⠿⠟⠉⠀⠛⢹⣿⣿⣿⣿⣿⣌⢤⣼⣿⣾⣿⡟⠉⠀⠀⠀⠀⠀"
		@echo "	⠀⣾⣷⣶⠇⠀⠀⣤⣄⣀⡀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠉⠈⠉⠀⠀⢦⡈⢻⣿⣿⣿⣶⣶⣶⣶⣤⣽⡹⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⠀⠉⠲⣽⡻⢿⣿⣿⣿⣿⣿⣿⣷⣜⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣶⣮⣭⣽⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⣀⣀⣈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀"
		@echo "	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⠿⠿⠿⠿⠛⠉\n\n$(NC)"
		@echo "$(RED)+==========================================+"
		@echo "      Welcome to $(NAME) - Build libft       "
		@echo "+==========================================+$(NC)"
		@echo "Compilando código...\n"
		@make -C $(PATH_LIBFT) NAME="libft.a" all

$(PATH_OBJT)%.o: $(PATH_MANDATORY)/$(EXEC_SRC_DIR)/%.c
		@mkdir -p build
		@printf "$(L_GREEN)Compiling...$(NC) %-40s\n" $<
		@sleep 0.01
		@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $(subst srcs/,build/,$@)

$(PATH_OBJT)%.o: $(PATH_MANDATORY)/$(PARSER_SRC_DIR)/%.c
		@mkdir -p build
		@printf "$(L_GREEN)Compiling...$(NC) %-40s\n" $<
		@sleep 0.01
		@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $(subst srcs/,build/,$@)

$(PATH_OBJT)%.o: $(PATH_MANDATORY)/%.c
		@mkdir -p build
		@printf "$(L_GREEN)Compiling...$(NC) %-40s\n" $<
		@sleep 0.01
		@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $(subst srcs/,build/,$@)

.PHONY: clean fclean re all bonus $(OBJTS_LIBFT)

clean:
		@make -C $(PATH_LIBFT) clean
		rm -f $(subst $(PATH_MANDATORY),$(PATH_OBJT),$(OBJTS))

fclean:
		@make -C $(PATH_LIBFT) fclean
		rm -f $(subst $(PATH_MANDATORY),$(PATH_OBJT),$(OBJTS))
		rm -f $(addprefix $(PATH_BIN),$(NAME))

re: fclean all

teste:
	@echo $(SRCS_MANDATORY)
	@echo
	@echo $(OBJTS)
