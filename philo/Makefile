# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/12 19:08:23 by emajuri           #+#    #+#              #
#    Updated: 2023/03/13 13:32:40 by emajuri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = $(NAME).c argument_conversion.c check_and_atoi.c helpers.c routine.c \
	  start_simulation.c eat.c

OSRC = $(SRC:%.c=%.o)

WWW = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OSRC)
	cc $(WWW) $(OSRC) -o $(NAME)

clean:
	rm -f $(OSRC)

fclean: clean
	rm -f $(NAME)

%.o: %.c
	cc $(WWW) -c -o $@ $^

re: fclean all
