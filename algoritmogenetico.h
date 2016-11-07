#ifndef _INCLUDE_ALGORITMO_GENETICO_H_
#define _INCLUDE_ALGORITMO_GENETICO_H_
using namespace std; 
#include "helper.h"
#include <vector>
#include <iostream>     // std::cout
#include <algorithm>    // std::shuffle
//mutuacion no deberia tener problemas
//
#include "nodocliente.h"

class AlgoritmoGenetico{
	
	public:

	//INICIALIZAR POBLACION
	vector<vector<NodoCliente> > InicializarPoblacion(int tamano_poblacion, const std::string& fileName);
	vector<NodoCliente> CrearRutasFactibles(vector<NodoCliente> clientesInstancia,NodoCliente nodoDeposito,int capacidad_vehiculos,int tiempo_max_ruta,int tiempo_servicio);

	//OTROS
    double DistanciaEuclidiana(double p1x,double p1y, double p2x,double p2y);
    void LeerSolucion(vector<NodoCliente> solucion);
    void LeerPoblacion(vector<vector<NodoCliente> > poblacion);
	vector<NodoCliente> EncontrarMejorSolucion(vector<vector<NodoCliente> >  poblacion, int tiempo_servicio);
	double EvaluarCalidad(vector<NodoCliente> solucion, int tiempo_servicio);
    void SetCostoSolucion(vector<NodoCliente> solucion, double costo); //dado un costo asigna la deposito, demanda = costo.
    double CostoSolucion(vector<NodoCliente> solucion); // retorna el costo de la solucion

	
/*
	int EvaluarCapacidad(vector<nodoCliente> solucion, int capacidad_vehiculo);
	vector<pair<int,pair<double,double> > > Mutacion(vector<pair<int,pair<double,double> > > rutas );//toma una ruta, de forma aleatoria cambia alguna variable
	int EvaluarCalidad(vector<pair<int,pair<double,double> > > rutas, int tiempo_servicio, pair<double,double> posicionDeposito);
	int EscribirMejorSolucion(vector<pair<int,pair<double,double> > > solucion,int costo);
	pair<vector<pair<int,pair<double,double> > >,double> EncontrarMejorSolucion(vector<vector<pair<int,pair<double,double> > > > poblacion, int tiempo_servicio, pair<double,double> posicionDeposito);
	vector<pair<int,pair<double,double> >  > RellenarMitad(vector<pair<int,pair<double,double> > > nuevaSolucion, vector<pair<int,pair<double,double> > > solucionVieja, int start,int end);
	int ContieneElemento(vector<pair<int,pair<double,double> > > solucion, int index, int cliente);
	pair<vector<pair<int,pair<double,double> > >,vector<pair<int,pair<double,double> > > > Cruzamiento(vector<pair<int,pair<double,double> > > solucion1,vector<pair<int,pair<double,double> > > solucion2,int num_clientes);
	vector<pair<int,pair<double,double> > > MejorCalce(vector<pair<int,pair<double,double> > > solucion, int cliente, pair<double,double> posicionCliente);
	vector<pair<int,pair<double,double> > > RevisionGramatica(vector<pair<int,pair<double,double> > > solucion);
*/

};
#endif 