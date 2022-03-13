# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snuts <snuts@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/29 20:43:05 by snuts             #+#    #+#              #
#    Updated: 2021/12/29 20:46:01 by snuts            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snuts <snuts@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 20:08:43 by snuts             #+#    #+#              #
#    Updated: 2021/12/05 20:51:35 by snuts            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

NAME_B = philo_bonus

SRCS	=	./mandatory/main.c		./mandatory/ft_atoi.c		./mandatory/ft_init.c\
			./mandatory/death_checker.c


SRCS_B	=	./bonus/main.c		./bonus/ft_atoi.c		./bonus/ft_init.c\
			./bonus/death_checker.c

OBJS = $(SRCS:.c=.o)

OBJS_B = $(SRCS_B:.c=.o)

HEADER	=	mandatory/philo.h

HEADER_B	=	bonus/philo.h

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(SRCS) $(MLXFLAGS) $(CFLAGS) -o $(NAME)

$(NAME_B):	$(OBJS_B)
			$(CC) $(SRCS_B) $(MLXFLAGS) $(CFLAGS) -o $(NAME_B)

%o:			%.c
			$(CC) $(CFLAGS) -c $< -o $@

bonus:		$(NAME_B)

clean:
			$(RM) $(OBJS) $(OBJS_B)

fclean:		clean
			$(RM) $(NAME) $(NAME_B)

re:			fclean all

.PHONY:		all clean fclean re