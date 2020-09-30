#include <iomanip>

#include "articulo.hpp"

// Constructor Articulo
Articulo::Articulo(const Cadena ref, const Cadena titulo, Fecha fechaPubli, double precio, unsigned ejemplares) 
: ref_{ref}, titulo_{titulo}, fechaPubli_{fechaPubli}, precio_{precio}, ejemplares_{ejemplares} {} 

std::ostream& operator <<(std::ostream& os, const Articulo& articulo)
{
	os 	<< "[" << articulo.referencia() << "] "
		<< "\"" << articulo.titulo() << "\", "
		<< articulo.f_publi().anno() << ". "
		<< std::fixed << std::setprecision(2) << articulo.precio() << " €";
	return os;
}
