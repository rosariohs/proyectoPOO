#include <iomanip>

#include "articulo.hpp"

// Constructor Articulo
Articulo::Articulo(const Autores& autores, const Cadena& ref, const Cadena& titulo,const Fecha& fechaPubli, double precio) 
: autores_{autores}, ref_{ref}, titulo_{titulo}, fechaPubli_{fechaPubli}, precio_{precio} {
	if (autores.empty())
		throw Autores_vacios();
} 

std::ostream& operator <<(std::ostream& os, const Articulo& articulo) noexcept {
	os 	<< "[" << articulo.referencia() << "] "
		<< "\"" << articulo.titulo() << "\", de ";

		for (auto i = articulo.autores().begin() ; i != articulo.autores().end() ; i ++) 
		{
			os << (*i)->apellidos();
			if (std::next(i) != articulo.autores().end()) 
			{
				os << ", ";
			} else 
			{
				os << ". ";
			}
		}

	os 	<< articulo.f_publi().anno() << ". "
		<< std::fixed << std::setprecision(2) << articulo.precio() << " €\n\t";
	articulo.impresion_especifica(os);
	return os;
}

void LibroDigital::impresion_especifica(std::ostream& os) const {
	os 	<< "A la venta hasta el " << f_expir_ << ".";
}

void Libro::impresion_especifica(std::ostream& os) const {
	os 	<< n_pag_ << " págs., " << stock_ << " unidades.";
}

void Cederron::impresion_especifica(std::ostream& os) const {
	os 	<< tam_ << " MB, " << stock_ << " unidades.";
}