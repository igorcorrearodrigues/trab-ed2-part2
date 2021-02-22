#include "Registro.hpp"
#include "utils.hpp"

#include <iostream>

const std::string& Registro::date() const
{
	return this->_date;
}

const std::string& Registro::state() const
{
	return this->_state;
}

const std::string& Registro::city() const
{
	return this->_city;
}

const std::string& Registro::code() const
{
	return this->_code;
}

int Registro::cases() const
{
	return this->_cases;
}

int Registro::deaths() const
{
	return this->_deaths;
}

int Registro::setDate(const std::string& date)
{
	// validate date
	this->_date = date;
	return 0;
}

int Registro::setState(const std::string& state)
{
	// validate state
	this->_state = state;
	return 0;
}

int Registro::setCity(const std::string& city)
{
	// validate city
	this->_city = city;
	return 0;
}

int Registro::setCode(const std::string& code)
{
	// validate code
	this->_code = code;
	return 0;
}

int Registro::setCases(int cases)
{
	// validate cases
	this->_cases = cases;
	return 0;
}

int Registro::setDeaths(int deaths)
{
	// validate deaths
	this->_deaths = deaths;
	return 0;
}

std::ostream& Registro::print(std::ostream& os) const
{
	return os << this->date() << "," << this->state() << ","
		<< this->city() << "," << this->code() << ","
		<< this->cases() << "," << this->deaths();
}


std::istream& Registro::read(std::istream& is)
{
	std::string line;
	size_t pos = 0;

	if (std::getline(is, line)) {
		// Adicionar alguma forma de tratamento de erros nessa funcao
		this->setDate(string_tok(line, ',', &pos));
		this->setState(string_tok(line, ',', &pos));
		this->setCity(string_tok(line, ',', &pos));
		this->setCode(string_tok(line, ',', &pos));
		this->setCases(std::stoi(string_tok(line, ',', &pos)));
		this->setDeaths(std::stoi(string_tok(line, '\0', &pos)));
	}
	return is;
}
