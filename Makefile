# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 19:07:46 by junguyen          #+#    #+#              #
#    Updated: 2024/10/08 19:37:18 by junguyen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC =	cc 

CFLAGS = -Wall -Werror -Wextra -g

SRC_PATH = srcs/

SRC =	main.c utils.c \
			
SRCS = $(addprefix $(SRC_PATH), $(SRC))

OBJ = $(SRCS:.c=.o)

.c.o:
		@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
		@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
		@echo "philo created"

all: $(NAME)

clean:
		@rm -f $(OBJ)
		@echo "objects cleaned"

fclean: clean
		@rm -f $(NAME)
		@echo "all clean"
	
re: fclean all

.PHONY: all clean fclean re