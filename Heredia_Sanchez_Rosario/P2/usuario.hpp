#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <iostream>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <cstring>

#include "cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"

//class clave
class Clave {
public:
	enum Razon{CORTA, ERROR_CRYPT};
	Clave(const char* contrasenia);
	Cadena clave() const {return contrasenia_;}
	bool verifica(const char* contrasenia) const;

	//class incorrecta
	class Incorrecta {
	public:
		Incorrecta(Razon razon) : razon_{razon} {}
		Razon razon() const {return razon_;}
	private:
		Razon razon_;
	};
	//fin incorrecta

private:
	Cadena contrasenia_;
};
//fin clave


//class usuario
class Usuario {
public:
	typedef std::map<Numero, Tarjeta*> Tarjetas;
	typedef std::unordered_map<Articulo*, unsigned> Articulos;
	typedef std::unordered_set<Cadena> Ids;
	
	//constructores//const
	Usuario(Cadena id, Cadena nombre, Cadena apellidos, Cadena direccion, Clave clave);
	Usuario(const Usuario&) = delete;
	Usuario& operator =(const Usuario&) = delete;
	
	//metodos observadores
	const Cadena& id() const {return id_;}
	const Cadena& nombre() const {return nombre_;}
	const Cadena& apellidos() const {return apellidos_;}
	const Cadena& direccion() const {return direccion_;}
	const Tarjetas& tarjetas() const {return tarjetas_;}
	const Articulos& compra() const {return articulos_;}
	
	void es_titular_de(const Tarjeta& tarjeta);
	void no_es_titular_de(Tarjeta& tarjeta);
	
	void compra(const Articulo& articulo, unsigned cantidad = 1);
	unsigned int n_articulos() const {return articulos_.size();}
	//destructor
	~Usuario();
	
	friend std::ostream& operator <<(std::ostream& os, const Usuario& usuario);

	//class id_duplicado
	class Id_duplicado
	{
	public:
		Id_duplicado(Cadena id) : id_{id} {}
		const Cadena& idd() const {return id_;}
	private:
		Cadena id_;
	};
	//fin id_duplicado

private:
	const Cadena id_, nombre_, apellidos_, direccion_;
	Clave clave_;
	Tarjetas tarjetas_;
	Articulos articulos_;
	static Ids idList_;
};
// fin usuario
void mostrar_carro(std::ostream& os, const Usuario& usuario);


#endif // USUARIO_HPP