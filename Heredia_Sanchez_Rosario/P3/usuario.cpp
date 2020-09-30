#include <unistd.h>
#include <cstdlib>
#include <iomanip>
#include <random>

#include "usuario.hpp"

// Constructor Clave
Clave::Clave(const char* contrasenia)
{
	if(strlen(contrasenia) < 5) throw Clave::Incorrecta(CORTA);
  	const char *const saltChar = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  	std::random_device random;
	std::uniform_int_distribution<unsigned> dist(0, 63);
	char salt[2] = { saltChar[dist(random)], saltChar[dist(random)] };
  	if(crypt(contrasenia,salt) == 0) throw Clave::Incorrecta(ERROR_CRYPT);
  	contrasenia_ = crypt(contrasenia,salt);
}

bool Clave::verifica(const char* contrasenia) const
{
	return !strcmp(crypt(contrasenia, contrasenia_.c_str()), contrasenia_.c_str());
}

Usuario::Ids Usuario::idList_;

Usuario::Usuario(const Cadena id, const Cadena nombre, const Cadena apellidos, const Cadena direccion,  Clave clave) 
: id_{id}, nombre_{nombre}, apellidos_{apellidos}, direccion_{direccion}, clave_{clave}
{
	if (!idList_.insert(id_).second)
		throw Id_duplicado(id_);
}

void Usuario::es_titular_de(const Tarjeta& tarjeta)
{
	if (tarjeta.titular() == this)
		tarjetas_[tarjeta.numero()] = const_cast<Tarjeta*>(&tarjeta);
}

void Usuario::no_es_titular_de(Tarjeta& tarjeta)
{
	tarjetas_.erase(tarjeta.numero());
}

void Usuario::compra(const Articulo& articulo, unsigned cantidad)
{
	if (cantidad == 0) 
		articulos_.erase(const_cast<Articulo*>(&articulo));
	else 
		articulos_[const_cast<Articulo*>(&articulo)] = cantidad;
}

Usuario::~Usuario()
{
	for (auto& i : tarjetas_) {
        i.second->anula_titular();
	}
    idList_.erase(id_);
}

std::ostream& operator <<(std::ostream& os, const Usuario& usuario)
{
	os 	<< usuario.id_ << " [" << usuario.clave_.clave() << "] " << usuario.nombre_ << usuario.apellidos_ << std::endl 
		<< usuario.direccion_ << std::endl 
		<< "Tarjetas:" << std::endl;

    for (auto const& tarjeta : usuario.tarjetas_)
        os << *tarjeta.second << std::endl;

    return os;
}

void mostrar_carro(std::ostream& os, const Usuario& usuario)
{
	os << "Carrito de compra de " << usuario.id() << " [Artículos: " << usuario.n_articulos() << "]" << std::endl;

    if (usuario.n_articulos() > 0) {
    	os << " Cant. Artículo" << std::endl
    	   << std::setw(60) << std::setfill('=') << '\n' << std::setfill(' ');
    	for (auto const& item : usuario.compra())
    	    os << std::setw(4) << item.second << std::setw(4) << *item.first << std::endl;
	}

    os << std::endl;
}