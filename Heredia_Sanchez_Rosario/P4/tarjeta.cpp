#include <iomanip>
#include <ctype.h>
#include <functional>
#include <algorithm>

#include "tarjeta.hpp"
#include "usuario.hpp"


bool luhn(const Cadena& num);

struct EsBlanco
{
	inline bool operator()(char c) {return isspace(c);}
};

struct EsDigito : std::unary_function<char, bool>
{
	inline bool operator()(char c) const {return isdigit(c);}

};

std::unary_negate<EsDigito> not_EsDigito((EsDigito()));


//Constructor Numero
Numero::Numero(Cadena num) : num_{num}
{
	if(num_.length() == 0)
		throw Incorrecto(Razon::LONGITUD);

	Cadena::iterator i = std::remove_if(num_.begin(), num_.end(), EsBlanco());
	num_ = num_.substr(0, i - num_.begin());

	if(std::find_if(num_.begin(), num_.end(), not_EsDigito) != num_.end())
		throw Incorrecto(Razon::DIGITOS);


	if(num_.length() < 13 || num_.length() > 19)
		throw Incorrecto(Razon::LONGITUD);


	if(!luhn(num_))
		throw Incorrecto(Razon::NO_VALIDO);
}

// Operador < nuumero
bool Numero::operator <(const Numero& numero) const
{
	return num_ < numero.num_;
}

//Constructor Tarjeta
Tarjeta::Tarjeta(const Numero& numero, Usuario& usuario, const Fecha& caduca) 
: numero_{numero}, usuario_{&usuario}, caduca_{caduca}, activa_{true}
{
	Fecha hoy;
	if (caduca < hoy)
		throw Caducada(caduca);
	
	usuario.es_titular_de(*this);
}

//Observador tipo
Tarjeta::Tipo Tarjeta::tipo() const{
	
	Tipo tipo;

	Cadena num(numero_);

	if (num.substr(0,2) == "34" || num.substr(0,2) == "37") 
	{
		tipo = Tipo::AmericanExpress;
	} else if (num.substr(0,1) == "3") 
	{
		tipo = Tipo::JCB;
	} else if (num.substr(0,1) == "4") 
	{
		tipo = Tipo::VISA;
	} else if (num.substr(0,1) == "5") 
	{
		tipo = Tipo::Mastercard;
	} else if (num.substr(0,1) == "6") 
	{
		tipo = Tipo::Maestro;
	} else 
		tipo = Tipo::Otro;
	
	return tipo;
}

//Inserción Tipo
std::ostream& operator << (std::ostream& os, Tarjeta::Tipo const& tipo)
{
	switch (tipo) {
		case Tarjeta::Tipo::AmericanExpress: os << "American Express";
				break;
		case Tarjeta::Tipo::JCB: os << "JCB";
				break;
		case Tarjeta::Tipo::VISA: os << "VISA";
				break;
		case Tarjeta::Tipo::Mastercard: os << "Mastercard";
				break;
		case Tarjeta::Tipo::Maestro: os << "Maestro";
				break;
		case Tarjeta::Tipo::Otro: os << "Tipo indeterminado";
				break;
		default: os << "";
	}

	return os;
}

//Modificador - observador tarjeta activa
bool Tarjeta::activa(bool num)
{
	activa_ = num;
	return activa_;
}

//Modificador anula_totular
void Tarjeta::anula_titular()
{
	const_cast<Usuario*&>(usuario_) = nullptr;
	activa_ = false;

}

//Operador < Tarjeta
bool Tarjeta::operator <(const Tarjeta& tarjeta) const
{
	return numero_ < tarjeta.numero_;
}

//Destructor Tarjeta
Tarjeta::~Tarjeta()
{
	if (usuario_)
	usuario_->no_es_titular_de(*this);
	numeros_.erase(numero_);
}

//Observador titularFacial
const Cadena Tarjeta::titularFacial() const
{
	Cadena titular(usuario_->nombre() + " " + usuario_->apellidos());
	for (size_t i = 0; i < titular.length(); i++) {
		titular[i] = toupper(titular[i]);
	}
	return titular;
}

//Inserción Tarjeta
std::ostream& operator <<(std::ostream& os, const Tarjeta& tarjeta)
{
	os 	<< tarjeta.tipo() << std::endl 
		<< tarjeta.numero() << std::endl 
	   	<< tarjeta.titularFacial() << std::endl  
	   	<< "Caduca: " << std::setfill('0') << std::setw(2) << tarjeta.caducidad().mes() << "/" << (tarjeta.caducidad().anno() % 100);

    return os;
}