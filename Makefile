# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdanylev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/18 17:07:17 by hdanylev          #+#    #+#              #
#    Updated: 2018/06/20 22:19:07 by hdanylev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = avm
SRC =	main.cpp \
		Number.class.cpp \
		VM.class.cpp \
		Factory.class.cpp \
		VM.operations.class.cpp 

OBJ = $(SRC:.cpp=.o)
HDRS = VM.class.hpp Factory.class.hpp Number.class.hpp IOperand.hpp
CLANG++ = clang++
CL_FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ) $(HDRS)
	@$(CLANG++) -c $(SRC)
	@$(CLANG++) $(CL_FLAGS) $(OBJ) -o $(NAME)
	@echo "\033[31mAbstractVM \033[35mMAKED\033[0m"

clean:
	@rm -f $(OBJ)
	@echo "\033[35mCLEANED\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[35mCLEANED ALL\033[0m"

re: fclean all

.PHONY: all clean fclean re
