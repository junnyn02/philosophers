# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junguyen <junguyen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 19:07:46 by junguyen          #+#    #+#              #
#    Updated: 2025/02/17 17:11:26 by junguyen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC =	cc 

CFLAGS = -Wall -Werror -Wextra -g
# -fsanitize=thread

SRC_PATH = srcs/

OBJ_PATH = obj/

SRC =	main.c			\
		utils.c			\
		init_destroy.c	\
		thread.c		\
		activity.c
SRCS	= ${addprefix $(SRC_PATH), $(SRC)}

OBJ		= $(SRC:.c=.o)

OBJS	= ${addprefix $(OBJ_PATH), $(OBJ)}

INCLUDES = -I incs/

RM		= rm -rfd

RED			:= "\033[0;31m\033[1m"
GREEN		:= "\033[0;32m\033[1m"
BLUE		:= "\033[0;34m\033[1m"
YELLOW		:= "\033[1;33m\033[1m"
PURPLE		:= "\033[0;35m\033[1m"
CYAN		:= "\033[0;36m\033[1m"
WHITE		:= "\033[0;37m\033[1m"
NO_STYLE	:= "\033[0m"

all:		$(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(INCLUDES) -c  $< -o $@

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDES)
		@echo $(GREEN)$(NAME) compiled!$(NO_STYLE)


clean:	
		@$(RM) $(OBJ_PATH)
		@echo $(YELLOW)object clean! $(NO_STYLE)

fclean: clean
		@$(RM) $(NAME)
		@echo $(RED)$(NAME) deleted!$(NO_STYLE)

re: fclean all
		@echo $(PURPLE)$(NAME) reloaded!$(NO_STYLE)

.PHONY: all clean fclean re