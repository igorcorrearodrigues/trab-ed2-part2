#include "Quadtree.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>

#define WIDTH 150
#define HEIGHT 150

struct Ponto{
    int x, y;
    bool operator==(const Ponto& p){
        return this->x == p.x && this->y == p.y;
    };
};

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
        this->coordX = city->longitude();
        this->coordY = city->latitude();
        //std::cerr << "Inseriu: " << *this->c << std::endl;
        return; 
    } 
    
    
    size_t quadrante = comparacao(*city);
    //std::cerr << "Quadrante: " << quadrante << std::endl;

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

void Quadtree::selecionaProximaRegiao(std::list<Cidade*>* cidadesNaRegiao ,double lat0, double long0, double lat1, double long1){
    /*std::cerr << "Ultimo atual: " << cidadesNaRegiao->back() << std::endl;
    if (this->quadNE != nullptr && this->quadNW != nullptr && this->quadSW != nullptr && this->quadSE != nullptr){
        std::cerr << "quadNE: " << *this->quadNE->c << std::endl;
        std::cerr << "quadNW: " << *this->quadNW->c << std::endl;
        std::cerr << "quadSW: " << *this->quadSW->c << std::endl;
        std::cerr << "quadSE: " << *this->quadSE->c << std::endl;
    }*/
    if (this->quadNE != nullptr){
        if(this->quadNE->coordY < lat1 && this->quadNE->coordY > lat0 &&
           this->quadNE->coordX < long1 && this->quadNE->coordX > long0){
              cidadesNaRegiao->push_back(this->quadNE->c);
              this->quadNE->selecionaProximaRegiao(cidadesNaRegiao, lat0, long0, lat1, long1);
        }
    }
    if (this->quadNW != nullptr){
        if(this->quadNW->coordY < lat1 && this->quadNW->coordY > lat0 &&
           this->quadNW->coordX < long1 && this->quadNW->coordX > long0){
               cidadesNaRegiao->push_back(this->quadNW->c);
               this->quadNW->selecionaProximaRegiao(cidadesNaRegiao, lat0, long0, lat1, long1);
        }
    }
    if (this->quadSW != nullptr){
        if(this->quadSW->coordY < lat1 && this->quadSW->coordY > lat0 &&
           this->quadSW->coordX < long1 && this->quadSW->coordX > long0){
               cidadesNaRegiao->push_back(this->quadSW->c);
               this->quadSW->selecionaProximaRegiao(cidadesNaRegiao, lat0, long0, lat1, long1);
        }
    }
    if (this->quadSE != nullptr){
        if(this->quadSE->coordY < lat1 && this->quadSE->coordY > lat0 &&
           this->quadSE->coordX < long1 && this->quadSE->coordX > long0){
               cidadesNaRegiao->push_back(this->quadSE->c);
               this->quadSE->selecionaProximaRegiao(cidadesNaRegiao, lat0, long0, lat1, long1);
        }
    }
}

std::list<Cidade*> Quadtree::buscaRegiao(double lat0, double long0, double lat1, double long1){
    //delimitar as regioes dos quadrantes pra facilitar a busca (precisa ?)
    //se long0 <= x <= long1 && lat0 <= y <= lat1, colocar na lista e chamar recursivamente a busca na regiao nova
    std::list<Cidade*>* cidadesNaRegiao;
    selecionaProximaRegiao(cidadesNaRegiao, lat0, long0, lat1, long1);
    std::cerr << "Lista de cidades na Região: " << std::endl;
    for(const auto& cidadeAtual : *cidadesNaRegiao)
        std::cerr << cidadeAtual << std::endl;
    return *cidadesNaRegiao;
}

void Quadtree::desenhaMapa(){
    std::ofstream fp("imagem.ppm");
	unsigned char lat0 = HEIGHT, long0 = WIDTH, lat1 = HEIGHT, long1 = WIDTH;


	if (!fp.is_open()) {
		std::cerr << ("Falha ao abrir o arquivo\n");
	}

	fp << "P3\n"<< WIDTH << HEIGHT << "\n255\n";

    std::list<Cidade*> cidadesNaRegiao = this->buscaRegiao(-lat0,-long0,lat1,long1);
    std::list<Ponto> pontosNaRegiao;

    for(const auto& cidadeAtual : cidadesNaRegiao){
        pontosNaRegiao.push_back({
            (int)cidadeAtual->longitude(),
            (int)cidadeAtual->latitude()
        });
    }

	for (lat0 = -lat1; lat0 < lat1; ++lat0) {
		for (long0 = -long1; long0 < long1; ++long0) {
            Ponto pontoAtual({long0,lat0});
            int r = 0;
            int g = 0;
            if(std::find(pontosNaRegiao.begin(), pontosNaRegiao.end(), pontoAtual) != pontosNaRegiao.end())
                g = 255;
            int b = 0;

			//int r = long0 % 255;
			//int g = lat0 % 255;
			//int b = (long0 * lat0) % 255;

			fp << r << g << b << "\n";
		}
	}
    
	fp.close();
}
