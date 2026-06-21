# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/21 16:18:39 by mmichele          #+#    #+#              #
#    Updated: 2026/06/21 16:18:53 by mmichele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc
DBG = -g -Wall -Wextra -Werror
BLD_DIR := build

OUT := ft_ping

all: $(OUT)

SRC_DIR := src
SRC := $(shell find $(SRC_DIR) -type f -name *.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(BLD_DIR)/%.o, $(SRC))
INC := -I $(SRC_DIR)
LIB :=
DEP := $(OBJ:.o=.d)

$(OUT): $(OBJ)
	$(CC) $(DBG) $^ -o $(OUT) $(LIB) $(INC)

$(BLD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(DBG) -MMD -MP -c $< -o $@ $(INC)

-include $(DEP)

lsan: DBG += -fsanitize=leak,address,undefined
lsan: all

.PHONY: fclean clean

clean:
	rm -rf $(BLD_DIR)

fclean: clean
	rm -rf $(OUT)
