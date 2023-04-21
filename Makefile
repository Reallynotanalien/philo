# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kafortin <kafortin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 20:32:19 by kafortin          #+#    #+#              #
#    Updated: 2023/04/21 18:21:56 by kafortin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

NAME = philo

MAKE_LIBFT = cd ./Libft/ && make

FILES = ./srcs/philosophers.c

OBJS = $(FILES:.c=.o)

RM = @rm -f

.SILENT: $(OBJS)

all: $(NAME)
		
$(NAME): $(OBJS)
		@$(MAKE_LIBFT)
		@echo "Compiling so_long..."
		@$(CC) $(CFLAGS) $(OBJS) ./Libft/libft.a $(NAME)
		@echo "Completed! 🤠"
		
clean:
		@$(MAKE) clean -C ./Libft
		$(RM) $(OBJS)
		
fclean: 
		@$(MAKE) fclean -C ./Libft
		@$(MAKE) clean -C ./Minilibx
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