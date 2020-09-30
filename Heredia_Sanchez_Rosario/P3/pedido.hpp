#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "usuario.hpp"

class Usuario_Pedido;
class Pedido_Articulo;

//class Pedido
class Pedido {
public:
Pedido(Usuario_Pedido& u_p, Pedido_Articulo& p_a, Usuario& usuario, Tarjeta const& tarjeta, const Fecha& fecha = Fecha());
int numero() const {return num_;}
Tarjeta const* tarjeta() const {return tarjeta_;}
Fecha fecha() const {return fecha_;}
double total() const {return total_;}
static int n_total_pedidos() {return n_pedidos;}

//class Vacio
class Vacio {
public:
	Vacio(Usuario& usuario) : usuario_{&usuario} {}
	Usuario const& usuario() const {return *usuario_;}
private:
	const Usuario* usuario_;
};
//fin class Vacio

//class Impostor
class Impostor {
public:
	Impostor(Usuario& usuario) : usuario_{&usuario} {}
	Usuario const& usuario() const {return *usuario_;}
private:
	const Usuario* usuario_;
};
//fin class Impostor

//class SinStock
class SinStock {
public:
	SinStock(Articulo* const articulo) : articulo_{articulo} {}
	Articulo const& articulo() const {return *articulo_;}
private:
	const Articulo* articulo_;
};
//fin class SinStock

private:
	int num_;
	Tarjeta const*  tarjeta_;
	Fecha fecha_;
	double total_;
	static int n_pedidos;
};

std::ostream& operator <<(std::ostream& os, const Pedido& pedido);

#endif
