NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = ./src/main.c
SRC_DIRS = ./src
OBJS = ${SRCS:.c=.o}

PRINTF		:= ft_printf/libftprintf.a
LIBFT		:= libft/libft.a

GREEN		=\033[0;32m
RED			=\033[0;31m
BLUE		=\033[0;34m
COLOUR_END	=\033[0m

OBJ_DIR = ./obj
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,${SRCS})

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@mkdir -p ./obj/libft
	@mkdir -p ./obj/ft_printf
	@$(CC) -g -c $< -o $@;

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C ft_printf/
	@$(MAKE) -C ./libft/
	@$(CC) $(CFLAGS) $(OBJS) $(PRINTF) $(LIBFT) -o $(NAME)
	@echo "$(RED)EVERYTHING COMPILE!$(COLOUR_END)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -sC ft_printf/
	@make clean -sC libft/
	@rm -rf $(OBJS)
	@${RM} -r ${OBJ_DIR}
	@echo "$(GREEN)EVERYTHING HAS CLEAN!$(COLOUR_END)"

fclean: clean
	@rm -f $(NAME)
	@$(RM) -f $(PRINTF)
	@$(RM) -f $(LIBFT)
	@echo "$(BLUE)EVERYTHING HAS FCLEAN!$(COLOUR_END)"

re: fclean all
	@$(MAKE)

git:
	git add *
	git commit -m "update"
	git push

.PHONY: all clean fclean re
