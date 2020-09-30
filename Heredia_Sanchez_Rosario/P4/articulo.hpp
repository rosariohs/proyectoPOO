#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include <iostream>
#include <set>
#include "cadena.hpp"
#include "fecha.hpp"

//class Autor
class Autor {
public:
	Autor(const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion) : nombre_{nombre}, apellidos_{apellidos}, direccion_{direccion} {}
	
	const Cadena& nombre() const noexcept {return nombre_;};
	const Cadena& apellidos() const noexcept {return apellidos_;}
	const Cadena& direccion() const noexcept {return direccion_;}

private:
	Cadena nombre_, apellidos_, direccion_;
};

// class articulo
class Articulo {
public:
	class Autores_vacios{};
	typedef std::set<Autor*> Autores;
	Articulo(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fechaPubli, double precio);
	const Cadena& referencia() const noexcept {return ref_;}
	const Cadena& titulo() const noexcept {return titulo_;}
	const Fecha& f_publi() const noexcept {return fechaPubli_;}
	double precio() const noexcept {return precio_;}
	double& precio() noexcept {return precio_;}
	const Autores& autores() const noexcept { return autores_; };
	virtual void impresion_especifica(std::ostream& os) const = 0;
	virtual ~Articulo(){};

private:
	const Autores autores_;
	const Cadena ref_, titulo_;
	Fecha fechaPubli_;
	double precio_;
	
};
// fin articulo

std::ostream& operator <<(std::ostream& os, const Articulo& articulo) noexcept;

//class ArticuloAlmacenable
class ArticuloAlmacenable : public Articulo {
public:
	ArticuloAlmacenable(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fechaPubli, double precio, unsigned ejemplares = 0)
	: Articulo(autores, ref, titulo, fechaPubli, precio), stock_{ejemplares} {}
	unsigned stock() const {return stock_;}
	unsigned& stock() {return stock_;}
	virtual ~ArticuloAlmacenable(){}

protected:
	unsigned stock_;
};

//class LibroDigital
class LibroDigital : public Articulo {
public:
	LibroDigital(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fechaPubli, double precio, const Fecha& f_expir)
	: Articulo(autores, ref, titulo, fechaPubli, precio), f_expir_{f_expir} {}
	const Fecha& f_expir() const noexcept {return f_expir_;}
	void impresion_especifica(std::ostream& os) const;

private:
	const Fecha f_expir_;
};

//class Libro
class Libro : public ArticuloAlmacenable {
public:
	Libro(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fechaPubli, double precio, unsigned n_pag, unsigned ejemplares = 0)
	: ArticuloAlmacenable(autores, ref, titulo, fechaPubli, precio, ejemplares), n_pag_{n_pag} {}
	unsigned n_pag() const noexcept {return n_pag_;}
	void impresion_especifica(std::ostream& os) const;

private:
	const unsigned n_pag_;
};

//class Cederron
class Cederron : public ArticuloAlmacenable {
public:
	Cederron(const Autores& autores, const Cadena& ref, const Cadena& titulo, const Fecha& fechaPubli, double precio, unsigned tam, unsigned ejemplares = 0)
	: ArticuloAlmacenable(autores, ref, titulo, fechaPubli, precio, ejemplares), tam_{tam} {}
	unsigned tam() const noexcept {return tam_;}
	void impresion_especifica(std::ostream& os) const;

private:
	const unsigned tam_;
};

#endif // ARTICULO_HPP