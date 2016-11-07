using namespace std;
#include "nodocliente.h"


	NodoCliente::NodoCliente(){
		idCliente = -1;
		posicionx = -1;
		posiciony = -1;
		demanda = -1;
	}
	NodoCliente::NodoCliente(int id, double x, double y, int d){
		idCliente = id;
		posicionx = x;
		posiciony = y;
		demanda = d;
	}
	int NodoCliente::getId(){
		return idCliente;
	}
	void NodoCliente::setId(int id){
		idCliente = id;
	}
	double NodoCliente::getCoordenadaX(){
		return posicionx;
	}
	double NodoCliente::getCoordenadaY(){
		return posiciony;
	}

	void NodoCliente::setPosicion(double x, double y){
		posicionx = x;
		posiciony = y;
	}
	int NodoCliente::getDemanda(){
		return demanda;
	}
	void NodoCliente::setDemanda(int d){
		demanda = d;
	}