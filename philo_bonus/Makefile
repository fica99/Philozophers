# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aashara- <aashara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/23 18:46:40 by aashara-          #+#    #+#              #
#    Updated: 2021/10/10 18:21:22 by aashara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------  PROJECT  ----------------------------------------------------- #
NAME	:=	 	philo_bonus

# ------------  DIRECTORIES  ------------------------------------------------- #
SRC_DIR	=		src
HDR_DIR	=		include
TMP_DIR =		tmp

# ------------  SOURCE FILES  ------------------------------------------------ #
PRE_FLS	=		philo_precomp.c\

SRC_FLS	=		$(PRE_FLS) \
				main.c \
				philo_utils.c \
				philo_init.c \
				philo_run.c \
				philo_time.c \
				philo_mutex.c

# ------------  FILEPATHS  --------------------------------------------------- #
SRCS	=		$(addprefix $(SRC_DIR)/, $(SRC_FLS))
OBJS	=		$(patsubst $(SRC_DIR)/%.c,$(TMP_DIR)/%.o, $(SRCS))
DEPS	=		$(OBJS:.o=.d)

# ------------  FLAGS  ------------------------------------------------------- #
CC		=		gcc
RM		=		rm -rf
CFLGS	=		-Wall -Werror -Wextra
DFLGS	=		-O2
EFLGS	=		
IFLGS	=		-I $(HDR_DIR)
DFLGS	=		-MMD -MP
LFLGS	=		-lpthread

# ------------  RULES  ------------------------------------------------------- #
.PHONY: all clean fclean re

all: $(NAME)

-include $(DEPS)
$(TMP_DIR)/%.o: $(SRC_DIR)/%.c | $(TMP_DIR)
	$(CC) $(DFLGS) $(EFLGS) $(CFLGS) $(DFLGS) -c -o $@ $< $(IFLGS)

$(TMP_DIR):
	mkdir -p $(TMP_DIR)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LFLGS)

clean:
	$(RM) $(TMP_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
