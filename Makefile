# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/18 16:06:01 by gtertysh          #+#    #+#              #
#    Updated: 2019/01/19 15:21:01 by gtertysh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif


# name of the main target

NAME :=							libft_malloc_$(HOSTTYPE).so


# project directories

ROOT :=							$(shell pwd)
SRC_DIR :=						$(ROOT)/src/
OBJ_DIR :=						$(ROOT)/obj/
INC_DIR :=						$(ROOT)/inc/
LIB_DIR :=						$(ROOT)/lib/
TST_DIR :=						$(ROOT)/t/


# project headers

MLC_HEADER :=					$(INC_DIR)/ft_malloc.h
TST_HEADER :=					$(INC_DIR)/tests.h
TST_RUNNER_HEADER :=			$(INC_DIR)/t.h
HEADERS :=						$(MLC_HEADER)								\
								$(TST_HEADER)								\
								$(TST_RUNNER_HEADER)


# libraries

LIBFT_DIR :=					$(LIB_DIR)libft/
LIBFT_INC :=					-I $(LIBFT_DIR)includes/
LIBFT_LIB :=					-lft -L $(LIBFT_DIR)
LIBFT =							$(LIBFT_DIR)libft.a


# project source files

MALLOC_SRC =					malloc.c

SRC :=							$(MALLOC_SRC)


# project object files

OBJ =							$(addprefix $(OBJ_DIR), $(SRC:.c=.o))


# project test files

TEST_BIN =						malloc_test

MALLOC_TESTS =					malloc_tests.c
MALLOC_TESTS +=					$(MALLOC_SRC)

TEST_SRC =						tests.c										\
								$(MALLOC_TESTS)

TEST_OBJ =						$(addprefix $(OBJ_DIR), $(TEST_SRC:.c=.o))


# compilation flags

CC_FLAGS =						-Wall -Wextra -Werror

CC_FLAGS +=						-Wpointer-arith
CC_FLAGS +=						-Wcast-align
CC_FLAGS +=						-Wwrite-strings
CC_FLAGS +=						-Wunreachable-code
CC_FLAGS +=						-Winit-self
CC_FLAGS +=						-Wmissing-field-initializers
CC_FLAGS +=						-Wno-unknown-pragmas
CC_FLAGS +=						-Wstrict-prototypes
CC_FLAGS +=						-Wundef
CC_FLAGS +=						-Wold-style-definition


# for debug

ifeq ($(DEBUG),true)

CC_FLAGS +=						-g
CC_FLAGS +=						-O0

endif


# linking flags

LINK_FLAGS =					$(LIBFT_LIB)


# header flags

HEADER_FLAGS =					-I $(INC_DIR)								\
								$(LIBFT_INC)


# compiler

CC :=							clang


# rules

$(NAME): $(OBJ)
	$(CC) -shared -fpic $(OBJ) -o $(NAME) $(LINK_FLAGS)

$(TEST_BIN): $(TEST_OBJ)
	$(CC) $(TEST_OBJ) $(LINK_FLAGS) -o $(TEST_BIN)

$(TEST_OBJ) $(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c $(LIBFT) $(HEADERS)
	$(CC) -c $< -o $@ $(CC_FLAGS) $(HEADER_FLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

all: $(NAME)

check: $(TEST_BIN)
	clear
	./$(TEST_BIN)

clean:
	rm -f $(OBJ)
	rm -f $(TEST_OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_BIN)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

multi:
	$(MAKE) $(LIBFT)
	$(MAKE) $(NAME)


# special stuff

vpath %.c						$(SRC_DIR)									\
								$(TST_DIR)

.PHONY: all check clean fclean re multi