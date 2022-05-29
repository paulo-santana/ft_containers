NAME ?= main
NAME_STD := main_std

SRC := main.cpp \
	   vector.test.cpp \
	   vector_iterator.test.cpp \
	   reverse_iterator.test.cpp \
	   stack.test.cpp \
	   pair.test.cpp \
	   rb_tree.test.cpp \
	   map.test.cpp \
	   test_utils.cpp \

OBJ_DIR ?= ./obj
vpath %.cpp \
	src \
	src/vector \
	src/internals \
	tests \

OBJ  := $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

DEPS := $(OBJ:.o=.d)
INCLUDE := -I ./src/
USE_STD ?= 0
CXXFLAGS := -DREAL_STD=$(USE_STD) -g -Wall -Werror -Wextra -std=c++98 -MMD -MP $(INCLUDE)
CXX := c++
RM := rm -rf


all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CXX) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(OBJ_DIR)2
	$(RM) my_out std_out

fclean: clean
	$(RM) $(NAME) $(NAME_STD)

re: fclean all


run: __compile_ft __compile_std
	./$(NAME_STD) > std_out
	./$(NAME) > my_out
	delta --diff-so-fancy my_out std_out && echo "OK :)"

test:
	c++ -I./src teste.cpp -o test_bin && ./test_bin && rm ./test_bin

__compile_ft:
	make

__compile_std:
	make USE_STD=1 NAME=main_std OBJ_DIR=./obj2

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

-include $(DEPS)
