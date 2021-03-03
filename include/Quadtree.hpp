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
    size_t comparacao(Cidade novaCidade);
    void insere(Cidade* city);
    void selecionaProximaRegiao(std::list<Cidade*> cidadesNaRegiao ,double lat0, double long0, double lat1, double long1);
    std::list<Cidade*> buscaRegiao(double x0, double y0, double x1, double y1);
};

#endif // QUADTREE_HPP