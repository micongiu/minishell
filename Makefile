NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ./src/main.c ./src/ft_utility.c ./src/ft_env.c ./src/ft_tokenizer.c ./src/ft_tokenizer_utility.c ./src/ft_signal_handle.c
SRC_DIRS = ./src
OBJS = ${SRCS:.c=.o}

LIBFT		:= libft/libft.a

GREEN		=\033[0;32m
PURPLE			=\033[0;31m
BLUE		=\033[0;34m
PURPLE = \033[0;35m

MAKEFLAGS += -s

OBJ_DIR = ./obj
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,${SRCS})

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@mkdir -p ./obj/libft
	@$(CC) -g -c $< -o $@;

all: $(NAME) clean

$(NAME): $(OBJS)
	@$(MAKE) -C ./libft/
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@echo "$(PURPLE)EVERYTHING COMPILE!$(COLOUR_END)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -sC libft/
	@rm -rf $(OBJS)
	@${RM} -r ${OBJ_DIR}
	@echo "$(GREEN)EVERYTHING HAS CLEAN!$(COLOUR_END)"

fclean: clean
	@rm -f $(NAME)
	@$(RM) -f $(LIBFT)
	@echo "$(BLUE)EVERYTHING HAS FCLEAN!$(COLOUR_END)"

re: fclean all clean
	@$(MAKE)

git:
	make fclean
	git add *
	git commit -m "update"
	git push

.PHONY: all clean fclean re
