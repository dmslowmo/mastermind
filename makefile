CC = g++
CPPFLAGS = -I"include" -O0 -g -Wall -Wextra -pedantic -Werror -std=c++11
RM = rm -rf
CURR_DIR := $(notdir $(shell pwd))
EXEC := $(CURR_DIR)
SRC = src
SRC_FILES := $(wildcard $(SRC)/*.cpp)
O_FILES := $(SRC_FILES:%.cpp=%.o)

all : $(O_FILES)
	$(CC) $(CPPFLAGS) -o $(EXEC) $(O_FILES)

clean:
	$(RM) $(O_FILES) $(EXEC)
