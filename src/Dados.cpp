#include "Dados.hpp"

#include <iomanip>

Dados::Dados(std::string titulo)
{
    this->_titulo = titulo;
    this->totalComparacoes = 0;
}

void Dados::addAmostra(const Amostra& a)
{
    this->tempoTotalDeBusca += a.tempoBusca;
    this->tempoTotalDeInsercao += a.tempoInsercao;
    this->totalComparacoes += a.comparacoesBusca;
    this->amostras.push_back(a);
}

size_t Dados::numeroDeAmostras() const
{
    return this->amostras.size();
}

const std::string& Dados::titulo() const
{
    return this->_titulo;
}

double Dados::mediaComparacoes() const
{
    return (double) this->totalComparacoes / this->numeroDeAmostras();
}

std::ostream& Dados::print(std::ostream& file) const
{
    // file << std::setw(11) << this->titulo();
	// file << std::setw(15) << "Comparacoes";
	// file << std::setw(15) << "Tempo de busca [µs]";
	// file << std::setw(15) << "Tempo de inserção [µs]";
	// file << std::endl;



    // size_t row = 1;

    // for (const auto& amostra: this->amostras) {
	    // file << std::setw(11) << (row++);
	    // file << std::setw(15) << amostra.comparacoesBusca;
	    // file << std::setw(15) << amostra.tempoInsercao.count();
	    // file << std::setw(15) << amostra.tempoBusca.count();
        // file << std::endl;
    // }

    // #define MEDIA_TEMPO(_duration)
        // ((double) (_duration).count() / this->numeroDeAmostras())
    
	// file << std::setw(11) << "Media";
	// file << std::setw(15) << this->mediaComparacoes();
	// file << std::setw(15) << MEDIA_TEMPO(this->tempoTotalDeBusca);
	// file << std::setw(15) << MEDIA_TEMPO(this->tempoTotalDeInsercao);
	// file << std::endl;
    // Oq é std??
	// file << std::setw(11) << "std";
	// file << std::setw(15) << stdComp[codigo][i];
	// file << std::setw(15) << stdTrocas[codigo][i];
	// file << std::setw(15) << stdTempos[codigo][i];
	// file << std::endl;
    return file;
}