NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

GREEN = \033[0;32m
BLUE = \033[0;34m
PURPLE = \033[0;35m
COLOUR_END = \033[0m

OBJ_DIR = ./obj
SRC_DIR = ./src
LIBFT_DIR = ./libft
LIBFT	:= libft/libft.a
MAKEFLAGS += -s

BUILDTINS = ./src/buildtins/ft_cd_2.c ./src/buildtins/ft_cd.c ./src/buildtins/ft_echo.c \
	./src/buildtins/ft_env.c ./src/buildtins/ft_exit.c ./src/buildtins/ft_export.c \
	./src/buildtins/ft_pwd.c ./src/buildtins/ft_unset.c

ENV = ./src/env/ft_env_list.c
HANDLE_FILE = ./src/handle_file/ft_handle_fd.c
PARSER = ./src/parser/ft_process_utility.c ./src/parser/ft_process.c
SIGNAL = ./src/signal/ft_signal_handle.c
TOKENIZER = ./src/tokenizer/ft_tokenizer_counter.c ./src/tokenizer/ft_tokenizer_utility.c \
	./src/tokenizer/ft_tokenizer.c
GNL = ./gnl/get_next_line_utils.c ./gnl/get_next_line.c
MAIN = ./src/main.c ./src/ft_utility.c ./src/ft_pipe.c ./src/ft_pipe_2.c

SRC = $(BUILDTINS) $(ENV) $(HANDLE_FILE) $(PARSER) $(SIGNAL) $(TOKENIZER) $(GNL) $(MAIN)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@echo "$(PURPLE)EVERYTHING COMPILED!$(COLOUR_END)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@mkdir -p ./obj/libft
	@mkdir -p ./obj/gnl
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)EVERYTHING CLEANED!$(COLOUR_END)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "$(BLUE)EVERYTHING CLEANED COMPLETELY!$(COLOUR_END)"

re: fclean all

git:
	make fclean
	git add .
	git commit -m "update"
	git push

.PHONY: all clean fclean re
