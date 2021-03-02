#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "Cidade.hpp"

class Quadtree
{ 
private:
    Cidade* c; 
    Quadtree* quadNW; 
    Quadtree* quadNE; 
    Quadtree* quadSW; 
    Quadtree* quadSE;
    double coordX;
    double coordY;

public:
    Quadtree();
    void insere(c*);
    //return uma lista com as cidade buscaRegiao(x0, y0, x1, y1);
};

#endif // QUADTREE_HPP