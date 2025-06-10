CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCDIR = ../philo
OBJDIR = obj
TARGET = philo

SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCFILES))

.PHONY: all clean fclean re

all: $(TARGET)

$(TARGET): $(OBJFILES)
	@echo "SRCFILES: $(SRCFILES)"
	@echo "OBJFILES: $(OBJFILES)"
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@echo "Compiling $< to $@"
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(TARGET)

re: fclean all
