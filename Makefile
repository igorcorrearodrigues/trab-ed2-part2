CC=g++
CC_FLAGS=-W -Wall -pedantic -std=c++11
INC_DIR=./include
SRC_DIR=./src

MAIN_SRC=main.cpp \
				 $(SRC_DIR)/Cidade.cpp \
				 $(SRC_DIR)/ArvB.cpp \
				 $(SRC_DIR)/NoB.cpp \
				 $(SRC_DIR)/AVLTree.cpp \
				 $(SRC_DIR)/Registro.cpp   \
				 $(SRC_DIR)/HashTable.cpp  \
				 $(SRC_DIR)/Quadtree.cpp   \
				 $(SRC_DIR)/string_tok.cpp

MAIN_HPP=$(INC_DIR)/Cidade.hpp    \
				 $(INC_DIR)/Registro.hpp  \
				 $(INC_DIR)/ArvB.hpp  \
				 $(INC_DIR)/AVLTree.hpp  \
				 $(INC_DIR)/NoB.hpp  \
				 $(INC_DIR)/HashTable.hpp \
				 $(INC_DIR)/Quadtree.hpp 


MODULO_HPP=$(INC_DIR)/Quadtree.hpp \
					 $(INC_DIR)/HashTable.hpp \
					 $(INC_DIR)/NoB.hpp    \
					 $(INC_DIR)/ArvB.hpp    \
					 $(INC_DIR)/AVLTree.hpp \
					 $(INC_DIR)/AVLNode.hpp \
					 $(INC_DIR)/Cidade.hpp \
					 $(INC_DIR)/Registro.hpp \
					 $(INC_DIR)/utils.hpp

MODULO_SRC=modulo_de_teste.cpp      \
					 $(SRC_DIR)/AVLTree.cpp   \
					 $(SRC_DIR)/NoB.cpp      \
					 $(SRC_DIR)/ArvB.cpp      \
					 $(SRC_DIR)/Cidade.cpp    \
					 $(SRC_DIR)/HashTable.cpp \
					 $(SRC_DIR)/Quadtree.cpp  \
					 $(SRC_DIR)/Registro.cpp  \
					 $(SRC_DIR)/string_tok.cpp 


build: main

main: $(MAIN_SRC) $(MAIN_HPP)
	$(CC) $(CC_FLAGS) -o $@ $(MAIN_SRC) -I $(INC_DIR)

modulo: $(MODULO_SRC) $(MODULO_HPP)
	$(CC) $(CC_FLAGS) -o $@ $(MODULO_SRC) -I $(INC_DIR)
