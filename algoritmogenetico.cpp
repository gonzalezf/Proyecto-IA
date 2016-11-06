using namespace std;
#include "algoritmogenetico.h"
#define MAX_DOUBLE 1.79769e+308

	vector<ruta> AlgoritmoGenetico::InicializarPoblacion(int tamano_poblacion, const std::string& fileName){
		int num_vehiculos;
		int capacidad_vehiculos;
		int tamano_max_ruta;
		int tiempo_servicio;
		double deposito_x; //coordenada x del deposito
		double deposito_y; //coordenada y del deposito
		int num_vehiculo_actual;
		int vehiculo_actual_x;
		int vehiculo_actual_y;


		vector<ruta> conjuntoRutas;
		cout <<"Imprimiendo desde algoritmo genetico"<<endl;

		string line;
  		ifstream myfile (fileName.c_str());
		if (myfile)  // same as: if (myfile.good())
		{
			int num_linea = 0;
			while (getline( myfile, line ))  // same as: while (getline( myfile, line ).good())
      			istringstream iss(line);
      			{
      			if(num_linea == 0){
      				iss >> num_vehiculos >> capacidad_vehiculos >> tamano_max_ruta >> tiempo_servicio; //parsear primera linea

      			}
      			if(num_linea == 1){
      				iss >> deposito_x >> deposito_y;
      			}
      			else{


      			}
		      	num_linea++;

		      	}
	    myfile.close();
    	}
    	else cout << "Imposible leer archivo" <<endl<<endl;

    	return conjuntoRutas;

	}

	//Hay que evaluar y ver si las condiciones se siguen cumpliendo al hacer esta mutacion
	//Las rutas seran de la forma 0 (pos 0) 15 (pos x,y) 14 (pos x,y) 0 2 4 0 15 17 0 1 3 
	

	vector<pair<int,pair<double,double>>> AlgoritmoGenetico::Mutacion(vector<pair<int,pair<double,double>>> rutas ){ //toma una ruta, de forma aleatoria cambia alguna variable
		//Random between 2 numbers int randNum = rand()%(max-min + 1) + min;
		int rutas_length = rutas.size();
		int PrimerElemento =0;
		int SegundoElemento = 0;
		pair<double,double> = posicionPrimerElemento;
		pair<double,double> = posicionSegundoElemento;
		int indexPrimerElemento =0;
		int indexSegundoElemento = 0;

		while(PrimerElemento ==0 || SegundoElemento==0){ 
			if(PrimerElemento == 0){
				indexPrimerElemento = rand()%(rutas_length);
			}
			if(SegundoElemento == 0){
				indexSegundoElemento = rand()%(rutas_length);
			}
			PrimerElemento = get<0>rutas.at(indexPrimerElemento);
			posicionPrimerElemento = get<1>rutas.at(indexPrimerElemento);
			SegundoElemento = get<0>rutas.at(indexSegundoElemento);
			posicionSegundoElemento = get<1>rutas.at(indexSegundoElemento);

		}

		//SWAP entre variables!
		int tempElemento = PrimerElemento; 
		pair<double,double> tempPosicion = posicionPrimerElemento;
		rutas.at(indexPrimerElemento) =  pair<get<0>ruta.at(indexSegundoElemento),get<1>rutas.at(indexSegundoElemento));
		rutas.at(indexSegundoElemento) = pair<PrimerElemento,tempPosicion>;
		return rutas;
	}

	//OBservacion: La distancia tiene la misma prioridad que el tiempo de servicio 

	int EvaluarCalidad(vector<pair<int,pair<double,double>>> rutas, int tiempo_servicio, pair<double,double> posicionDeposito){
		int costo = 0;
		int rutas_length = rutas.size();

		for(int i =0; i<rutas_length;i++){
			//Descomponer 
			int cliente = get<0>rutas.at(i);
			pair<double,double> posicion_actual = get<1>rutas.at(i); // esto no funcionaria , arreglar
			if(cliente !=0){
				costo += tiempo_servicio; // tiempo gastado en atender a este cliente
				costo += DistanciaEuclidiana(posicionDeposito,posicion_actual); 
			}
		}
		return costo;
	}

	int EscribirMejorSolucion(vector<pair<int,pair<double,double>>> solucion,int costo){
		int solucion_length = solucion.size();

		ofstream myfile;
  		myfile.open ("mejor_solucion.txt");
  		int num_rutas = 1;
  		int cliente_actual = -1;
  		bool start = true;
  		for(int i = 0, i<solucion_length;i++){
  			cliente_actual = get<0>solucion.at(i);
  			if(cliente_actual == 0){
  				if(!start){
  					myfile<<endl;
  				}
  				myfile <<"ROUTE #"<<num_rutas<<" : ";
  				num_rutas++;
  				start = false;
  			}
  			if(cliente_actual !=0){
  				myfile << cliente_actual <<" ";
  			}
  		}
 		myfile << "COST "<<costo<<endl;
  		myfile.close();
  		return 0;
	}

	pair<vector<pair<int,pair<double,double>>>,double> MejorSolucion(vector<vector<pair<int,pair<double,double>>>> poblacion, int tiempo_servicio, pair<double,double> posicionDeposito){
		int size_poblacion = poblacion.size();
		double costo_global = MAX_DOUBLE;
		vector<pair<int,pair<double,double>> mejor_solucion_global;		
		vector<pair<int,pair<double,double>> solucion_actual;
		for(int i = 0;i < size_poblacion;i++){
			solucion_actual = poblacion.at(i);
			costo_actual = EvaluarCalidad(solucion_actual,tiempo_servicio,posicionDeposito);

			if(costo_actual<costo_global){
				mejor_solucion_global = solucion_actual;
				costo_global = costo_actual;
			}
		}
		return pair <mejor_solucion_global,costo_global>;
	}

	vector<pair<int,pair<double,double>>>> RellenarMitad(vector<pair<int,pair<double,double>>> nuevaSolucion, vector<pair<int,pair<double,double>>> solucionVieja, int start,int end){
	
			for(int i = start; i<index+1;i++){
				nuevaSolucion.push_back(solucionVieja.at(i));
			}		
		
	}
	int ContieneElemento(vector<pair<int,pair<double,double>>> solucion, int index, int cliente){
		int length_solucion = solucion.size();
		for(int i = index; i<length_solucion){
			if(get<0>solucion.at(i) == cliente){
				return i; //return el index donde se encuentra
			}
		}
		return -1; //no existe el elemento, no fue encontrado.
	}



	pair<vector<pair<int,pair<double,double>>>,vector<pair<int,pair<double,double>>>> Cruzamiento(vector<pair<int,pair<double,double>>> solucion1,vector<pair<int,pair<double,double>>> solucion2,int num_clientes){
		//Cada mitad desde el inicio al punto de corte se intercambian
		//Los valores que se intercambian, si estan en la segunda mitad de donde llegan se eliminan de ahi
		//Los valores que se intercambian, si no aparecen en la nueva solucion, uno x uno se colocan en el mejor ajuste

		int length_solucion1 = solucion1.size();
		int length_solucion2 = solucion2.size();
		int punto_corte = int(min(length_solucion1,length_solucion2)/2) -1; // ahora tenemos un nuevo indice, hasta este valor incluyendolo se intercambian mitades

		vector<pair<int,pair<double,double>>> nuevasolucion1;
		vector<pair<int,pair<double,double>>> nuevasolucion2;

		RellenarMitad(nuevasolucion2,solucion1,0,punto_corte); //Intercambiar hasta el punto de corte.
		RellenarMitad(nuevasolucion1,solucion2,0,punto_corte); 

		RellenarMitad(nuevasolucion2,solucion2,punto_corte+1,length_solucion2-1); //copiar mitad restante
		RellenarMitad(nuevasolucion1,solucion1,punto_corte+1,length_solucion1-1); 

		//Por cada elemento que este en la primera mitad, eliminarlo de la segunda y calzarlo donde mejor calce.
		for(int i = 0; i<punto_corte+1;i++){
			int cliente1 = get<0>solucion1.at(i);
			int cliente2 = get<0>solucion2.at(i);
			pair<double,double> posicionCliente1 = get<1>solucion1.at(i);
			pair<double,double> posicionCliente2 = get<1>solucion2.at(i);

			int resultado1 = ContieneElemento(solucion1,punto_corte+1,cliente1);
			int resultado2 = ContieneElemento(solucion2,punto_corte+1,cliente2);
			if(resultado1 != -1){ // significa que contiene el elemento, quitar de la pila y 
				solucion1.erase(solucion1.begin() + resultado1); // removido del vector
				solucion1 = MejorCalce(solucion1,cliente1,posicionCliente1);
			}
			if(resultado2 != -1){ // significa que contiene el elemento, quitar de la pila y 
				solucion2.erase(solucion1.begin() + resultado1); // removido del vector
				solucion2 = MejorCalce(solucion2,cliente2,posicionCliente2);
			}
		}


		//Eliminar 2 0 concecutivos, o un 0 al final (Revision de gramatica)
		nuevasolucion1 = RevisionGramatica(nuevasolucion1);
		nuevasolucion2 = RevisionGramatica(nuevasolucion2);

		return pair<nuevasolucion1,nueva2>;

	}

	vector<pair<int,pair<double,double>>> MejorCalce(vector<pair<int,pair<double,double>>> solucion, int cliente, pair<double,double> posicionCliente){
		int costo_global = MAX_DOUBLE;
		int size_solucion = solucion.size();
		pair<double,double> posicion_elemento_actual;
		pair<double,double>posicion_elemento_siguiente;
		int index = -1;
		for(int i = 0; i<size_solucion-1;i++){
			posicion_elemento_actual = get<1>solucion.at(i);
			posicion_elemento_siguiente = get<1> solucion.at(i+1);
			int costo_actual = abs(DistanciaEuclidiana(posicion_elemento_actual,posicionCliente)+abs(DistanciaEuclidiana(posicion_elemento_actual,posicionCliente)));
			if(costo_actual<costo_global){
				index = i; //Agregar despues de ese index
			}
		}
		//Evaluar si es conveniente ponerla al final de la solucion
		if(abs(DistanciaEuclidiana(solucion.at(size_solucion-1)))<costo_global){
			costo_global = abs(DistanciaEuclidiana(solucion.at(size_solucion-1)));
			index = size_solucion-1;
		}

		vector<pair<int,pair<double,double>>> nuevaSolucion;

		for(int j = 0; j<index+1;j++){
			nuevaSolucion.push_back(solucion.at(j));
		}
		nuevaSolucion.push_back(pair<cliente,posicionCliente>); // elemento actual
		for(int z = index+1; z <size_solucion;<z++){
			nuevaSolucion.push_back(solucion.at(z));
		}
		return nuevaSolucion;
	}
	vector<pair<int,pair<double,double>>> RevisionGramatica(vector<pair<int,pair<double,double>>> solucion){
		int size_solucion = solucion.size();
		for(int i = 0; i<size_solucion-1;i++){
			elemento_actual = get<0>solucion.at(i);
			elemento_siguiente = get<0> solucion.at(i+1);
			if(elemento_actual == elemento_siguiente){ //POdria ocurrir tener 2 ocurrencias de '0'
				solucion.erase(solucion.begin()+i);
			}
		}
		return solucion;
	}







