NAME := Minishell

CC := cc
CFLAGS := -Wall -Wextra -g
CPPFLAGS = $(addprefix -I,$(INCLUDES))

LIB_DIRS = $(PATH_LIBFT)/bin

LIBFT := ./libs/libft/bin/libft.a
SRCS_LIBFT := ./libs/libft/build/
PATH_LIBFT := ./libs/libft/

INCLUDES := include libs/libft/include
PATH_MANDATORY := ./srcs/
SRCS_MANDATORY := \
	lexer.c \
	lexer_aux.c \
	lexer_utils.c \
	main.c \
	parser.c \
	parser_utils.c \
	segment.c \
	token.c 
SRCS_MANDATORY := $(addprefix $(PATH_MANDATORY),$(SRCS_MANDATORY))

OBJTS             := $(SRCS_MANDATORY:.c=.o)
OBJTS_LIBFT = $(shell $(MAKE) -s -C $(PATH_LIBFT) get_var)
OBJTS_LIBFT := $(subst ./build/,$(SRCS_LIBFT),$(OBJTS_LIBFT))

PATH_BIN := ./bin/
PATH_OBJT := ./build/
PATH_BUILD := build/

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

$(PATH_OBJT)%.o: $(PATH_MANDATORY)%.c
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
