#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include <iostream>
#include "cadena.hpp"
#include "fecha.hpp"

// class articulo
class Articulo {
public:
	Articulo(Cadena ref, Cadena titulo, Fecha fechaPubli, double precio = 0, unsigned ejemplares = 0);
	const Cadena& referencia() const {return ref_;}
	const Cadena& titulo() const {return titulo_;}
	const Fecha& f_publi() const {return fechaPubli_;}
	double precio() const {return precio_;}
	double& precio() {return precio_;}
	unsigned stock() const {return ejemplares_;}
	unsigned& stock() {return ejemplares_;}
private:
	const Cadena ref_, titulo_;
	Fecha fechaPubli_;
	double precio_;
	unsigned ejemplares_;
};
// fin articulo

std::ostream& operator <<(std::ostream& os, const Articulo& articulo);

#endif // ARTICULO_HPP