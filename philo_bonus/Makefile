# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/12 19:07:49 by emajuri           #+#    #+#              #
#    Updated: 2023/03/12 19:07:51 by emajuri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BONUS_NAME = philo_bonus

BSRC = $(BONUS_NAME).c argument_conversion_bonus.c check_and_atoi_bonus.c \
	   helpers_bonus.c routine_bonus.c start_simulation_bonus.c

BOSRC = $(BSRC:%.c=%.o)

WWW = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(BOSRC)
	cc $(WWW) $(BOSRC) -o $(BONUS_NAME)

clean:
	rm -f $(BOSRC)

fclean: clean
	rm -f $(BONUS_NAME)

%.o: %.c
	cc $(WWW) -c -o $@ $^

re: fclean all
