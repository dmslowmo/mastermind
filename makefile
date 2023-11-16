# Flags
CPP_FLAGS := -O0 -g -Wall -Wextra -pedantic -Werror -std=c++20

# Commands
RM := rm -rf
MKDIR_P := mkdir -p

# Paths
CURR_DIR := $(notdir $(shell pwd))
SRC_PATH = ./src/
OBJ_PATH = ./obj/

# Files to compile
SRC_FILES := $(wildcard $(SRC_PATH)*.cpp)
OBJ1 := $(SRC_FILES:%.cpp=%.o)
OBJ := $(patsubst $(SRC_PATH)%, $(OBJ_PATH)%, $(OBJ1))

# Target name
EXEC := $(CURR_DIR)


# Build .o first
$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	$(MKDIR_P) $(OBJ_PATH)
	$(CXX) $(CPP_FLAGS) -o $@ -c $<

# Build the executable
$(EXEC): $(OBJ)
	$(CXX) $(CPP_FLAGS) -o $@ $^

all: $(EXEC)

# Clean executable and object files
clean:
	$(RM) $(OBJ_PATH) $(EXEC)
