#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include "pedido.hpp"

//class LineaPedido
class LineaPedido {
public:
	explicit LineaPedido(double precio, unsigned cantidad = 1) 
	: precio_venta_{precio}, cantidad_{cantidad} {}
	double precio_venta() const {return precio_venta_;}
	unsigned cantidad() const {return cantidad_;}

private:
	double precio_venta_;
	unsigned cantidad_;
};

std::ostream& operator <<(std::ostream& os, const LineaPedido& lineaPedido);
//fin class LineaPedido

struct OrdenaArticulos {
	bool operator() (Articulo* articulo1, Articulo* articulo2) const
	{
		return articulo1->referencia() < articulo2->referencia();
	}
};

struct OrdenaPedidos {
	bool operator() (Pedido* pedido1, Pedido* pedido2) const
	{
		return pedido1->numero() < pedido2->numero();
	}
};

//class Pedido_Articulo
class Pedido_Articulo {
public:
	//tyoedef
	typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
	typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
	//pedir
	void pedir(Pedido& pedido, Articulo& articulo, double precio, unsigned cantidad=1);
	void pedir(Articulo& articulo, Pedido& pedido, double precio, unsigned cantidad=1);
	
	ItemsPedido& detalle(Pedido& pedido) {return pedidoArticulo_[&pedido];}
	Pedidos& ventas(Articulo& articulo) {return articuloPedido_[&articulo];}
	//mostrar
	void mostrarDetallePedidos(std::ostream& os);
	void mostrarVentasArticulos(std::ostream& os);

private:
	std::map<Pedido*, ItemsPedido, OrdenaPedidos> pedidoArticulo_;
	std::map<Articulo*, Pedidos, OrdenaArticulos> articuloPedido_;
};

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ItemsPedido);
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& pedidos);

#endif

