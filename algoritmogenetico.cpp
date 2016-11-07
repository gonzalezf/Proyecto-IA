using namespace std;
#include "algoritmogenetico.h"
#include "nodocliente.h"

#define MAX_DOUBLE 1.79769e+300


//CREAR FUNCION QUE TOMA LA POBLACION Y ELIGE LAS MEJORES, PARA LUEGO CREAR CRUZAMIENTOS Y MUTACIONES
//IR REEMPLAZANDO CADA UNA DE ELLAS, CADA SOLUCION TENDRA UNA  "EFICIENCIA"
	



	double AlgoritmoGenetico::EvaluarCalidad(vector<NodoCliente> solucion, int tiempo_servicio){
		int length_solucion = solucion.size();
		double tiempo_total = 0;
		for(int i = 0; i<length_solucion-1;i++){
			NodoCliente cliente_actual = solucion.at(i);
			NodoCliente cliente_siguiente = solucion.at(i+1);

			double x_actual = cliente_actual.getCoordenadaX();
			double y_actual = cliente_actual.getCoordenadaY();

			double x_siguiente = cliente_siguiente.getCoordenadaX();
			double y_siguiente = cliente_siguiente.getCoordenadaY();

			if(cliente_actual.getId()!=0){
				tiempo_total += tiempo_servicio; //se visita un cliente, de lo contrario es un deposito el q se lee
			}
			if(cliente_siguiente.getId()!=0){
				tiempo_total += DistanciaEuclidiana(x_actual,y_actual,x_siguiente,y_siguiente);
			}
		}
		//Agregar el costo de la visita del ultimo nodo
		tiempo_total+= tiempo_servicio;
		return tiempo_total;
	}		
	double AlgoritmoGenetico::DistanciaEuclidiana(double p1x,double p1y, double p2x, double p2y){
	  return sqrt(pow(p2x-p1x,2)+pow(p2y-p1y,2));
	}


    void AlgoritmoGenetico::LeerSolucion(vector<NodoCliente> solucion){
    	int length_vector = solucion.size();
    	for(int i = 0; i<length_vector;i++){
    		NodoCliente nodoActual = solucion.at(i);
    		cout << "ID = " << nodoActual.getId() << "X =" << nodoActual.getCoordenadaX() << "Y = " << nodoActual.getCoordenadaY() << " D = " << nodoActual.getDemanda()<<endl; 
    	}
    }

    void AlgoritmoGenetico::LeerPoblacion(vector<vector<NodoCliente> > poblacion){
    	int length_poblacion = poblacion.size();
    	for(int i = 0; i<length_poblacion; i++){
    		vector<NodoCliente> solucionActual = poblacion.at(i);
    		LeerSolucion(solucionActual);
    	}
    }

    double AlgoritmoGenetico::CostoSolucion(vector<NodoCliente> solucion){
    	return solucion.at(0).getDemanda(); // en la demanda del primer deposito se ecuenntra el costo total de la solucion
    }

    void AlgoritmoGenetico::SetCostoSolucion(vector<NodoCliente> solucion, double costo){
    	NodoCliente firstNode = solucion.at(0);
    	firstNode.setDemanda(costo); //
    	cout <<"Costo actualizado = "<<costo<<endl;

    }

	vector<NodoCliente> AlgoritmoGenetico::CrearRutasFactibles(vector<NodoCliente> clientesInstancia,NodoCliente nodoDeposito,int capacidad_vehiculos,int tiempo_max_ruta,int tiempo_servicio){
		//Se debe considerar tanto la capacidad max del vehiculo, como el tiempo max de ruta.
		int cantidad_almacenada_actual = 0;
		double tiempo_ruta_actual = 0.0;

		int length_clientesInstancia = clientesInstancia.size();
		vector<NodoCliente> solucion_individual_terminada;
		solucion_individual_terminada.push_back(nodoDeposito); //primer elemento

		double coordenadaXDeposito = nodoDeposito.getCoordenadaX();
		double coordenadaYDeposito = nodoDeposito.getCoordenadaY();

		//int k=0;
		for(int i =0; i<length_clientesInstancia;i++){
			//Ir colocando el deposito donde corresponda. 
			NodoCliente ClienteActual = clientesInstancia.at(i);
			double coordenadaXActual =  ClienteActual.getCoordenadaX();
			double coordenadaYActual = ClienteActual.getCoordenadaY();
			/*if(k == 0){
				cout << "PRIMER ELEMENTO " << coordenadaXActual << coordenadaYActual <<endl<<endl;
				k=1;
			}*/
			NodoCliente lastNode = solucion_individual_terminada.back();
			double coordenadaXPasada = lastNode.getCoordenadaX();
			double coordenadaYPasada = lastNode.getCoordenadaY();

			int demanda_cliente_actual = ClienteActual.getDemanda();
			
			int tmp_cantidad_almacenada = cantidad_almacenada_actual + demanda_cliente_actual;
			double tmp_tiempo_ruta_actual = tiempo_servicio + DistanciaEuclidiana(coordenadaXPasada,coordenadaYPasada,coordenadaXActual,coordenadaYActual) + tiempo_ruta_actual;

			if(tmp_cantidad_almacenada > capacidad_vehiculos || tmp_tiempo_ruta_actual > tiempo_max_ruta){
				//No ingresar a la ruta, colocar un 0 antes de ingresarlo.
				cout << "Se Inicia Nueva Ruta en la Solucion" <<endl;
				solucion_individual_terminada.push_back(nodoDeposito);
				solucion_individual_terminada.push_back(ClienteActual);

				tiempo_ruta_actual = DistanciaEuclidiana(coordenadaXDeposito,coordenadaYDeposito,coordenadaXActual,coordenadaYActual)+tiempo_servicio;
				cantidad_almacenada_actual = demanda_cliente_actual;

			}
			else{
				solucion_individual_terminada.push_back(ClienteActual);
				cantidad_almacenada_actual = tmp_cantidad_almacenada;
				tiempo_ruta_actual = tmp_tiempo_ruta_actual;
		
			}
		}

		return solucion_individual_terminada; //Deberia tener los '0' donde corresponde
	} 	




	vector<vector<NodoCliente> > AlgoritmoGenetico::InicializarPoblacion(int tamano_poblacion, const std::string& fileName){

		cout << "Ejecutando InicializarPoblacion"<<endl;
		//Leer archivo, obtener datos importantes como capacidad de vehiculo, tiempo de servicio, crear vector con todos los cliente sy sus posiciones

		int num_clientes;
		int capacidad_vehiculos;
		int tiempo_max_ruta;
		int tiempo_servicio;
		pair<double,double> posicionDeposito;
		 //coordenada y del deposito
		pair<double,double> posicion_cliente_actual;
		int demanda_cliente_actual;
		int idCLiente = 1;
		vector<vector<NodoCliente> > conjuntoRutas; // creo que esto esta mal definido??? no reconoce a NodoCLiente
		//NODO CLIENTE NO DEFINIDO EN EL SCOPE.

		NodoCliente nodoDeposito = NodoCliente();
		vector<NodoCliente> clientesInstancia;
		string line;
  		ifstream myfile (fileName.c_str());
		if (myfile)  // same as: if (myfile.good())
		{
			int num_linea = 0;
			while (getline( myfile, line ))  // same as: while (getline( myfile, line ).good())
      			{
      			istringstream iss(line); //ver si esto funciona
      			if(num_linea == 0){
      				iss >> num_clientes >> capacidad_vehiculos >> tiempo_max_ruta >> tiempo_servicio; //parsear primera linea
      				//cout << "tiempo max  " << tiempo_max_ruta << "tiempo_servicio" << tiempo_servicio << endl;

      			}
      			if(num_linea == 1){
      				iss >> posicionDeposito.first >> posicionDeposito.second;
      				nodoDeposito.setPosicion(posicionDeposito.first,posicionDeposito.second);
      				//cout << "X = " << nodoDeposito.getCoordenadaX() << "Y = " << nodoDeposito.getCoordenadaY() << endl;

      			}
      			else{
      				// parseamos y obtenemos el elemento cliente (su numero y su posicion)

      				iss >> posicion_cliente_actual.first >> posicion_cliente_actual.second >> demanda_cliente_actual; // se obtiene elemento
      				//Una vez parseado llevar estos elementos a un struct
      				NodoCliente nodoActual(idCLiente,posicion_cliente_actual.first,posicion_cliente_actual.second,demanda_cliente_actual);
		    		//cout << "ID = " << nodoActual.getId() << "X =" << nodoActual.getCoordenadaX() << "Y = " << nodoActual.getCoordenadaY() << " D = " << nodoActual.getDemanda() << endl; 

      				clientesInstancia.push_back(nodoActual); //insertar elemento dentro de ese vector
      				//cout << "size = " << clientesInstancia.size() << endl;
      				idCLiente++;
      			}
		      	num_linea++;
		      	}

		    myfile.close();
	    	//Hasta este punto, se obtiene un vector con todos los nodos que representan a los distintos clientes (no esta el nodo deposito)
	    	//La idea es realizar combinaciones aleatorias de ese conjunto, e ir insertando posteriormente el conjunto deposito en la ruta segun las condiciones
	    	//del problema, es decir tiempo de servicio y capacidad del vehiculo. Una vez eso agregarlo a un vector que almacenará el conjunto de rutas total
		    
		    
		    for(int i = 0; i < tamano_poblacion; i++){ // Aqui se generara una solucion individual factible que será parte de la población.
			     //Crear orden aleatorio

		   		//unsigned seed = chrono::system_clock::now().time_since_epoch().count();
			 	random_shuffle (clientesInstancia.begin(), clientesInstancia.end()); //se modifica orden del vector
			 	//LeerSolucion(clientesInstancia);
				vector<NodoCliente> solucion_individual_terminada = CrearRutasFactibles(clientesInstancia,nodoDeposito,capacidad_vehiculos,tiempo_max_ruta,tiempo_servicio); 	
				double costo_solucion_actual = EvaluarCalidad(solucion_individual_terminada,tiempo_servicio);
				SetCostoSolucion(solucion_individual_terminada,costo_solucion_actual);
				conjuntoRutas.push_back(solucion_individual_terminada); //agregar a nuestra poblacion esta solucion factible
		    }

    	}
    	else{
    		cout << "Imposible leer archivo" <<endl<<endl;
    	} 
		cout << "Finalizó InicializarPoblacion "<<endl;

   		return conjuntoRutas;
	}




	//Hay que evaluar y ver si las condiciones se siguen cumpliendo al hacer esta mutacion
	//Las rutas seran de la forma 0 (pos 0) 15 (pos x,y) 14 (pos x,y) 0 2 4 0 15 17 0 1 3 
	/*

	vector<pair<int,pair<double,double>>> AlgoritmoGenetico::Mutacion(vector<pair<int,pair<double,double> > > rutas ){ //toma una ruta, de forma aleatoria cambia alguna variable
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

	int AlgoritmoGenetico::EvaluarCalidad(vector<pair<int,pair<double,double> > > rutas, int tiempo_servicio, pair<double,double> posicionDeposito){
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

	int AlgoritmoGenetico::EscribirMejorSolucion(vector<pair<int,pair<double,double> > > solucion,int costo){
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
*/


	vector<NodoCliente> AlgoritmoGenetico::EncontrarMejorSolucion(vector<vector<NodoCliente> > poblacion, int tiempo_servicio){
		int size_poblacion = poblacion.size();
		double costo_global = MAX_DOUBLE;
		vector<NodoCliente> mejor_solucion_global;		
		vector<NodoCliente> solucion_actual;

		for(int i = 0;i < size_poblacion;i++){
			solucion_actual = poblacion.at(i);
			double costo_actual = EvaluarCalidad(solucion_actual,tiempo_servicio);

			if(costo_actual<costo_global){
				mejor_solucion_global = solucion_actual;
				costo_global = costo_actual;
			}
		}
		return mejor_solucion_global;
	}
/*
	vector<pair<int,pair<double,double> > > AlgoritmoGenetico::RellenarMitad(vector<pair<int,pair<double,double> > > nuevaSolucion, vector<pair<int,pair<double,double> > > solucionVieja, int start,int end){
	
			for(int i = start; i<index+1;i++){
				nuevaSolucion.push_back(solucionVieja.at(i));
			}		
		
	}
	int AlgoritmoGenetico::ContieneElemento(vector<pair<int,pair<double,double> > > solucion, int index, int cliente){
		int length_solucion = solucion.size();
		for(int i = index; i<length_solucion;i++){
			if(get<0>solucion.at(i) == cliente){
				return i; //return el index donde se encuentra
			}
		}
		return -1; //no existe el elemento, no fue encontrado.
	}



	pair<vector<pair<int,pair<double,double> > >,vector<pair<int,pair<double,double> > > > AlgoritmoGenetico::Cruzamiento(vector<pair<int,pair<double,double> > > solucion1,vector<pair<int,pair<double,double> > > solucion2,int num_clientes){
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

	vector<pair<int,pair<double,double> > > AlgoritmoGenetico::MejorCalce(vector<pair<int,pair<double,double> > > solucion, int cliente, pair<double,double> posicionCliente){
		int costo_global = MAX_DOUBLE;
		int size_solucion = solucion.size();
		pair<double,double> posicion_elemento_actual;
		pair<double,double>posicion_elemento_siguiente;
		int index = -1;
		for(int i = 0; i<size_solucion-1;i++){
			posicion_elemento_actual = get<1>solucion.at(i);
			posicion_elemento_siguiente = get<1> solucion.at(i+1);
			
			elemento_actual = get<0>solucion.at(i);
			elemento_siguiente = get<0>solucion.at(i+1);
			int costo_actual;

			if(elemento_siguiente == 0){
				costo_actual = abs(DistanciaEuclidiana(posicion_elemento_actual,posicionCliente))); //nO Necesita ser comparado con elemento siguiente

			}
			else{
				costo_actual = abs(DistanciaEuclidiana(posicion_elemento_actual,posicionCliente)+abs(DistanciaEuclidiana(posicion_elemento_siguiente,posicionCliente)));
			}

			if(costo_actual<costo_global){
				index = i; //Agregar despues de ese index
			}
		}
		//Evaluar si es conveniente ponerla al final de la solucion
		if((DistanciaEuclidiana(solucion.at(size_solucion-1))) < costo_global){
			costo_global = abs(DistanciaEuclidiana(solucion.at(size_solucion-1)));
			index = size_solucion-1;
		}

		vector<pair<int,pair<double,double> > > nuevaSolucion;

		for(int j = 0; j<index+1;j++){
			nuevaSolucion.push_back(solucion.at(j));
		}
		pair<int,pair<double,double> > elemento = pair<cliente,posicionCliente>; // reemplazar por struct despues
		nuevaSolucion.push_back(elemento); // elemento actual
		for(int z = index+1; z <size_solucion;z++){
			nuevaSolucion.push_back(solucion.at(z));
		}
		return nuevaSolucion;
	}

	vector<pair<int,pair<double,double> > > AlgoritmoGenetico::RevisionGramatica(vector<pair<int,pair<double,double> > > solucion){
		int size_solucion = solucion.size();
		for(int i = 0; i<size_solucion-1;i++){
			int elemento_actual = get<0>solucion.at(i);
			int elemento_siguiente = get<0> solucion.at(i+1);
			if(elemento_actual == elemento_siguiente){ //POdria ocurrir tener 2 ocurrencias de '0'
				solucion.erase(solucion.begin()+i);
			}
		}
		return solucion;
	}
*/






