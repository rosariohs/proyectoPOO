#ifndef TARJETA_HPP
#define TARJETA_HPP

#include <iostream>
#include <set>

#include "cadena.hpp"
#include "fecha.hpp"

//class numero
class Numero
{
public:
	enum Razon{LONGITUD, DIGITOS, NO_VALIDO};
	Numero(Cadena num);
	operator const char*() const {return num_.c_str();}
	bool operator <(const Numero& num) const;

	//clas incorrecto
	class Incorrecto
	{
	public:
		Incorrecto(Razon razon) : razon_{razon} {}
		Razon razon() const {return razon_;}
	private:
		Razon razon_;
	};
	//fin incorrecto

private:
	Cadena num_;
};
// fin numero


class Usuario;
//class tarjeta
class Tarjeta
{
public:
	enum Tipo{Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};
	typedef std::set<Numero> Numeros;
	//constructor
	Tarjeta(const Numero& numero, Usuario& usuario, const Fecha& caduca);
	Tarjeta(const Tarjeta& tarjeta) = delete;
	Tarjeta& operator= (const Tarjeta& tarjeta) = delete;
	
	Tipo tipo() const;
	//metodos observadores
	const Numero& numero() const {return numero_;}
	const Usuario* titular() const {return usuario_;}
	const Cadena titularFacial() const;
	Fecha caducidad() const {return caduca_;}

	bool activa() const {return activa_;}
	bool activa(bool val = true);

	
	void anula_titular();
	bool operator <(const Tarjeta& tarjeta) const;
	//destructor
	~Tarjeta();

	//class desactivada
	class Desactivada
	{

	};
	//fin desactivada

	// class caducada
	class Caducada
	{
	public:
		Caducada(Fecha fecha) : fecha_{fecha} {}
		Fecha cuando() const {return fecha_;}
	private:
		Fecha fecha_;
	};
	// fin caducada

	//class num_duplicado
	class Num_duplicado
	{
	public:
		Num_duplicado(Numero numero) : numero_{numero} {}
		Numero que() const {return numero_;}
	private:
		Numero numero_;
	};
	//fin num_duplicado

private:
	const Numero numero_;
	Usuario* usuario_;
	const Fecha caduca_;
	bool activa_;
	
	//Tipo tipo_;
	Numeros numeros_;
};

std::ostream& operator <<(std::ostream& os, const Tarjeta& tarjeta);
std::ostream& operator <<(std::ostream& os, Tarjeta::Tipo const& tipo);


#endif // TARJETA_HPP