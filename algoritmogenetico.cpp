using namespace std;
#include "algoritmogenetico.h"
#include "nodocliente.h"

#define MAX_DOUBLE 1.79769e+300



	

/*
	int AlgoritmoGenetico::EvaluarCapacidad(vector<nodoCliente> solucion, int capacidad_vehiculo){
		int cantidad_almacenada = 0;
		int length_solucion  = solucion.size();
		for(int i = 0; i<length_solucion;i++){
			int cliente_actual = solucion.at(i).num_cliente;
			pair<double,double> posicion_cliente_actual = solucion.at(i).posicion;
			int demanda_cliente_actual = solucion.at(i).demanda;

			if(cliente_actual == 0){
				cantidad_almacenada = 0;
			}
			else{
				cantidad_almacenada += demanda_cliente_actual;
			}
			if(cantidad_almacenada>capacidad_vehiculo){
				return -1; //Se excedio capacidad, solucion no es factible!
			}

		}


		return 0; // Es factible
	}
*/

	double AlgoritmoGenetico::DistanciaEuclidiana(pair<double,double> p1, pair<double,double> p2){
	  return sqrt(pow(p2.first-p1.first,2)+pow(p2.second-p1.second,2));
	}

	vector<vector<NodoCliente> > AlgoritmoGenetico::InicializarPoblacion(int tamano_poblacion, const std::string& fileName){

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
		vector<vector<NodoCliente> > conjuntoRutas;


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

      			}
      			if(num_linea == 1){
      				iss >> posicionDeposito.first >> posicionDeposito.second;
      			}
      			else{
      				// parseamos y obtenemos el elemento cliente (su numero y su posicion)

      				iss >> posicion_cliente_actual.first >> posicion_cliente_actual.second >> demanda_cliente_actual; // se obtiene elemento
      				//Una vez parseado llevar estos elementos a un struct
      				//
      				NodoCliente nodoActual = NodoCliente(idCLiente,posicion_cliente_actual.first,posicion_cliente_actual.second,demanda_cliente_actual);

      				clientesInstancia.push_back(nodoActual); //insertar elemento dentro de ese vector
      				idCLiente++;
      			}
		      	num_linea++;
		      	}

		    myfile.close();
	    	//Hasta este punto, se obtiene un vector con todos los nodos que representan a los distintos clientes (no esta el nodo deposito)
	    	//La idea es realizar combinaciones aleatorias de ese conjunto, e ir insertando posteriormente el conjunto deposito en la ruta segun las condiciones
	    	//del problema, es decir tiempo de servicio y capacidad del vehiculo. Una vez eso agregarlo a un vector que almacenará el conjunto de rutas total
		    /*
		    nodoCliente nodoDeposito = {0, posicionDeposito,0}; //el id del deposito y su demanda es 0
		    for(int i = 0; i < tamano_poblacion; i++){ // Aqui se generara una solucion individual factible que será parte de la población.
			     //Crear orden aleatorio

		   		//unsigned seed = chrono::system_clock::now().time_since_epoch().count();
			 	random_shuffle (clientesInstancia.begin(), clientesInstancia.end()); //se modifica orden del vector

				vector<nodoCliente> solucion_individual_terminada = CrearRutasFactibles(clientesInstancia,nodoDeposito,capacidad_vehiculos,tiempo_max_ruta,tiempo_servicio); 	
				conjuntoRutas.push_back(solucion_individual_terminada); //agregar a nuestra poblacion esta solucion factible
		    }*/

    	}
    	else{
    		cout << "Imposible leer archivo" <<endl<<endl;
    	} 
   		return conjuntoRutas;
	}

/*
	vector<nodoCliente> AlgoritmoGenetico::CrearRutasFactibles(vector<nodoCliente> clientesInstancia,nodoCliente nodoDeposito,int capacidad_vehiculos,int tiempo_max_ruta,int tiempo_servicio){
		//Se debe considerar tanto la capacidad max del vehiculo, como el tiempo max de ruta.
		int cantidad_almacenada_actual = 0;
		int tiempo_ruta_actual = 0;

		int length_clientesInstancia = clientesInstancia.size();
		vector<nodoCliente> solucion_individual_terminada;
		solucion_individual_terminada.push_back(nodoDeposito); //primer elemento


		for(int i =0; i<length_clientesInstancia;i++){
			//Ir colocando el deposito donde corresponda. 
			nodoCliente ClienteActual = clientesInstancia.at(i);
			nodoCliente lastNode = solucion_individual_terminada.back();

			int demanda_cliente_actual = ClienteActual.demanda;
			
			int tmp_cantidad_almacenada = cantidad_almacenada_actual + demanda_cliente_actual;
			int tmp_tiempo_ruta_actual = tiempo_servicio + abs(DistanciaEuclidiana(ClienteActual,lastNode)) + tiempo_ruta_actual;

			if(tmp_cantidad_almacenada > capacidad_vehiculos || tmp_tiempo_ruta_actual > tiempo_max_ruta){
				//No ingresar a la ruta, colocar un 0 antes de ingresarlo.
				solucion_individual_terminada.push_back(nodoDeposito);
				solucion_individual_terminada.push_back(ClienteActual);

				tiempo_ruta_actual = abs(DistanciaEuclidiana(nodoDeposito,ClienteActual))+tiempo_servicio;
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




	//Hay que evaluar y ver si las condiciones se siguen cumpliendo al hacer esta mutacion
	//Las rutas seran de la forma 0 (pos 0) 15 (pos x,y) 14 (pos x,y) 0 2 4 0 15 17 0 1 3 
	

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

	pair<vector<pair<int,pair<double,double> > >,double> AlgoritmoGenetico::EncontrarMejorSolucion(vector<vector<pair<int,pair<double,double> > > > poblacion, int tiempo_servicio, pair<double,double> posicionDeposito){
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






