# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdeguing <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/15 12:59:18 by pdeguing          #+#    #+#              #
#    Updated: 2018/09/21 13:58:41 by pdeguing         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
CFLAGS = -Wall -Wextra -Werror
SRC = *.c \
	  utils/get_grp.c \
	  utils/get_name.c \
	  utils/get_link.c \
	  utils/get_user.c \
	  utils/get_stat.c \
	  utils/execution_mode.c
LIB = -lft -L./libft/
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) 
	gcc -o $(NAME) $(CFLAGS) $(SRC) $(LIB)

$(LIBFT):
	cd libft/ && make

cmp:
	gcc -o $(NAME) $(CFLAGS) $(SRC) $(LIB)

clean:
	/bin/rm -f *.o
	cd libft/ && make clean

fclean: clean
	/bin/rm -f $(NAME)
	cd libft/ && make fclean

re: fclean all

.PHONY: clean fclean all re
