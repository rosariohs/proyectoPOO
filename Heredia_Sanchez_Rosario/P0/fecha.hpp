#ifndef FECHA_HPP
#define FECHA_HPP

#include<iostream> //Para el 'operator<<'

class Fecha {

private:
	
	////VARIABLES////
	int dd_, mm_, aaaa_, anioActual_;
	
	////FUNCIONES////
	void actualiza();
	bool comprueba() const;
	int dia_max() const;
	
public:
	
	////INVALIDA////
	class Invalida {
	private:
		const char *info_;
	public:
		Invalida(const char *in);
		const char* por_que() const;
	};

	////CONSTRUCTOR////
	Fecha(int dd=0, int mm=0, int aaaa=0);
	Fecha(const char* c);
	Fecha(const Fecha &f);//constructor copia
	
	/*Constructor asignación default*/
	operator const char*() const; //conversor a const char*
	
	////DESTRUCTOR////
	~Fecha();
	
	////OBSERVADORES////
	int dia() const;
	int mes() const;
	int anno() const;
	
	////OPERADOR////
	Fecha operator+=(int i);
	Fecha operator-=(int i);
	Fecha operator++();
	Fecha& operator++(int);
	Fecha operator--();
	Fecha& operator--(int);

};

////OPERADORES ARITMÉTICOS////
Fecha operator+(Fecha f, int d);
Fecha operator-(Fecha f, int d);

////OPERADORES LÓGICOS////
bool operator==(const Fecha& f1, const Fecha& f2);
bool operator!=(const Fecha& f1, const Fecha& f2);
bool operator> (const Fecha& f1, const Fecha& f2);
bool operator< (const Fecha& f1, const Fecha& f2);
bool operator>=(const Fecha& f1, const Fecha& f2);
bool operator<=(const Fecha& f1, const Fecha& f2);

////ENTRADA - SALIDA////
std::ostream& operator<<(std::ostream& os, const Fecha& f);
std::istream& operator>>(std::istream& is, Fecha& f);

#endif
