using namespace std;
#include <iostream> 
#include "helper.h"
#include <vector>
#include <algorithm>

//mutuacion no deberia tener problemas

class AlgoritmoGenetico{
	
	public:
	
	struct ruta{ // Será un resultado
	  double fitness; // valor de la función objetivo
	  int cantidad_vehiculos;
	  std::vector<int> ruta;
	};

	vector<ruta> InicializarPoblacion(int tamano_poblacion, const std::string& fileName);

	vector<pair<int,pair<double,double>>> Mutacion(vector<pair<int,pair<double,double>>> ruta); //recibe y devuelve una ruta de la forma 0 (x,y) 1 (x,y)
	int EvaluarCalidad(vector<pair<int,pair<double,double>>>,int tiempo_servicio, pair<double,double> posicionDeposito); //Entrega valor de funcion objetivo de una solucion
	int EscribirMejorSolucion(vector<pair<int,pair<double,double>>>,int costo); //retorna 0 si  no hubo problema al escribir solucion
	void Cruzamiento(vector<pair<int,pair<double,double>>> solucion1,vector<pair<int,pair<double,double>>> solucion2,int num_clientes);
	vector<pair<int,pair<double,double>>> MejorSolucion(vector<vector<pair<int,pair<double,double>>>> poblacion);




};