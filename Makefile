#
#
CC = cc
CFLAGS = -g -Wall -Werror -Wextra -I$(INCDIR) -I$(LIBFTDIR)/include -I$(GNLDIR)
MAKEFLAGS += -s

SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./include
LIBFTDIR = ./include/libft
GNLDIR = ./include/getnextline

SRCS = $(SRCDIR)/main.c $(SRCDIR)/pipex.c $(SRCDIR)/expansion.c $(SRCDIR)/execution.c $(SRCDIR)/process_hdoc.c \
		$(SRCDIR)/parse_command.c $(SRCDIR)/process_redir.c $(SRCDIR)/parse_logic.c $(SRCDIR)/parse_redir.c \
		$(SRCDIR)/signal.c \
		\
		$(SRCDIR)/builtins/env.c $(SRCDIR)/builtins/builtins.c $(SRCDIR)/builtins/pwd.c $(SRCDIR)/builtins/exit.c \
		$(SRCDIR)/builtins/echo.c $(SRCDIR)/builtins/cd.c $(SRCDIR)/builtins/unset.c $(SRCDIR)/builtins/export.c \
		$(SRCDIR)/builtins/minishell.c \
		\
		$(SRCDIR)/utils/functions.c $(SRCDIR)/utils/more_functions.c $(SRCDIR)/utils/even_more_functions.c \
		$(SRCDIR)/utils/guess_what_more_functions.c $(SRCDIR)/utils/dir_utils.c \
		\
		$(GNLDIR)/get_next_line.c $(GNLDIR)/get_next_line_utils.c

OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
LIBFT = $(LIBFTDIR)/libft.a
NAME = minishell

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS) $(LIBFT)
	@echo "\033[33mCompilating $(NAME)...\033[0m"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFTDIR) -lft -lreadline
	@echo "$(NAME) compiled \033[32msuccessfully\033[0m!"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(GNLDIR)/%.c | $(OBJDIR)
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
