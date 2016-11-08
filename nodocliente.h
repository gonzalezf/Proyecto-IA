#ifndef _INCLUDE_NODO_CLIENTE_H_
#define _INCLUDE_NODO_CLIENTE_H_
#include <iostream>     // std::cout

using namespace std;


class NodoCliente{

	private:
		int idCliente;
		double posicionx;
		double posiciony;
		double demanda;

	public:
		NodoCliente();
		NodoCliente(int id, double x, double y, double d);
		int getId();
		void setId(int id);
		double getCoordenadaX();
		double getCoordenadaY();
		void setPosicion(double x, double y);
		double getDemanda();
		void setDemanda(double d);


};

#endif //_INCLUDE_NODO_CLIENTE_H_

