#include <iomanip> 

#include "pedido-articulo.hpp"

//asocia pedido y articulo
void Pedido_Articulo::pedir(Pedido& pedido, Articulo& articulo, double precio, unsigned cantidad)
{
	LineaPedido linea(precio, cantidad);
    pedidoArticulo_[&pedido].insert(std::make_pair(&articulo, linea));
    articuloPedido_[&articulo].insert(std::make_pair(&pedido, linea));
}

//asocia articulo y pedido
void Pedido_Articulo::pedir(Articulo& articulo, Pedido& pedido, double precio, unsigned cantidad)
{
	pedir(pedido, articulo, precio, cantidad);
}

void Pedido_Articulo::mostrarDetallePedidos(std::ostream& os)
{
	double total=0;
    for(const auto& i : pedidoArticulo_) 
    {
        os << i.second << std::endl;
        total= total + i.first->total();
    }

    os << std::endl << std::fixed << std::setprecision(2) << total << " €" << std::endl;
}

void Pedido_Articulo::mostrarVentasArticulos(std::ostream& os)
{
	for(const auto& i : articuloPedido_)
    {
        os << i.second << std::endl;
    }
}

std::ostream& operator <<(std::ostream& os, const LineaPedido& lineaPedido)
{
	os << std::fixed << std::setprecision(2) << lineaPedido.precio_venta() << " €\t" << lineaPedido.cantidad();
	return os;
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& itemsPedido)
{
	double total=0;
    
    os  << "  PVP\tCantidad\tArtículo \n"
        << std::setw(67) << std::setfill('=') << "\n";
    
    for (const auto& i : itemsPedido) 
    {
        os  << i.second.precio_venta() 
            << " €\t" 
            << i.second.cantidad() << "\t\t"
            << "[" << i.first->referencia() << "] \"" 
            << i.first->titulo() << "\""
            << std::endl;
        total += i.second.precio_venta() * i.second.cantidad();
    }

    os  << std::setw(67) << std::setfill('=') << "\n"
        << "Total: " << std::fixed << std::setprecision(2)
        << total << std::endl;
    
    return os;
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& pedidos)
{
	double total=0;
    int cantidades=0;

    os  << "[Pedidos: " << pedidos.size() << "]\n"
        << std::setw(67) << std::setfill('=') << "\n"
        << "  PVP\tCantidad\tFecha de venta\n"
        << std::setw(67) << std::setfill('=') << "\n";

    for (const auto& i : pedidos) 
    {
        os  << i.second.precio_venta() << " €\t"
            << i.second.cantidad() << "\t\t"
            << i.first->fecha() << std::endl;
        total = total + i.second.precio_venta() * i.second.cantidad();
        cantidades = cantidades + i.second.cantidad();
    }

    os  << std::setw(67) << std::setfill('=') << "\n"
        << std::fixed
        << std::setprecision(2) << total << " €  " << cantidades <<std::endl;

    return os;
}
