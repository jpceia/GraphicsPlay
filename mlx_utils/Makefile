NAME		= mlx_utils.a

LIBFT_DIR	= ../libft

INC_DIR		= .

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= $(shell find $(SRC_DIR) -name *.c -type f)
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC			= gcc
RM			= rm -f

CFLAGS		= -Wall -Wextra -I$(INC_DIR) -I$(LIBFT_DIR) -I/usr/local/include -Imlx_linux -O3
LFLAGS		= -L$(LIBFT_DIR) -lft

all:		$(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) libft
	ar rc $@ $(OBJS)

libft:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
