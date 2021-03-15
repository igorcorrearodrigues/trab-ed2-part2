CC=g++
CC_FLAGS=-W -Wall -pedantic -std=c++11
INC_DIR=./include
SRC_DIR=./src

CPP_SOURCE=$(wildcard $(SRC_DIR)/*.cpp)

HPP_SOURCE=$(wildcard $(INC_DIR)/*.hpp)

MAIN_SRC=main.cpp $(CPP_SOURCE)
MAIN_HPP=$(HPP_SOURCE)

MODULO_SRC=modulo_de_teste.cpp $(CPP_SOURCE)
MODULO_HPP=$(HPP_SOURCE)


build: main

main: $(MAIN_SRC) $(MAIN_HPP)
	$(CC) $(CC_FLAGS) -o $@ $(MAIN_SRC) -I $(INC_DIR)

modulo: $(MODULO_SRC) $(MODULO_HPP)
	$(CC) $(CC_FLAGS) -o $@ $(MODULO_SRC) -I $(INC_DIR)
