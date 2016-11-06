using namespace std;
#include <iostream> 
#include "helper.h"
#include <vector>
#include <algorithm>

//mutuacion no deberia tener problemas

class AlgoritmoGenetico{
	
	public:
	


	struct nodoCliente{
		int num_cliente;
		pair<double,double> posicion;
		int demanda;
	}	

	vector<ruta> InicializarPoblacion(int tamano_poblacion, const std::string& fileName);


	//OPERADORES
	vector<pair<int,pair<double,double>>> Mutacion(vector<pair<int,pair<double,double>>> ruta); //recibe y devuelve una ruta de la forma 0 (x,y) 1 (x,y)
	pair<vector<pair<int,pair<double,double>>>,vector<pair<int,pair<double,double>>>> Cruzamiento(vector<pair<int,pair<double,double>>> solucion1,vector<pair<int,pair<double,double>>> solucion2,int num_clientes);

	//Evaluar Calidad
	int EvaluarCalidad(vector<pair<int,pair<double,double>>>,int tiempo_servicio, pair<double,double> posicionDeposito); //Entrega valor de funcion objetivo de una solucion
	
	//ETILISMO
	int EscribirMejorSolucion(vector<pair<int,pair<double,double>>> solucion,int costo); //retorna 0 si  no hubo problema al escribir solucion
	pair<vector<pair<int,pair<double,double>>>,double> EncontrarMejorSolucion(vector<vector<pair<int,pair<double,double>>>> poblacion, int tiempo_servicio, pair<double,double> posicionDeposito);

	//OTROS
	vector<pair<int,pair<double,double>>> MejorCalce(vector<pair<int,pair<double,double>>> solucion, int cliente, pair<double,double> posicionCliente);
	vector<pair<int,pair<double,double>>> RevisionGramatica(vector<pair<int,pair<double,double>>> solucion);
	int ContieneElemento(vector<pair<int,pair<double,double>>> solucion, int index, int cliente);
	vector<pair<int,pair<double,double>>>> RellenarMitad(vector<pair<int,pair<double,double>>> nuevaSolucion, vector<pair<int,pair<double,double>>> solucionVieja, int start,int end);




};