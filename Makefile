NAME			= ray_tracer

INC_DIR			= headers

SRC_DIR			= src
OBJ_DIR			= obj


SRCS			= $(shell find $(SRC_DIR) -name *.cpp -type f)
OBJS			= $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CC				= clang++ -std=c++98
RM				= rm -f

OS				= $(shell uname)

ifeq ($(OS), Linux)
	FLAG_OS		= -DOS_Linux
endif
FLAGS_WARN		= -Wall -Wextra -Werror -pedantic-errors
FLAGS_INC		= -MD -I$(INC_DIR) -I$(LIBFT_DIR)
FLAGS_DEBUG		= -g
FLAGS_OPT		= -O3
FLAGS_LIBFT		= -L$(LIBFT_DIR) -lft
CFLAGS			= $(FLAGS_WARN) $(FLAGS_OPT) $(FLAGS_INC) $(FLAG_OS)
LDFLAGS			= $(FLAGS_WARN) $(FLAGS_OPT) -lm

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)

$(NAME): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

# Debugging functions

debug:		CFLAGS += $(FLAGS_DEBUG)
debug:		LDFLAGS += $(FLAGS_DEBUG)
debug:		all

.PHONY:		all clean fclean re debug
