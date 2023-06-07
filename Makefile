# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 20:32:19 by kafortin          #+#    #+#              #
#    Updated: 2023/06/07 18:16:02 by kafortin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread

NAME = philo

FILES = ./srcs/main.c \
		./srcs/data.c \
		./srcs/death.c \
		./srcs/free.c \
		./srcs/meals.c \
		./srcs/philos.c \
		./srcs/thread.c \
		./srcs/time.c \
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