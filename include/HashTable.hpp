#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#define TABLE_M 1431490

#include "Registro.hpp"

class HashTable
{
private:
	struct No
	{
		const static size_t STATUS_LIVRE    = 1;
		const static size_t STATUS_OCUPADO  = 2;
		const static size_t STATUS_REMOVIDO = 3;

		Registro info;
		char status;

		No(): info(), status(STATUS_LIVRE)
		{
		}
	};

	No tabela[TABLE_M];

	No *_buscar(std::string codigo, std::string data);

public:
	bool insere(const Registro& r);
	Registro *buscar(std::string codigoDaCidade, std::string data);
	void remover(std::string codigoDaCidade, std::string data);
};

#endif // HASH_TABLE_HPP
