CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -I/usr/include

NAME = philo

SRCDIR = source/
SRC = source/main.c parsing.c utils.c death_thread.c free.c init.c \
		routine.c routine_utils.c 

ALL_SRC = $(SRC)

OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(ALL_SRC:.c=.o)))

all: $(NAME)

$(NAME):$(OBJECTS)
	@echo "Compiling Philo..."
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo ""
	@echo "\033[1mUsage:\033[0m"
	@echo " ./program (NP) (TD) (TE) (TS) [LE]"
	@echo "   -(Number of philosophers)"
	@echo "   -(Time to die)"
	@echo "   -(Time to eat)"
	@echo "   -(Time to sleep)"
	@echo "   -[Limit a philosopher must eat] (Optional)"
	@echo "\033[1mAll time values must be in milliseconds.\033[0m"

$(OBJ_DIR)/%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
