#ifndef FECHA_HPP
#define FECHA_HPP
#include <iostream>
#include <ctime>
#include <cstdio>

using namespace std;

class Fecha
{
public:

	static const int AnnoMinimo = 1902;
	static const int AnnoMaximo = 2037;

	class Invalida
	{
	public:
		Invalida(const char* motivo);
		const char* por_que() const;
	private:
		const char* motivo_;
	};

	explicit Fecha(int dia = 0, int mes = 0, int anno = 0);
	Fecha(const char* fecha);

	inline int dia() const noexcept{return dia_;}
	inline int mes() const noexcept{return mes_;}
	inline int anno() const noexcept{return anno_;}

	const char* cadena() const;

	Fecha& operator ++();
	Fecha operator ++(int);
	Fecha& operator --();
	Fecha operator --(int);

	Fecha& operator +=(int n);
	Fecha& operator -=(int n);

	Fecha operator +(int n);
	Fecha operator -(int n);
private:
	int dia_, mes_, anno_;
	void validarFecha() const;
};

Fecha operator +(const Fecha& f, int n);
Fecha operator -(const Fecha& f, int n);
bool operator ==(const Fecha& fecha1, const Fecha& fecha2);
bool operator !=(const Fecha& fecha1, const Fecha& fecha2);
bool operator <(const Fecha& fecha1, const Fecha& fecha2);
bool operator <=(const Fecha& fecha1, const Fecha& fecha2);
bool operator >(const Fecha& fecha1, const Fecha& fecha2);
bool operator >=(const Fecha& fecha1, const Fecha& fecha2);

std::istream& operator >>(std::istream& is, Fecha& fecha);
std::ostream& operator <<(std::ostream& os, const Fecha& fecha);

#endif /*FECHA_HPP*/