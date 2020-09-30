#include <iomanip>
#include <ctype.h>

#include "tarjeta.hpp"
#include "usuario.hpp"


bool luhn(const Cadena& num);

//Constructor Numero
Numero::Numero(Cadena num) 
: num_{num}
{
	size_t cont = 0;
	size_t digits = 0;
	for (size_t i = 0; i < num.length(); ++i)
	{
		if (isdigit(num[i])) {
			digits++;
		} else {
			if (!isspace(num[i]))
				throw Incorrecto(Razon::DIGITOS);
		}
	}

	Cadena aux(digits);

	for (size_t i = 0; i < num.length(); ++i)
	{
		if (isdigit(num[i])) {
			aux[cont] = num[i];
			cont++;
		}
	}

	num_ = aux;

	if (num.length() < 13 || num.length() > 19)
		throw Incorrecto(Razon::LONGITUD);

	if (!luhn(num_))
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
	
	Tarjeta::Tipo tipo;

	Cadena numerito(numero_);

	if (numerito.substr(0,2) == "34" || numerito.substr(0,2) == "37") {
		tipo = Tarjeta::Tipo::AmericanExpress;
	} else if (numerito.substr(0,1) == "3") {
		tipo = Tarjeta::Tipo::JCB;
	} else if (numerito.substr(0,1) == "4") {
		tipo = Tarjeta::Tipo::VISA;
	} else if (numerito.substr(0,1) == "5") {
		tipo = Tarjeta::Tipo::Mastercard;
	} else if (numerito.substr(0,1) == "6") {
		tipo = Tarjeta::Tipo::Maestro;
	} else {
		tipo = Tarjeta::Tipo::Otro;
	}
	return tipo;
}

//Inserción Tipo
std::ostream& operator << (std::ostream& os, Tarjeta::Tipo const& tipo)
{
	switch (tipo) {
		case Tarjeta::Tipo::AmericanExpress:	os << "American Express";
				break;
		case Tarjeta::Tipo::JCB: os << "JCB";
				break;
		case Tarjeta::Tipo::VISA: os << "VISA";
				break;
		case Tarjeta::Tipo::Mastercard: os << "Mastercard";
				break;
		case Tarjeta::Tipo::Maestro: os << "Maestro";
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