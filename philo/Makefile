# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apodader <apodader@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/14 14:25:36 by apodader          #+#    #+#              #
#    Updated: 2024/09/06 21:19:31 by apodader         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
RM = rm -rf
FLAGS = -Wall -Wextra -Werror -Iincludes -MMD
SRC = args_checker init philosophers routine threads
INC = philosophers
DIR_SRC = ./src/
INCDIR = ./includes/
DIR_OBJ_DST = ./obj/

SRCS := $(addprefix $(DIR_SRC), $(addsuffix .c, $(SRC)))
OBJS := $(patsubst $(DIR_SRC)%.c, $(DIR_OBJ_DST)/%.o, $(SRCS))
DEPS := $(patsubst $(DIR_SRC)%.c, $(DIR_OBJ_DST)/%.d, $(SRCS))
INCLUDE := $(addprefix $(INCDIR), $(addsuffix .h, $(INC)))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(DIR_OBJ_DST)/%.o: $(DIR_SRC)/%.c $(INCLUDE)
	@mkdir -p $(DIR_OBJ_DST)
	$(CC) $(FLAGS) -c $< -o $@

-include $(DEPS)

clean:
	$(RM) $(DIR_OBJ_DST)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
