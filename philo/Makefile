# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evdos-sa <evdos-sa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 17:31:00 by evdos-sa          #+#    #+#              #
#    Updated: 2023/09/18 19:49:46 by evdos-sa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread -pthread

SRC_DIR = src/
OBJ_DIR = objects/

SRC =	phil_action_eat \
		phil_actions \
		phil_check_routine \
		phil_forks_take_drop \
		phil_get_times \
		phil_get_utils \
		phil_init \
		phil_main \
		phil_threads \
		phil_utils

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC)))

OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling philo..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "Done!"
	
$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR) $(NAME)

fclean: clean
	@$(RM) $(NAME) 

re: fclean all

.PHONY: all clean fclean re