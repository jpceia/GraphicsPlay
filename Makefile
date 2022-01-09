NAME			= miniRT

LIBFT_DIR		= ./libft

INC_DIR			= headers

SRC_DIR			= src
OBJ_DIR			= obj


SRCS			= $(shell find $(SRC_DIR) -name *.c -type f)
OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC				= clang
RM				= rm -f

OS				= $(shell uname)

ifeq ($(OS), Linux)
	FLAG_OS		= -D OS_Linux
endif
FLAGS_WARN		= -Wall -Wextra -Werror
FLAGS_INC		= -MD -I$(INC_DIR) -I$(LIBFT_DIR)
FLAGS_DEBUG		= -g
FLAGS_OPT		= -O3
FLAGS_LIBFT		= -L$(LIBFT_DIR) -lft
CFLAGS			= $(FLAGS_WARN) $(FLAGS_INC) $(FLAGS_OPT) $(FLAG_OS)
LDFLAGS			= $(FLAGS_LIBFT) $(FLAGS_OPT) -lm

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $^ -o $@ $(LDFLAGS)

all: $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re:	fclean all

# Debugging functions

debug:		CFLAGS += $(FLAGS_DEBUG)
debug:		LDFLAGS += $(FLAGS_DEBUG)
debug:		all

.PHONY:		all clean fclean re debug
