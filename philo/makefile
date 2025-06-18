CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCDIR = .
OBJDIR = obj
NAME = philo

# List all source files explicitly
SRC = backdoor.c forks.c get.c init.c input.c main.c mood_swings.c \
      routines.c set.c threads.c time.c update.c utils.c

# Generate object file names
OBJFILES = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJFILES)
	@echo "SRCFILES: $(SRCFILES)"
	@echo "OBJFILES: $(OBJFILES)"
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@echo "Compiling $< to $@"
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

helgrind:
	@valgrind --quiet -v --tool=helgrind ./$(NAME) $(ARGS)
sanitize: SANITIZE = -fsanitize=thread
sanitize: re

valgrind:
	@valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=memcheck ./$(NAME) $(ARGS)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
