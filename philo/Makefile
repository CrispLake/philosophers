# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emajuri <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 16:39:22 by emajuri           #+#    #+#              #
#    Updated: 2023/03/08 23:59:43 by emajuri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = $(NAME).c argument_conversion.c check_and_atoi.c helpers.c routine.c \
	  create.c eat.c

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
