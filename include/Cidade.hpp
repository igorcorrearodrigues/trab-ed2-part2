#ifndef CIDADE_HPP
#define CIDADE_HPP

#include <cstddef>
#include <istream>
#include <ostream>

class Cidade
{
private:
	std::string _nome;
	double _latitude;
	double _longitude;
	unsigned _codigo;
	uint8_t _codigoDoEstado;
	bool _isCapital;

public:
	const std::string& nome() const;
	double latitude() const;
	double longitude() const;
	unsigned codigo() const;
	uint8_t codigoDoEstado() const;
	bool isCapital() const;

	void setNome(const std::string& nome);
	void setLatitude(double latitude);
	void setLongitude(double longitude);
	void setCodigo(unsigned codigo);
	void setCodigoDoEstado(unsigned codigo);

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
