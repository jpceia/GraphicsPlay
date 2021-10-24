NAME			= miniRT
BONUS_NAME		= miniRT_bonus

LIBFT_DIR		= ./libft

INC_DIR			= headers

SRC_DIR			= src
OBJ_DIR			= obj

SRC_MAND_DIR	= $(SRC_DIR)/mandatory
SRC_SHARED_DIR	= $(SRC_DIR)/shared
SRC_BONUS_DIR	= $(SRC_DIR)/bonus
OBJ_MAND_DIR	= $(OBJ_DIR)/mandatory
OBJ_SHARED_DIR	= $(OBJ_DIR)/shared
OBJ_BONUS_DIR	= $(OBJ_DIR)/bonus


SRCS_MAND		= $(shell find $(SRC_MAND_DIR) $(SRC_SHARED_DIR) -name *.c -type f)
SRCS_BONUS		= $(shell find $(SRC_BONUS_DIR) $(SRC_SHARED_DIR) -name *.c -type f)
OBJS_MAND		= $(SRCS_MAND:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS		= $(SRCS_BONUS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC				= gcc
RM				= rm -f

OS				= $(shell uname)

ifeq ($(OS), Linux)
	MLX_INC_DIR	= /usr/local/include
	MLX_DIR		= /usr/local/lib
	FLAG_OS		= -D OS_Linux
	FLAGS_MLX	= -Lmlx_Linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lz
else
	MLX_INC_DIR	= ./minilibx_opengl_20191021
	MLX_DIR		= ./minilibx_opengl_20191021
	FLAGS_MLX	= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif
FLAGS_WARN		= -Wall -Wextra -Werror
FLAGS_INC		= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_INC_DIR)
FLAGS_DEBUG		= -g
FLAGS_OPT		= -O3
FLAGS_LIBFT		= -L$(LIBFT_DIR) -lft
CFLAGS			= $(FLAGS_WARN) $(FLAGS_INC) $(FLAGS_OPT) $(FLAG_OS)
LDFLAGS			= $(FLAGS_LIBFT) $(FLAGS_MLX) $(FLAGS_OPT) -lm

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)

$(NAME): $(OBJS_MAND)
ifneq ($(OS), Linux)
	$(MAKE) -C $(MLX_DIR)
endif
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BONUS_NAME): $(OBJS_BONUS)
ifneq ($(OS), Linux)
	$(MAKE) -C $(MLX_DIR)
endif
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

bonus:	$(BONUS_NAME)

all: $(NAME)

clean:
ifneq ($(OS), Linux)
	$(MAKE) -C $(MLX_DIR) clean
endif
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME) $(BONUS_NAME)

re:	fclean all

# Debugging functions

debug:		CFLAGS += $(FLAGS_DEBUG)
debug:		LDFLAGS += $(FLAGS_DEBUG)
debug:		re

.PHONY:		all bonus clean fclean re
