#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "Cidade.hpp"

class Quadtree
{ 
private:
    Cidade* city; 
    Quadtree* quadNW; 
    Quadtree* quadNE; 
    Quadtree* quadSW; 
    Quadtree* quadSE;
    double coordX;
    double coordY;

public:
    Quadtree();
    size_t comparacao(Cidade* novaCidade);
    void insere(Cidade* city);
    //return uma lista com as cidade buscaRegiao(x0, y0, x1, y1);
};

#endif // QUADTREE_HPP