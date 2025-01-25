NAME	=	ft_ls
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
OBJ_DIR	=	obj/
SRC_DIR	=	src/
SRCS	=	src/ft_ls.c
OBJS	=	$(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
GREY	=	\33[1;30m
BLUE	=	\33[0;34m
DEFAULT	=	\33[0m

all: $(NAME)

$(SRC_DIR)libft/libft.a:
	@make -C $(SRC_DIR)libft

$(NAME): $(OBJS) $(SRC_DIR)libft/libft.a
	@printf "$(GREY)Compiling $(BLUE)$(NAME)$(DEFAULT)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(SRC_DIR)libft/libft.a -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@printf "$(GREY)Compiling $(BLUE)$< $(GREY)> $(BLUE)$@$(DEFAULT)\n"
	@$(CC) $(CFLAGS) -c $< -o $@ 


clean:
	@printf "$(GREY)Deleting $(BLUE)$(OBJ_DIR)$(DEFAULT)\n"
	@rm -fr $(OBJ_DIR)
	@make clean -C $(SRC_DIR)libft

fclean: clean
	@printf "$(GREY)Deleting $(BLUE)$(NAME)$(DEFAULT)\n"
	@rm -f $(NAME)
	@make fclean -C $(SRC_DIR)libft

re: fclean all