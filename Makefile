# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/18 13:57:10 by jbrandt           #+#    #+#              #
#    Updated: 2025/01/18 16:56:57 by jbrandt          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./include
FLAGS = -O3 -g3 -L -lft

LIBFT = ./libft
LIBS = /include

RM = rm -f
FILES = 

OBJ_DIR = build

OBJS = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I.$(LIBS) -c $< -o $@

$(NAME): $(OBJS)
	make -C $(LIBFT)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT)/libft.a $(FLAGS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	make clean -C $(LIBFT)
	$(RM) $(OBJ_DIR)/*.o

fclean: clean
	make fclean -C $(LIBFT)
	$(RM) $(NAME)

re: fclean all

# dude stop traumatizing a 6-yo boy..
# never, i shall torment him