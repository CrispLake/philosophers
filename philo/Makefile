# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emajuri <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 16:39:22 by emajuri           #+#    #+#              #
#    Updated: 2023/03/06 14:12:02 by emajuri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = $(NAME).c argument_conversion.c check_and_atoi.c fork_functions.c \
	  helpers.c routine.c

OSRC = $(SRC:%.c=%.o)

WWW = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OSRC)
	cc $(WWW) $(OSRC) -o $(NAME)

clean:
	rm -f $(OSRC) $(BOSRC)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

%.o: %.c
	cc $(WWW) -c -o $@ $^ 

re: fclean all
