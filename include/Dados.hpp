#ifndef DADOS_HPP
#define DADOS_HPP

#include <chrono>
#include <string>
#include <vector>

struct Amostra
{
	std::chrono::microseconds tempoBusca;
	std::chrono::microseconds tempoInsercao;
	size_t comparacoesBusca;
};

class Dados
{
private:
	std::vector<Amostra> amostras;
	std::string _titulo;
	std::chrono::microseconds tempoTotalDeBusca;
	std::chrono::microseconds tempoTotalDeInsercao;
	size_t totalComparacoes;

public:
	Dados(std::string titutlo);

	void addAmostra(const Amostra& a);
	size_t numeroDeAmostras() const;
	const std::string& titulo() const;
	double mediaComparacoes() const;
	std::ostream& print(std::ostream& out) const;
};

inline std::ostream& operator<<(std::ostream& out, const Dados& d)
{
	return d.print(out);
}

#endif // DADOS_HPP