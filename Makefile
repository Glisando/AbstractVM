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

    # name of the executable file

NAME = avm

	# project directories

SRC_DIR =	./src/
OBJ_DIR =	./obj/
INC_DIR =	./inc/

	# project source files

SRC =	main.cpp \
		Number.class.cpp \
		VM.class.cpp \
		Factory.class.cpp \
		VM.operations.class.cpp \
		Exception.class.cpp

	# project object files

OBJ =		$(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

	# project header files

HDRS = VM.class.hpp Factory.class.hpp Number.class.hpp IOperand.hpp Exception.class.hpp

	# compilation flags

CL_FLAGS	=	-Wall -Wextra -Werror

	# header flags

HEADER_FLAGS = -I $(INC_DIR)

	# compiler

CLANG++ = clang++

all: $(NAME)

$(NAME): $(OBJ)
	$(CLANG++) $(CL_FLAGS) $(OBJ) -o $(NAME)
	@echo "\033[31mAbstractVM \033[35mMAKED\033[0m"

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
		mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: %.cpp $(INC_DIR)
		$(CLANG++) $(CL_FLAGS) $(HEADER_FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[35mCLEANED\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@echo "\033[35mCLEANED ALL\033[0m"

re: fclean all

vpath %.cpp $(SRC_DIR)
.PHONY: all clean fclean re
