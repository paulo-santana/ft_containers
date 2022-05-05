NAME := test_bin

SRC := main.cpp \

OBJ_DIR := ./obj
vpath %.cpp \
	src			\

OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

DEPS := $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.d))
CXXFLAGS := -Wall -Wextra -MMD -MP
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
