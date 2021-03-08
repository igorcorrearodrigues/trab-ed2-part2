#include "Quadtree.hpp"
#include <iostream>

Quadtree::Quadtree() {
    this->c = nullptr; 
    this->quadNW = nullptr; 
    this->quadNE = nullptr; 
    this->quadSW = nullptr; 
    this->quadSE = nullptr;
    this->coordX = 0;
    this->coordY = 0;
}

//o numero do quadrante e igual no plano cartesiano mesmo
//>= pra arestas, long igual joga pro lado E, lat igual joga pro lado N

size_t Quadtree::comparacao(Cidade novaCidade){
    if(novaCidade.longitude() >= this->coordX){
        if(novaCidade.latitude() >= this->coordY){
            return 1; //NE
        }
        else
            return 4; //SE
    }
    else{
        if(novaCidade.latitude() >= this->coordY){
            return 2; //NW
        }
        else
            return 3; //SW
    }
}

void Quadtree::insere(Cidade* city) 
{ 
    if (city == nullptr) 
        return;

    if (this->c == nullptr){
				this->c = new Cidade(*city);
        this->c = city;
        this->coordX = city->longitude();
        this->coordY = city->latitude();
        return; 
    } 
    
    size_t quadrante = comparacao(*city);

    switch(quadrante) {
        case 1: 
            if (this->quadNE == nullptr) 
                this->quadNE = new Quadtree();
            this->quadNE->insere(city); 
            break;
        case 2: 
            if (this->quadNW == nullptr) 
                this->quadNW = new Quadtree();
            this->quadNW->insere(city); 
            break;
        case 3: 
            if (this->quadSW == nullptr) 
                this->quadSW = new Quadtree();
            this->quadSW->insere(city); 
            break;
        case 4: 
            if (this->quadSE == nullptr) 
                this->quadSE = new Quadtree();
            this->quadSE->insere(city); 
            break;
        default:
            std::cerr << "Não foi inserido\n";
            return;
    }
} 

void Quadtree::selecionaProximaRegiao(std::list<Cidade*> cidadesNaRegiao ,double lat0, double long0, double lat1, double long1){
    if (this->quadNE != nullptr){
        if(this->quadNE->c->latitude() < lat1 && this->quadNE->c->latitude() > lat0 &&
           this->quadNE->c->longitude() < long1 && this->quadNE->c->longitude() > long0){
              cidadesNaRegiao.push_back(this->quadNE->c);
              this->quadNE->selecionaProximaRegiao(cidadesNaRegiao, lat0, long0, lat1, long1);
        }
    }
    if (this->quadNW != nullptr){
        if(this->quadNW->c->latitude() < lat1 && this->quadNW->c->latitude() > lat0 &&
           this->quadNW->c->longitude() < long1 && this->quadNW->c->longitude() > long0){
               cidadesNaRegiao.push_back(this->quadNW->c);
               this->quadNW->selecionaProximaRegiao(cidadesNaRegiao, lat0, long0, lat1, long1);
        }
    }
    if (this->quadSW != nullptr){
        if(this->quadSW->c->latitude() < lat1 && this->quadSW->c->latitude() > lat0 &&
           this->quadSW->c->longitude() < long1 && this->quadSW->c->longitude() > long0){
               cidadesNaRegiao.push_back(this->quadSW->c);
               this->quadSW->selecionaProximaRegiao(cidadesNaRegiao, lat0, long0, lat1, long1);
        }
    }
    if (this->quadSE != nullptr){
        if(this->quadSE->c->latitude() < lat1 && this->quadSE->c->latitude() > lat0 &&
           this->quadSE->c->longitude() < long1 && this->quadSE->c->longitude() > long0){
               cidadesNaRegiao.push_back(this->quadSE->c);
               this->quadSE->selecionaProximaRegiao(cidadesNaRegiao, lat0, long0, lat1, long1);
        }
    }
}

std::list<Cidade*> Quadtree::buscaRegiao(double lat0, double long0, double lat1, double long1){
    //delimitar as regioes dos quadrantes pra facilitar a busca (precisa ?)
    //se long0 <= x <= long1 && lat0 <= y <= lat1, colocar na lista e chamar recursivamente a busca na regiao nova
    std::list<Cidade*> cidadesNaRegiao;
    selecionaProximaRegiao(cidadesNaRegiao, lat0, long0, lat1, long1);
    return cidadesNaRegiao;
    //vai ser preciso uma hashing que garanta o inicio igual para cidades na mesma regiao, pq o csv usado na quad n tem as datas
    //e pra pegar as cidaddes ao longo das datas na tabela hash depois pode complicar
    //mod 10000 pra codigo cidade (mesmo estado tem os 2 primeiros digitos iguais) concatenando com hashing na data
}
