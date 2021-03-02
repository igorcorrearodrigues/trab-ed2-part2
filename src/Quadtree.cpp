#include "./include/Quadtree.hpp"

Quadtree::Quadtree() {
    this->c = NULL; 
    this->quadNW = NULL; 
    this->quadNE = NULL; 
    this->quadSW = NULL; 
    this->quadSE = NULL;
    this->coordX = 0;
    this->coordY = 0;
}