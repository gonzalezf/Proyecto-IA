#ifndef _INCLUDE_ALGORITMO_GENETICO_H_
#define _INCLUDE_ALGORITMO_GENETICO_H_
#include "helper.h"
#include <vector>
#include <iostream>     // std::cout
#include <algorithm>    // std::shuffle
#include <limits>
#include <cstddef>
#include <cfloat>
#include <stdlib.h>
#include <time.h>
#include "nodocliente.h"
using namespace std; 

class AlgoritmoGenetico{
	
	public:

	//SET DE HERRAMIENTAS
	double DistanciaEuclidiana(double p1x,double p1y, double p2x,double p2y);
    void LeerSolucion(vector<NodoCliente> solucion);
    void LeerPoblacion(vector<vector<NodoCliente> > poblacion);
    void SetCostoSolucion(vector<NodoCliente> solucion, double costo); //dado un costo asigna la deposito, demanda = costo.
    double CostoSolucion(vector<NodoCliente> solucion); // retorna el costo de la solucion
    double CostoPoblacion(vector<vector<NodoCliente> > poblacion);
	vector<NodoCliente > RevisionGramatica(vector<NodoCliente> solucion);
	vector<NodoCliente> RellenarMitad(vector<NodoCliente > nuevaSolucion, vector<NodoCliente> solucionVieja, int start,int end);
	int ContieneElemento(vector<NodoCliente > solucion, int index, int cliente); //Retorna -1 si no encuentra el elemento, de lo contrario devuelve el indice.
	vector<NodoCliente > MejorCalce(vector<NodoCliente > solucion, int cliente, double coordenada_x_cliente, double coordenada_y_cliente, double demanda);

	
	//INICIALIZAR POBLACION
	vector<vector<NodoCliente> > InicializarPoblacion(int tamano_poblacion, const std::string& fileName);
	vector<NodoCliente> CrearRutasFactibles(vector<NodoCliente> clientesInstancia,NodoCliente nodoDeposito,int capacidad_vehiculos,int tiempo_max_ruta,int tiempo_servicio);

	//ETILISMO
	vector<vector<NodoCliente> > ObtenerMejoresSoluciones(vector<vector<NodoCliente> > poblacion, int k);
 	vector<NodoCliente> EncontrarMejorSolucion(vector<vector<NodoCliente> >  poblacion, int tiempo_servicio);
	double EvaluarCalidad(vector<NodoCliente> solucion, int tiempo_servicio);
	int ObtenerPeorSolucion(vector<vector<NodoCliente> > poblacion); //devuelve el index de donde esta la peor solucion de una poblacion;

	//SELECCION
	vector<NodoCliente> ObtenerSolucionPorRuleta(vector<vector<NodoCliente> > poblacion,double costo_poblacion);

	//TRANSFORMACION
	vector<NodoCliente> Mutacion(vector<NodoCliente> solucion );//toma una ruta, de forma aleatoria cambia alguna variable
	vector<vector<NodoCliente> > Cruzamiento(vector<NodoCliente > solucion1,vector<NodoCliente > solucion2);



/*
	int EvaluarCapacidad(vector<nodoCliente> solucion, int capacidad_vehiculo);
	int EvaluarCalidad(vector<pair<int,pair<double,double> > > rutas, int tiempo_servicio, pair<double,double> posicionDeposito);
	int EscribirMejorSolucion(vector<pair<int,pair<double,double> > > solucion,int costo);
	pair<vector<pair<int,pair<double,double> > >,double> EncontrarMejorSolucion(vector<vector<pair<int,pair<double,double> > > > poblacion, int tiempo_servicio, pair<double,double> posicionDeposito);
	int ContieneElemento(vector<pair<int,pair<double,double> > > solucion, int index, int cliente);
	pair<vector<pair<int,pair<double,double> > >,vector<pair<int,pair<double,double> > > > Cruzamiento(vector<pair<int,pair<double,double> > > solucion1,vector<pair<int,pair<double,double> > > solucion2,int num_clientes);
	vector<pair<int,pair<double,double> > > MejorCalce(vector<pair<int,pair<double,double> > > solucion, int cliente, pair<double,double> posicionCliente);
*/

	//OTROS



};

#endif 