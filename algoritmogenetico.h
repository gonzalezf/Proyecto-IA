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
	vector<int> GetDatosInstancia( const std::string&  path);
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
	vector<NodoCliente> UnirSoluciones(vector<NodoCliente> solucion1, vector<NodoCliente> solucion2);
	vector<NodoCliente> EliminarCeros(vector<NodoCliente> solucion);
	NodoCliente ObtenerNodoDeposito(vector<NodoCliente> solucion);
	vector<NodoCliente> EliminarRepetidos(vector<NodoCliente> solucion);
	//INICIALIZAR POBLACION
	vector<vector<NodoCliente> > InicializarPoblacion(int tamano_poblacion, const std::string& fileName, int costo_activacion_vehiculo);
	vector<NodoCliente> CrearRutasFactibles(vector<NodoCliente> clientesInstancia,NodoCliente nodoDeposito,int capacidad_vehiculos,int tiempo_max_ruta,int tiempo_servicio);

	//ETILISMO
	vector<vector<NodoCliente> > ObtenerMejoresSoluciones(vector<vector<NodoCliente> > poblacion, int k);
	vector<NodoCliente>EncontrarMejorSolucion(vector<vector<NodoCliente> > poblacion, int tiempo_servicio, int capacidad_vehiculos, int tiempo_max_ruta, int costo_activacion_vehiculo); // No la estoy ocupando
	double EvaluarCalidad(vector<NodoCliente> solucion, int tiempo_servicio, int capacidad_vehiculos, int tiempo_max_ruta, int costo_activacion_vehiculo);
	int ObtenerPeorSolucion(vector<vector<NodoCliente> > poblacion); //devuelve el index de donde esta la peor solucion de una poblacion;

	//SELECCION
	vector<NodoCliente> ObtenerSolucionPorRuleta(vector<vector<NodoCliente> > poblacion,double costo_poblacion);

	//TRANSFORMACION
	vector<NodoCliente> Mutacion(vector<NodoCliente> solucion );//toma una ruta, de forma aleatoria cambia alguna variable
	vector<vector<NodoCliente> > Cruzamiento(vector<NodoCliente > solucion1,vector<NodoCliente > solucion2);

	//INFORMAR MEJOR SOLUCION
	int EscribirMejorSolucion(vector<NodoCliente > solucion,double costo);

	//UNA VEZ MUTADO HAY QUE REASIGNAR EL COSTO Y VER SI SON FACTIBLES!

/*
	int EscribirMejorSolucion(vector<pair<int,pair<double,double> > > solucion,int costo);
*/

	//OTROS



};

#endif 