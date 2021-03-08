CC=g++
CC_FLAGS=-W -Wall -pedantic -std=c++11
INC_DIR=./include

MAIN_SRC=main.cpp             \
				 ./src/Cidade.cpp     \
				 ./src/Quadtree.cpp   \
				 ./src/string_tok.cpp 

MAIN_HPP=$(INC_DIR)/Cidade.hpp   \
				 $(INC_DIR)/Quadtree.hpp \
				 $(INC_DIR)/utils.hpp

build: main

main: main.cpp $(MAIN_SRC) $(MAIN_HPP)
	$(CC) $(CC_FLAGS) -o $@ $(MAIN_SRC) -I $(INC_DIR)
