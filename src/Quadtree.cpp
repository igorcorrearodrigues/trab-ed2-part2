#include "Quadtree.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>

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

    bool regiaoDistante = true;

    if (this->quadNE != nullptr){
        if(this->quadNE->coordY < lat1 && this->quadNE->coordY > lat0 &&
           this->quadNE->coordX < long1 && this->quadNE->coordX > long0){
                cidadesNaRegiao->push_back(this->quadNE->c);
                this->quadNE->selecionaProximaRegiao(cidadesNaRegiao, lat0, long0, lat1, long1);
                regiaoDistante = false;
        }
    }
    if (this->quadNW != nullptr){
        if(this->quadNW->coordY < lat1 && this->quadNW->coordY > lat0 &&
           this->quadNW->coordX < long1 && this->quadNW->coordX > long0){
                cidadesNaRegiao->push_back(this->quadNW->c);
                this->quadNW->selecionaProximaRegiao(cidadesNaRegiao, lat0, long0, lat1, long1);
                regiaoDistante = false;
        }
    }
    if (this->quadSW != nullptr){
        if(this->quadSW->coordY < lat1 && this->quadSW->coordY > lat0 &&
           this->quadSW->coordX < long1 && this->quadSW->coordX > long0){
                cidadesNaRegiao->push_back(this->quadSW->c);
                this->quadSW->selecionaProximaRegiao(cidadesNaRegiao, lat0, long0, lat1, long1);
                regiaoDistante = false;
        }
    }
    if (this->quadSE != nullptr){
        if(this->quadSE->coordY < lat1 && this->quadSE->coordY > lat0 &&
           this->quadSE->coordX < long1 && this->quadSE->coordX > long0){
                cidadesNaRegiao->push_back(this->quadSE->c);
                this->quadSE->selecionaProximaRegiao(cidadesNaRegiao, lat0, long0, lat1, long1);
                regiaoDistante = false;
        }
    }
    if(regiaoDistante){
        //std::cerr << "PASSOU 1" << std::endl;
        if(long0 >= this->coordX){
            //std::cerr << "PASSOU 2" << std::endl;
            if(lat0 >= this->coordY){
                //std::cerr << "PASSOU NE" << std::endl;
                if (this->quadNE != nullptr){
                    this->quadNE->selecionaProximaRegiao(cidadesNaRegiao, lat0, long0, lat1, long1); //NE
                }
            }
            else{
                //std::cerr << "PASSOU SE" << std::endl;
                if (this->quadSE != nullptr){
                    this->quadSE->selecionaProximaRegiao(cidadesNaRegiao, lat0, long0, lat1, long1); //SE
                }
            }
        }
        else{
            //std::cerr << "PASSOU 3" << std::endl;
            if(lat0 >= this->coordY){
                //std::cerr << "PASSOU NW" << std::endl;
                if (this->quadNW != nullptr){
                    this->quadNW->selecionaProximaRegiao(cidadesNaRegiao, lat0, long0, lat1, long1); //NW
                }
            }
            else{
                //std::cerr << "PASSOU SW" << std::endl;
                if (this->quadSW != nullptr){
                    this->quadSW->selecionaProximaRegiao(cidadesNaRegiao, lat0, long0, lat1, long1); //SW
                }
            }
        }
    }

}

std::list<Cidade*> Quadtree::buscaRegiao(double lat0, double long0, double lat1, double long1)
{
    //delimitar as regioes dos quadrantes pra facilitar a busca (precisa ?)
    //se long0 <= x <= long1 && lat0 <= y <= lat1, colocar na lista e chamar recursivamente a busca na regiao nova
    std::list<Cidade*> cidadesNaRegiao;
    selecionaProximaRegiao(&cidadesNaRegiao, lat0, long0, lat1, long1);
    /*std::cerr << "Lista de cidades na Região: " << std::endl;
    for(const auto& cidadeAtual : cidadesNaRegiao)
        std::cerr << *cidadeAtual << std::endl;*/
    return cidadesNaRegiao;
}


std::list<Cidade*> Quadtree::desenhaMapaRegional(double paramlat0, double paramlong0, double paramlat1, double paramlong1)
{
    std::ofstream img("mapaRegiao.ppm");
     
	double lat0 = paramlat0, long0 = paramlong0;
    double lat1 = paramlat1, long1 = paramlong1;

    //funçao q garante que lat 1 > lat 0 && long1 > long1
    // na chamada mesmo, senão vai dar ruim depois

    int width = (int) std::max(abs(long0),abs(long1)); //abs do maior valor de long
    int height =(int) std::max(abs(lat0),abs(lat1)); //abs do maior valor de lat

	if (!img.is_open()) {
		std::cerr << "Falha ao abrir o arquivo\n";
        return std::list<Cidade*>{};
	}

	img << "P3\n"<< 2*width << " " << 2*height << "\n255\n";

    std::list<Cidade*> cidadesNaRegiao = this->buscaRegiao(lat0,long0,lat1,long1);
    std::list<Ponto> pontosNaRegiao;

    for(const auto& cidadeAtual : cidadesNaRegiao){
        pontosNaRegiao.push_back({
            (int) cidadeAtual->longitude(),
            (int) cidadeAtual->latitude()
        });
    }

    /*std::cerr << "Lista de Pontos na Região: " << std::endl;
    for(const auto& pontoAtual : pontosNaRegiao){
        std::cerr << pontoAtual.x << " " << pontoAtual.y << std::endl;
    }*/

	for (int y0 = height; y0 > -height; --y0) {
		for (int x0 = -width; x0 < width; ++x0) {
            Ponto pontoAtual({(int) x0, (int) y0});
            int r = 0;
            int g = 0;
            int b = 0;
            if (std::find(pontosNaRegiao.begin(), pontosNaRegiao.end(), pontoAtual) != pontosNaRegiao.end()){
                //std::cerr << "Achou" << std::endl;
                r = 43;
			    g = 240;
			    b = 125;
            }
			img << r << " " << g << " " << b << std::endl;
		}
	}
	img.close();
    return cidadesNaRegiao;
}


void Quadtree::desenhaMapa()
{
    std::ofstream img("mapaBrasil.ppm");
     
	int lat0 = -45, long0 = -75;
    int lat1 = 15, long1 = -30;

    int width = 75; //abs do maior valor de long
    int height = 45; //abs do maior valor de lat

	if (!img.is_open()) {
		std::cerr << "Falha ao abrir o arquivo\n";
        return;
	}

	img << "P3\n"<< 2*width << " " << 2*height << "\n255\n";

    std::list<Cidade*> cidadesNaRegiao = this->buscaRegiao(lat0,long0,lat1,long1);
    std::list<Ponto> pontosNaRegiao;

    for(const auto& cidadeAtual : cidadesNaRegiao){
        pontosNaRegiao.push_back({
            (int) cidadeAtual->longitude(),
            (int) cidadeAtual->latitude()
        });
    }

    /*std::cerr << "Lista de Pontos na Região: " << std::endl;
    for(const auto& pontoAtual : pontosNaRegiao){
        std::cerr << pontoAtual.x << " " << pontoAtual.y << std::endl;
    }*/

	for (int y0 = height; y0 > -height; --y0) {
		for (int x0 = -width; x0 < width; ++x0) {
            Ponto pontoAtual({(int) x0, (int) y0});
            int r = 0;
            int g = 0;
            int b = 0;
            if (std::find(pontosNaRegiao.begin(), pontosNaRegiao.end(), pontoAtual) != pontosNaRegiao.end()){
                //std::cerr << "Achou" << std::endl;
                r = 43;
			    g = 240;
			    b = 125;
            }
			img << r << " " << g << " " << b << std::endl;
		}
	}
	img.close();
}
