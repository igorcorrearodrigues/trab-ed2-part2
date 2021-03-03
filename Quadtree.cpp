#include "./include/Quadtree.hpp"
#include <iostream>

Quadtree::Quadtree() {
    this->c = NULL; 
    this->quadNW = NULL; 
    this->quadNE = NULL; 
    this->quadSW = NULL; 
    this->quadSE = NULL;
    this->coordX = 0;
    this->coordY = 0;
}

//o numero do quadrante e igual no plano cartesiano mesmo
size_t Quadtree::comparacao(Cidade novaCidade){
    if(novaCidade.longitude() > this->coordX){
        if(novaCidade.latitude() > this->coordY){
            return 1; //NE
        }
        else
            return 4; //SE
    }
    else{
        if(novaCidade.latitude() > this->coordY){
            return 2; //NW
        }
        else
            return 3; //SW
    }
}

void Quadtree::insere(Cidade* city) 
{ 
    if (city == NULL) 
        return;

    if (this->c == NULL){
        this->c = city;
        this->coordX = city->longitude();
        this->coordY = city->latitude();
        return; 
    } 
    
    size_t quadrante = comparacao(*city);

    switch(quadrante) {
        case 1: 
            if (this->quadNE == NULL) 
                this->quadNE = new Quadtree();
            this->quadNE->insere(city); 
            break;
        case 2: 
            if (this->quadNW == NULL) 
                this->quadNW = new Quadtree();
            this->quadNW->insere(city); 
            break;
        case 3: 
            if (this->quadSW == NULL) 
                this->quadSW = new Quadtree();
            this->quadSW->insere(city); 
            break;
        case 4: 
            if (this->quadSE == NULL) 
                this->quadSE = new Quadtree();
            this->quadSE->insere(city); 
            break;
        default:
            std::cerr << "Não foi inserido\n";
            return;
    }
} 