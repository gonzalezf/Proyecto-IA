using namespace std;
#include "nodocliente.h"


//ESTA ES MI CLASE
	NodoCliente::NodoCliente(){
		idCliente = 0;
		posicionx = 0;
		posiciony = 0;
		demanda = 0;
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