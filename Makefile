# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 20:32:19 by kafortin          #+#    #+#              #
#    Updated: 2023/04/26 18:18:11 by kafortin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = philo

FILES = ./srcs/philo.c \
		./srcs/exit_management.c \
		./srcs/utils.c \

OBJS = $(FILES:.c=.o)

RM = @rm -f

.SILENT: $(OBJS)

all: $(NAME)
		
$(NAME): $(OBJS)
		@echo "Compiling philo..."
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "Completed! 🤠"
		
clean:
		$(RM) $(OBJS)
		
fclean: 
		$(RM) $(OBJS)
		$(RM) $(NAME)

re: fclean all

add:
	git add $(FILES)
	git add *.h
	git add Makefile

commit:
	git commit -m "$m"

push:
	git push origin master

git: add commit push

.PHONY: all clean fclean re add commit push git