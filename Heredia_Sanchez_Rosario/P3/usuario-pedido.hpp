#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

#include <iostream>
#include "pedido.hpp"

//class Usuario_Pedido
class Usuario_Pedido {
public:
	typedef std::set<Pedido*> Pedidos;
	void asocia(Usuario& usuario, Pedido& pedido) {usuarioPedido_[&usuario].insert(&pedido); pedidoUsuario_[&pedido] = &usuario;}
	void asocia(Pedido& pedido, Usuario& usuario) {asocia(usuario, pedido);}
	const Pedidos pedidos(Usuario& usuario) {return usuarioPedido_.find(&usuario)->second;}
	const Usuario* cliente(Pedido& pedido) {return pedidoUsuario_.find(&pedido)->second;}

private:
	std::map<Usuario*, Pedidos> usuarioPedido_;
	std::map<Pedido*, Usuario*> pedidoUsuario_;
};

#endif 