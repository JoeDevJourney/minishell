#
#
CC = cc
CFLAGS = -g -Wall -Werror -Wextra -I$(LIBFTDIR)/include -I$(INCDIR)
MAKEFLAGS += -s

SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./include
LIBFTDIR = ./include/libft

SRCS = $(SRCDIR)/main.c $(SRCDIR)/pipex.c \
		$(SRCDIR)/commands.c $(SRCDIR)/redirection.c \
		$(SRCDIR)/builtins/env.c $(SRCDIR)/builtins/builtins.c $(SRCDIR)/builtins/pwd.c \
		$(SRCDIR)/utils/functions.c $(SRCDIR)/utils/more_functions.c $(SRCDIR)/utils/even_more_functions.c


OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
# OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
LIBFT = $(LIBFTDIR)/libft.a
NAME = minishell

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS) $(LIBFT)
	@echo "\033[33mCompilating $(NAME)...\033[0m"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFTDIR) -lft -lreadline
	@echo "$(NAME) compiled \033[32msuccessfully\033[0m!"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/builtins/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/utils/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	@echo "\033[33mRemoving project build and library build...\033[0m"
	rm -f $(OBJDIR)/*.o
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean
	@echo "All build files removed \033[32msuccessfully\033[0m!"

fclean: clean
	@echo "\033[33mRemoving executable and static libraries...\033[0m"
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean
	@echo "Executable and static libraries removed \033[32msuccessfully\033[0m!"
	
re: fclean all

.PHONY: all clean fclean re
