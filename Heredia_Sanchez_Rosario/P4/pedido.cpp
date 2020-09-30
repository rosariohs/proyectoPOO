#include <iomanip>
#include "pedido.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"

int Pedido::n_pedidos=0;

//constructor
Pedido::Pedido(Usuario_Pedido& u_p, Pedido_Articulo& p_a, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& fecha) 
: num_{n_pedidos+1}, tarjeta_{&tarjeta}, fecha_{fecha}, total_{0}
{
	//vacio
	if(usuario.n_articulos() == 0)
		throw Vacio(usuario);
	//impostor
	if(usuario.nombre() != tarjeta.titular()->nombre() || usuario.apellidos() != tarjeta.titular()->apellidos())
		throw Impostor(usuario);
	//caducada
	if(tarjeta.caducidad() < fecha)
		throw Tarjeta::Caducada(tarjeta.caducidad());
	//desactivada
	if(!tarjeta.activa())
		throw Tarjeta::Desactivada();

	// comprobar que hay stock suficiente
	auto carro = usuario.compra();
	for (auto i = carro.begin() ; i != carro.end() ; i ++) {
		if (ArticuloAlmacenable* articulo = dynamic_cast<ArticuloAlmacenable*> (i->first)) {
			if (articulo->stock() < i->second){
				// encuentra articulo con stock insuficiente. vacia carrito, lanza excepcion
				const_cast<Usuario::Articulos&>(usuario.compra()).clear();
				throw SinStock(i->first);
			} 
		} else {
			if (LibroDigital* libro = dynamic_cast<LibroDigital*> (i->first)) {
				if (libro->f_expir() < fecha){
					usuario.compra(*i->first, 0);
				}
			}
		}
	}

	if(usuario.compra().empty())
		throw Vacio(usuario);

	//asocia el usuario y el pedido
	u_p.asocia(*this, usuario);

	//asocia pedido, articulos 
	for(const auto& i: usuario.compra()) 
	{
		p_a.pedir(*i.first, *this, i.first->precio(), i.second);
		if (ArticuloAlmacenable* articulo = dynamic_cast<ArticuloAlmacenable*> (i.first)) 
		{
			articulo->stock() = articulo->stock() - i.second;
		}
		//calcula el total
		total_ = total_ + i.first->precio() * i.second;
	}

	//se vacia el carrito y se incrementa el contador de pedidos
	const_cast<Usuario::Articulos&>(usuario.compra()).clear();
	
	n_pedidos++;
}

std::ostream& operator <<(std::ostream& os, const Pedido& pedido) 
{
	os <<"Núm. pedido: "<< pedido.numero() << std::endl
	   <<"Fecha:       "<< pedido.fecha() << std::endl
	   <<"Pagado con:    "<< pedido.tarjeta()->tipo() << " n.º: " << pedido.tarjeta()->numero() << std::endl
	   <<"Importe:     "<< std::fixed << std::setprecision(2) << pedido.total() << " €" << std::endl;

	return os;
}
