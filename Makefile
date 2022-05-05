NAME := main

SRC := main.cpp

OBJ_DIR := ./obj

OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

DEPS := $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.d))
CXXFLAGS := -g -Wall -Werror -Wextra -std=c++98 -MMD -MP
CXX := c++
RM := rm -rf

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CXX) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

-include $(DEPS)
