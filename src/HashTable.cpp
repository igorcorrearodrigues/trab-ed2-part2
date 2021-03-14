#include "HashTable.hpp"

#include <algorithm>

No::No(): info(), status(STATUS_LIVRE)
{
}

#define _INSERE(no, r) do { no.info = r; no.status = No::STATUS_OCUPADO; } while (0)

static size_t h1(std::string codigo, std::string data)
{
	std::string s = codigo + data;
	size_t hash = 0;

	for (auto c : s) {
		hash = hash * 256 + c;
	}
	return hash;
}

static size_t h2(std::string codigo, std::string data)
{
	std::string s = codigo + data;
	size_t hash = 0;

	size_t pos = 0;
	for (auto c : s) {
		hash += (c + 31 * pos++);
	}
	return hash;
}

static size_t getPos(std::string codigo, std::string data, size_t i)
{
	if (i == 0)
		return h1(codigo, data) % TABLE_M;
	return (h1(codigo, data) + i * h2(codigo, data)) % TABLE_M;
}

static size_t getPos(const Registro& r, size_t i)
{
	return getPos(r.code(), r.date(), i);
}

static void insereOrdenado(std::vector<size_t>& vec, size_t valor)
{
	std::vector<size_t>::iterator it = std::lower_bound(vec.begin(), vec.end(), valor);
	vec.insert(it, valor);
}

static void removeDoVector(std::vector<size_t>& vec, size_t valor)
{
	std::vector<size_t>::iterator it = std::find(vec.begin(), vec.end(), valor);
	if (it != vec.end()) {
		vec.erase(it);
	}
}

HashTable::HashTable()
{
	this->tabela = new No[TABLE_M];
}

HashTable::~HashTable()
{
	delete[] this->tabela;
}

bool HashTable::insere(const Registro& r)
{
	for (size_t i = 0; i < TABLE_M; ++i) {
		size_t pos = getPos(r, i);

		if (this->tabela[pos].status != No::STATUS_OCUPADO) {
			_INSERE(this->tabela[pos], r);
			insereOrdenado(this->hashes, pos);
			return true;
		}
	}
	return false;
}

No *HashTable::_buscar(std::string codigo, std::string data)
{
	for (size_t i = 0; i < TABLE_M; ++i) {
		No *no = this->tabela + getPos(codigo, data, i);

		if (no->status == No::STATUS_LIVRE)
			break;
		if (no->status == No::STATUS_OCUPADO) {
			const Registro& info = no->info;

			if (info.code() == codigo && info.date() == data)
				return no;
		}
	}
	return nullptr;
}

Registro* HashTable::buscar(std::string codigo, std::string data)
{
	No *noptr;

	if ((noptr = this->_buscar(codigo, data)) == nullptr)
		return nullptr;
	return &(noptr->info);
}

void HashTable::remover(std::string codigo, std::string data)
{
	No *noptr;

	if ((noptr = this->_buscar(codigo, data)) != nullptr) {
		noptr->status = No::STATUS_REMOVIDO;
		removeDoVector(this->hashes, (noptr - this->tabela));
	}
}

std::vector<size_t> HashTable::getRandomHashes(size_t n)
{
	std::vector<size_t> aleatorios(this->hashes);
	
	std::random_shuffle(aleatorios.begin(), aleatorios.end());
	aleatorios.resize(n);
	return aleatorios;
}
