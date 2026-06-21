##################################################################################
# This file is under MIT License												 #
# https://mit-license.org/														 #
# 																				 #
# Copyright (c) 2024 Totema														 #
# https://github.com/TotemaM													 #
##################################################################################

CC := gcc
DBG = -g -Wall -Wextra -Werror
BLD_DIR := build

OUT := ft_ping

all: $(OUT)

##################################################################################
# 							DEFAULT ENVIRONMENT 								 #	
##################################################################################
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

##################################################################################
# 							ALTERNATIVE TARGETS									 #
##################################################################################

# Address and memory leak sanitizing
lsan: DBG += -fsanitize=leak,address,undefined
lsan: all

##################################################################################
#    							FAKE TARGETS     								 #
##################################################################################
.PHONY: fclean clean

clean:
	rm -rf $(BLD_DIR)

fclean: clean
	rm -rf $(OUT)
