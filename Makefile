NAME		= miniRT

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

INC_DIR		= .

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= $(shell find $(SRC_DIR) -name *.c -type f)
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC			= gcc
RM			= rm -f

CFLAGS		= -Wall -Wextra -I$(INC_DIR) -I$(LIBFT_DIR) -I/usr/local/include -Imlx_linux -g
LFLAGS		= -L/usr/local/lib -Lmlx_Linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -lz -g

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $^ -o $@ $(LFLAGS)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re:	fclean all

.PHONY:		all clean fclean re
