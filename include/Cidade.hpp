#ifndef CIDADE_HPP
#define CIDADE_HPP

#include <cstddef>
#include <istream>
#include <ostream>

#include "CodigoDaCidade.hpp"

class Cidade
{
private:
	std::string _nome;
	double _latitude;
	double _longitude;
	CodigoDaCidade _codigo;
	int _codigoDoEstado;
	bool _isCapital;

public:
	const std::string& nome() const;
	double latitude() const;
	double longitude() const;
	const std::string& codigo() const;
	int codigoDoEstado() const;
	bool isCapital() const;

	void setNome(const std::string& nome);
	void setLatitude(double latitude);
	void setLongitude(double longitude);
	void setCodigo(const std::string& codigo);
	void setCodigoDoEstado(int codigo);
	void setCapital(bool isCapital);

	std::ostream& print(std::ostream& out) const;
	std::istream& read(std::istream& in);
};

inline std::ostream& operator<<(std::ostream& out, const Cidade& c)
{
	return c.print(out);
}

inline std::istream& operator>>(std::istream& in, Cidade& c)
{
	return c.read(in);
}

#endif // CIDADE_HPP
