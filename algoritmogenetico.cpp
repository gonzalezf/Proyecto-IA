using namespace std;
#include "algoritmogenetico.h"
#include "nodocliente.h"

#define MAX_DOUBLE 1.7976931348623158e+308 /* max value */



//CREAR FUNCION QUE TOMA LA POBLACION Y ELIGE LAS MEJORES, PARA LUEGO CREAR CRUZAMIENTOS Y MUTACIONES
//IR REEMPLAZANDO CADA UNA DE ELLAS, CADA SOLUCION TENDRA UNA  "EFICIENCIA"
	



	//OTROS - SET DE HERRAMIENTAS

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

    	//cout << "ID NODE = "<<firstNode.getCoordenadaX()<< " demanda = "<<firstNode.getDemanda()<<endl;

    	//cout << "Costo Solucion = "<<solucion.at(0).getDemanda()<<endl;
    	return solucion.at(0).getDemanda(); // en la demanda del primer deposito se ecuenntra el costo total de la solucion
    }

    void  AlgoritmoGenetico::SetCostoSolucion(vector<NodoCliente>  solucion, double costo){ ///AQUI ESTA EL ERROR PERO AL PARECER SI FUNCIONA!


	    NodoCliente & firstNode = solucion.at(0);
    	firstNode.setDemanda(costo); //
    	//cout<<"Set Costo Solucion, tenemos "<<firstNode.getDemanda()<<" llega "<<costo<<endl;

    	//cout << "ID = "<<firstNode.getId()<<" x = "<<firstNode.getCoordenadaX()<<" demnada ="<<firstNode.getDemanda()<<endl;
    	//cout <<"Costo ==  "<<costo<<" Aparece"<<firstNode.getDemanda()<<endl; // si funciona

    }

    double AlgoritmoGenetico::CostoPoblacion(vector<vector<NodoCliente> > poblacion){
    	int length_poblacion = poblacion.size();
    	double costo_poblacion = 0.0;
    	for(int i = 0; i<length_poblacion;i++){

    		costo_poblacion += CostoSolucion(poblacion.at(i));
    		//cout << "sumatoria = "<<costo_poblacion<<" i = "<<i<<endl ;
       	}
    	return costo_poblacion;
    }


	//INICIALIZAR POBLACION

	vector<int> AlgoritmoGenetico::GetDatosInstancia( const std::string& fileName){
		vector<int> resultado;
		int num_clientes; 
		int capacidad_vehiculos;
		int tiempo_servicio;
		int tiempo_max_ruta;
		string line;
		ifstream myfile (fileName.c_str());
		if(myfile){
			int num_linea = 0;
			while(getline(myfile,line)){
				istringstream iss(line);
				if(num_linea == 0){
					iss >> num_clientes >> capacidad_vehiculos >> tiempo_max_ruta >> tiempo_servicio;
					num_linea ++;
				}
			}
		}
		resultado.push_back(capacidad_vehiculos);
		resultado.push_back(tiempo_max_ruta);
		resultado.push_back(tiempo_servicio);
		return resultado;
	}

	vector<vector<NodoCliente> > AlgoritmoGenetico::InicializarPoblacion(int tamano_poblacion, const std::string& fileName, int costo_activacion_vehiculo){
		//cout << "Ejecutando InicializarPoblacion"<<endl;
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
				vector<NodoCliente>  solucion_individual_terminada = CrearRutasFactibles(clientesInstancia,nodoDeposito,capacidad_vehiculos,tiempo_max_ruta,tiempo_servicio); 	
				double costo_solucion_actual = EvaluarCalidad(solucion_individual_terminada,tiempo_servicio, capacidad_vehiculos,tiempo_max_ruta,costo_activacion_vehiculo);
				SetCostoSolucion(solucion_individual_terminada,costo_solucion_actual); // está cambiando a la copia


				NodoCliente & firstNode = solucion_individual_terminada.at(0); //nunca olvidar el puntero!!
				firstNode.setDemanda(costo_solucion_actual);

				//cout<<"TAMANO_POBLACION = "<<tamano_poblacion<<" I = "<<i<<endl;
				//cout<<"INICIALIZAR - SET COSTO = "<<costo_solucion_actual<<endl; si funciona

				//cout << "costo solucion antes de entrar a pob "<<solucion_individual_terminada.at(0).getDemanda()<<endl; // aqui falla


				conjuntoRutas.push_back(solucion_individual_terminada); //agregar a nuestra poblacion esta solucion factible
		    }

    	}
    	else{
    		cout << "Imposible leer archivo" <<endl<<endl;
    	} 
		//cout << "Finalizó InicializarPoblacion "<<endl;
    	cout<<"FIN InicializarPoblacion"<<endl;
   		return conjuntoRutas;
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
				//cout << "Se Inicia Nueva Ruta en la Solucion" <<endl;
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

	/*
	///////////////////////////////////////////////////////////////////
	//\\\\\\\\\\\\\\\\\\\\\ETILISMO\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	///////////////////////////////////////////////////////////////////
	*/
	//devuelve el indice de donde esta la peor solucion
	int AlgoritmoGenetico::ObtenerPeorSolucion(vector<vector<NodoCliente> > poblacion){
		double costo_global = 0;
		int length_poblacion = poblacion.size();
		int index = -1; // error
		for(int i = 0; i<length_poblacion;i++){
			vector<NodoCliente> solucion_actual = poblacion.at(0);
			NodoCliente nodo_actual = solucion_actual.at(0);
			double costo_actual = nodo_actual.getDemanda();

			if(costo_actual > costo_global){
				index = i;
				costo_global = costo_actual; //update
			}
		}
		return index;
	}
	//AL PARECER ESTA FUNCION ESTA BIEN - ULTIMA REVISION 3:31
	//DETERMINA LAS K Mejores soluciones de una población, luego las devuelve. 
	//TIENE PINTA DE TIRAR ERROR, PERO NO LOGRO PILLAR DONDE!
	vector<vector<NodoCliente> > AlgoritmoGenetico::ObtenerMejoresSoluciones(vector<vector<NodoCliente> > poblacion, int k){
		int length_poblacion = poblacion.size();
		//cout<<"obtener mejores soluciones algoritmo - size pob = "<<poblacion.size()<<" k = "<<k<<endl;// esta bien esto
		vector<vector<NodoCliente> > resultado;
		int cantidad_almacenada = 0;
		double costo_minimo_actual = MAX_DOUBLE;
		int index = -1; 
		int index_2 = -1;
		for(int i = 0; i<length_poblacion;i++){
			vector<NodoCliente> solucion_actual = poblacion.at(i);
			NodoCliente deposito_actual = solucion_actual.at(0); // en la demanda de este elemento esta almacenado el costo
			// funciona bien esto cout <<"ID DEBIESE SER 0 PERO ES = "<<deposito_actual.getId()<<" costo = "<<deposito_actual.getDemanda()<<endl;
			double costo_actual = deposito_actual.getDemanda();

			if(resultado.size()>1){
				//cout<<"I = "<<i<<" ALMACENADO = "<<cantidad_almacenada<<"COSTO SOL MAS ALTO = "<<resultado.at(ObtenerPeorSolucion(resultado)).at(0).getDemanda()<<endl;  
			}
			if(costo_actual<costo_minimo_actual){
				if(cantidad_almacenada<k){ //revisar si efectivamente devuelve las k mejores.
					//Hay espacio para almacenar esta solución sin problemas.
					resultado.push_back(solucion_actual);
					if(cantidad_almacenada==k-1){
						int index3 = ObtenerPeorSolucion(resultado);
						costo_minimo_actual = resultado.at(index3).at(0).getDemanda();
					}
				}
				else{
					
					//Ingresar a la solución pero borrar la de mayor costo.
					//Ordenar de menor a mayor costo, eliminar la peor, agregar la actual

					index = ObtenerPeorSolucion(resultado);
					//cout <<"PREVIO REEMPLAZO = "<<resultado.at(index).at(0).getDemanda()<<endl;
					resultado[index] = solucion_actual; //update // SIEMPRE CONSIDERA QUE ESTE ES EL PEOR, PERO NO ESTOY SEGURO SI ES REALMENTE ASI
					//cout <<"UPDATE REEMPLAZO = "<<resultado.at(index).at(0).getDemanda()<<endl;

					index_2 = ObtenerPeorSolucion(resultado);
					costo_minimo_actual = resultado.at(index_2).at(0).getDemanda(); //
					//cout<<"PEOR = "<<resultado.at(index_2).at(0).getDemanda()<<endl; EL problema es que

				}
				cantidad_almacenada++;
			}
		}
		//cout <<"OBTENER MEJORES SOLUCIONES ENTREGA NUMERO RESULTADOS = "<<resultado.size()<<endl;
		return resultado;
	}

	//Esta funcion es más costosa, revisa la calidad de la solucion entera, no la demnada del primer elemento.
	vector<NodoCliente> AlgoritmoGenetico::EncontrarMejorSolucion(vector<vector<NodoCliente> > poblacion, int tiempo_servicio, int capacidad_vehiculos, int tiempo_max_ruta, int costo_activacion_vehiculo){
		int size_poblacion = poblacion.size();
		double costo_global = MAX_DOUBLE;
		vector<NodoCliente> mejor_solucion_global;		
		vector<NodoCliente> solucion_actual;

		for(int i = 0;i < size_poblacion;i++){
			solucion_actual = poblacion.at(i);
			double costo_actual = EvaluarCalidad(solucion_actual,tiempo_servicio, capacidad_vehiculos, tiempo_max_ruta, costo_activacion_vehiculo);

			if(costo_actual<costo_global){
				mejor_solucion_global = solucion_actual;
				costo_global = costo_actual;
			}
		}
		return mejor_solucion_global;
	}

	//DETERMINA EL COSTO DE LA SOLUCION, este valor luego es seteado en la demanda del deposito para acceder mas rapido. Devuelve -1 si solucion no es factible	
		double AlgoritmoGenetico::EvaluarCalidad(vector<NodoCliente> solucion, int tiempo_servicio, int capacidad_vehiculos, int tiempo_max_ruta,int costo_activacion_vehiculo){
		int length_solucion = solucion.size();
		double tiempo_total_solucion = 0;
		double tiempo_ruta_actual = 0; // evaluar factibilidad
		int cantidad_almacenada = 0; // evaluar factibilidad

		NodoCliente cliente_actual;
		NodoCliente cliente_siguiente;
		for(int i = 0; i<length_solucion-1;i++){
			cliente_actual = solucion.at(i);
			cliente_siguiente = solucion.at(i+1);

			double x_actual = cliente_actual.getCoordenadaX();
			double y_actual = cliente_actual.getCoordenadaY();

			int demanda_cliente_actual = cliente_actual.getDemanda();

			double x_siguiente = cliente_siguiente.getCoordenadaX();
			double y_siguiente = cliente_siguiente.getCoordenadaY();


			if(cliente_actual.getId()!=0){ // visitamos ese nodo
				tiempo_total_solucion += tiempo_servicio; //se visita un cliente, de lo contrario es un deposito el q se lee
				tiempo_ruta_actual += tiempo_servicio;
				cantidad_almacenada += demanda_cliente_actual;				
			}
			else{ // cliente_actual.getId() == 0
				tiempo_total_solucion += costo_activacion_vehiculo; // se agrega un nuevo vehiculo, se suma su costo
				tiempo_ruta_actual = 0.0;
				cantidad_almacenada = 0;
			}

			if(cliente_siguiente.getId()!=0){
				tiempo_total_solucion += DistanciaEuclidiana(x_actual,y_actual,x_siguiente,y_siguiente);
				tiempo_ruta_actual+= DistanciaEuclidiana(x_actual,y_actual,x_siguiente,y_siguiente);
			}
			if(tiempo_ruta_actual > tiempo_max_ruta || cantidad_almacenada > capacidad_vehiculos){
				//cout << "SOLUCION INFACTIBLE"; #qui
				return -1; // SOLUCION INFACTIBLE!
			}
		}
		//Agregar el costo de la visita del ultimo nodo
		//IF ULTIMO NODO ID != 0
		if(cliente_siguiente.getId()!=0){
			tiempo_total_solucion+= tiempo_servicio; // EL TIEMPO de camino ya se agrego
			tiempo_ruta_actual+=tiempo_servicio;
			cantidad_almacenada += cliente_siguiente.getDemanda();
		}

		if(tiempo_ruta_actual> tiempo_max_ruta || cantidad_almacenada > capacidad_vehiculos){
			//cout << "SOLUCION INFACTIBLE" <<endl; #qui
			return -1;
		}

		//cout << "YAY! SOLUCION FACTIBLE! COSTO TOTAL = "<<tiempo_total_solucion<<endl; #qui
		return tiempo_total_solucion;
	}	

	//FUNCION REVISADA, DEBERIA ESTAR TODO OK
	vector<NodoCliente> AlgoritmoGenetico::ObtenerSolucionPorRuleta(vector<vector<NodoCliente> > poblacion,double costo_poblacion){
		vector<NodoCliente> resultado; 
		double limite_inferior = 0.0;
		double limite_superior = 0.0;
		int length_poblacion = poblacion.size();
		//Crear número aleatorio
        double random_number =  (rand() % (101))/100.0;
        //cout<<"RANDOM NUMBER RULETA = "<<random_number<<endl; FUNCIONA OBTIENE CADA VEZ UN NUMERO DISTINTO.

		for(int i = 0; i<length_poblacion;i++){
			vector<NodoCliente> solucion_actual = poblacion.at(i);
			NodoCliente nodo_actual = solucion_actual.at(0);
			double costo_actual = nodo_actual.getDemanda();
			//cout << "Costo actual = "<<costo_actual<<" Costo Poblacion = "<<costo_poblacion<<endl;
			double porcentaje_solucion = costo_actual/costo_poblacion;

			limite_superior+= porcentaje_solucion;

			if(random_number>= limite_inferior && random_number <= limite_superior){
				//cout << "Encontro solucion por ruleta, i = "<<i << "random_number = "<<random_number<<endl; #qui
				return solucion_actual;
			}
			limite_inferior = limite_superior;
		}
		return resultado;
	}	




	//Hay que evaluar y ver si las condiciones se siguen cumpliendo al hacer esta mutacion
	//Las rutas seran de la forma 0 (pos 0) 15 (pos x,y) 14 (pos x,y) 0 2 4 0 15 17 0 1 3 
	

	vector<NodoCliente> AlgoritmoGenetico::Mutacion(vector<NodoCliente> solucion ){ //toma una ruta, de forma aleatoria cambia alguna variable
		//Random between 2 numbers int randNum = rand()%(max-min + 1) + min;
		
		//cout<<"COSTO Mutacion pre "<<CostoSolucion(solucion)<<endl;
		int solucion_length = solucion.size();
		
		int idPrimerElemento =0;
		int idSegundoElemento = 0;

		int indexPrimerElemento =0;
		int indexSegundoElemento = 0;

		while(idPrimerElemento ==0 || idSegundoElemento==0){ // Queremos cambiar clientes, no 'depositos', por eso esta comprobacion
			if(idPrimerElemento == 0){
				indexPrimerElemento = rand()%(solucion_length);
			}
			if(idSegundoElemento == 0){
				indexSegundoElemento = rand()%(solucion_length);
			}
			idPrimerElemento = solucion.at(indexPrimerElemento).getId(); 
			idSegundoElemento = solucion.at(indexSegundoElemento).getId();

		}

		//SWAP entre variables!
		NodoCliente  tmp = NodoCliente(); // var tmp


		NodoCliente & nodo1 = solucion.at(indexPrimerElemento);
		NodoCliente & nodo2 = solucion.at(indexSegundoElemento);

		//cout << "Mutacion Id  pre swap nodo 1 = "<<nodo1.getId(); #qui

		//Guardar datos temporales de nodo 1 en tmp

		tmp.setDemanda(nodo1.getDemanda());
		tmp.setId(nodo1.getId());
		tmp.setPosicion(nodo1.getCoordenadaX(),nodo1.getCoordenadaY()); // debiese funcionar, comprobar

		//Guardar datos de nodo 2 en nodo 1

		nodo1.setDemanda(nodo2.getDemanda());
		nodo1.setId(nodo2.getId());
		nodo1.setPosicion(nodo2.getCoordenadaX(),nodo2.getCoordenadaY());

		//guardar datos de tmp en nodo 2

		nodo2.setDemanda(tmp.getDemanda());
		nodo2.setId(tmp.getId());
		nodo2.setPosicion(tmp.getCoordenadaX(),tmp.getCoordenadaY());


		//cout << "Mutacion Id nodo 1 = "<<nodo1.getId() << "ID tmp despues swap = "<<tmp.getId()<<endl;

		//cout << "Mutacion Id  post swap nodo 1 = "<<nodo1.getId()<<endl; #qui #importante
		double nuevo_costo = CostoSolucion(solucion); // segun esto el costo no cambia, entonces (? ) no esta mutando?
		NodoCliente & deposito = solucion.at(0);
		deposito.setDemanda(nuevo_costo);

		//cout <<"POST MUTACION  se tiene = "<<solucion.at(0).getDemanda()<<" deberia ser "<<nuevo_costo<<endl;

		return solucion;
	}




	vector<NodoCliente> AlgoritmoGenetico::RellenarMitad(vector<NodoCliente> solucionNueva,vector<NodoCliente> solucionVieja, int start,int end){
		

			for(int i = start; i<end+1;i++){
				solucionNueva.push_back(solucionVieja.at(i));
			}		
			return solucionNueva;
		

	}


	int AlgoritmoGenetico::ContieneElemento(vector<NodoCliente > solucion, int index, int cliente){
		int length_solucion = solucion.size();
		for(int i = index; i<length_solucion;i++){
			if(solucion.at(i).getId() == cliente){
				return i; //return el index donde se encuentra
			}
		}
		return -1; //no existe el elemento, no fue encontrado.
	}


	//Entrega 2 hijos! a partir de 2 padres
	vector<vector<NodoCliente> > AlgoritmoGenetico::Cruzamiento(vector<NodoCliente > solucion1,vector<NodoCliente > solucion2){
		//Cada mitad desde el inicio al punto de corte se intercambian
		//Los valores que se intercambian, si estan en la segunda mitad de donde llegan se eliminan de ahi
		//Los valores que se intercambian, si no aparecen en la nueva solucion, uno x uno se colocan en el mejor ajuste
		int length_solucion1 = solucion1.size();
		int length_solucion2 = solucion2.size();
		int punto_corte = int(min(length_solucion1,length_solucion2)/2) -1; // ahora tenemos un nuevo indice, hasta este valor incluyendolo se intercambian mitades

		 

		vector<NodoCliente> nuevasolucion1;
		vector<NodoCliente> nuevasolucion2;

		vector<NodoCliente> nuevasolucion1_rellenada_mitad = RellenarMitad(nuevasolucion1, solucion2,0,punto_corte); //Intercambiar hasta el punto de corte.
		vector<NodoCliente> nuevasolucion2_rellenada_mitad =RellenarMitad(nuevasolucion2,solucion1,0,punto_corte); 
		//revisar si los indices que recibe rellenar mitad son correctos!
		vector<NodoCliente> solucion_rellenada_final_2 = RellenarMitad(nuevasolucion2,solucion2,punto_corte+1,length_solucion2-1); //copiar mitad restante
		vector<NodoCliente> solucion_rellenada_final_1 = RellenarMitad(nuevasolucion1,solucion1,punto_corte+1,length_solucion1-1); 

		vector<NodoCliente>  s2;
		vector<NodoCliente> s1;
		//Por cada elemento que este en la primera mitad, eliminarlo de la segunda y calzarlo donde mejor calce.
		for(int i = 0; i<punto_corte+1;i++){
			int idCliente1 = solucion_rellenada_final_1.at(i).getId();
			int idCliente2 = solucion_rellenada_final_2.at(i).getId();


			double x_1 = solucion_rellenada_final_1.at(i).getCoordenadaX();
			double y_1 = solucion_rellenada_final_1.at(i).getCoordenadaY();

			double x_2 = solucion_rellenada_final_2.at(i).getCoordenadaX();
			double y_2 = solucion_rellenada_final_2.at(i).getCoordenadaY();

			double demanda_c1 = solucion_rellenada_final_1.at(i).getDemanda();
			double demanda_c2 = solucion_rellenada_final_2.at(i).getDemanda();

			int resultado1 = ContieneElemento(solucion_rellenada_final_1,punto_corte+1,idCliente1);
			int resultado2 = ContieneElemento(solucion_rellenada_final_2,punto_corte+1,idCliente2);
			//Aqui hay algo malo, por cada elemento meh

			if(resultado1 != -1 && idCliente1 !=0){ // significa que contiene el elemento, quitar de la pila. No se eliminan 0 
				solucion_rellenada_final_1.erase(solucion_rellenada_final_1.begin() + resultado1); // removido del vector
				

				solucion_rellenada_final_1 = MejorCalce(solucion_rellenada_final_1,idCliente1,x_1,y_1,demanda_c1);
			}
			if(resultado2 != -1 && idCliente2 != 0){ // significa que contiene el elemento, quitar de la pila y 
				solucion_rellenada_final_2.erase(solucion_rellenada_final_2.begin() + resultado2); // removido del vector
				solucion_rellenada_final_2 = MejorCalce(solucion_rellenada_final_2,idCliente2,x_2,y_2,demanda_c2);
				//VER SI SOLUCION_RELLENADA_FINAL_2 SE REDEFINE CADA VEZ..la idea es ir quitando los elementos incompatibles!!	

			}
		}
		


		//Eliminar 2 0 concecutivos, o un 0 al final (Revision de gramatica)
		vector<NodoCliente> s1_f = RevisionGramatica(solucion_rellenada_final_1);
		vector<NodoCliente> s2_f = RevisionGramatica(solucion_rellenada_final_2);
		


		double costo_solucion_final_hijo1 = CostoSolucion(s1_f);
		SetCostoSolucion(s1_f,costo_solucion_final_hijo1);
		//cout << "SE TIENE  EN CRUZAMIENTO D= "<<s1_f.at(0).getDemanda()<<" deberia ser = "<<costo_solucion_final<<endl;
		
		double costo_solucion_final_hijo2 = CostoSolucion(s2_f);
		SetCostoSolucion(s2_f,costo_solucion_final_hijo2);

		vector<vector<NodoCliente> > resultado;
		resultado.push_back(s1_f);
		resultado.push_back(s2_f);
		//cout << "CrossOver terminado"<<endl; #qui
		return resultado; // arreglo de dos elementos, hay dos nuevas soluciones!

	}

	vector<NodoCliente > AlgoritmoGenetico::MejorCalce(vector<NodoCliente > solucion, int cliente, double coordenada_x_cliente, double coordenada_y_cliente, double demanda){
		double costo_global = MAX_DOUBLE;
		int size_solucion = solucion.size();

		double x_elemento_actual;
		double y_elemento_actual;

		double x_elemento_siguiente;
		double y_elemento_siguiente;


		int index = -1;
		for(int i = 0; i<size_solucion-1;i++){

			x_elemento_actual = solucion.at(i).getCoordenadaX();
			y_elemento_actual = solucion.at(i).getCoordenadaY();

			x_elemento_siguiente = solucion.at(i+1).getCoordenadaX();
			y_elemento_siguiente = solucion.at(i+1).getCoordenadaY();

			
			int id_elemento_siguiente = solucion.at(i+1).getId();
			
			double costo_actual;

			if(id_elemento_siguiente == 0){
				costo_actual = DistanciaEuclidiana(x_elemento_actual,y_elemento_actual,coordenada_x_cliente,coordenada_y_cliente); //nO Necesita ser comparado con elemento siguiente

			}
			else{
				costo_actual = DistanciaEuclidiana(x_elemento_actual,y_elemento_actual,coordenada_x_cliente,coordenada_y_cliente)+DistanciaEuclidiana(x_elemento_siguiente,y_elemento_siguiente,coordenada_x_cliente,coordenada_y_cliente);
			}

			if(costo_actual<costo_global){
				index = i; //Agregar despues de ese index
				costo_global = costo_actual; //update
			}
		}
		//Evaluar si es conveniente ponerla al final de la solucion
		double x_ultimo_elemento = solucion.at(size_solucion-1).getCoordenadaX();
		double y_ultimo_elemento = solucion.at(size_solucion-1).getCoordenadaY();

		if(DistanciaEuclidiana(x_ultimo_elemento,y_ultimo_elemento,coordenada_x_cliente,coordenada_y_cliente) < costo_global){
			costo_global = DistanciaEuclidiana(x_ultimo_elemento,y_ultimo_elemento,coordenada_x_cliente,coordenada_y_cliente);
			index = size_solucion-1;
		}

		vector<NodoCliente > nuevaSolucion; // esta se retorna.

		for(int j = 0; j<index+1;j++){ //revisar si el index esta correcto
			nuevaSolucion.push_back(solucion.at(j));
		}

		NodoCliente elemento(cliente,coordenada_x_cliente,coordenada_y_cliente,demanda);
		nuevaSolucion.push_back(elemento); // elemento actual
		for(int z = index+1; z <size_solucion;z++){
			nuevaSolucion.push_back(solucion.at(z));
		}
		return nuevaSolucion;
	}


	vector<NodoCliente > AlgoritmoGenetico::RevisionGramatica(vector<NodoCliente> solucion){
		int size_solucion = solucion.size();
		for(int i = 0; i<size_solucion-1;i++){
			int id_elemento_actual = solucion.at(i).getId();
			
			int id_elemento_siguiente = solucion.at(i+1).getId();

			if(id_elemento_actual == id_elemento_siguiente){ //POdria ocurrir tener 2 ocurrencias de '0'
				solucion.erase(solucion.begin()+i);
			}
		}
		return solucion;
	}
	/*
	/////////////////////////////////////////////////////////////////////////////////////
	/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ENCONTRAR MEJOR SOLUCION \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	/////////////////////////////////////////////////////////////////////////////////////
	*/


	int AlgoritmoGenetico::EscribirMejorSolucion(vector<NodoCliente > solucion,double costo){
		int solucion_length = solucion.size();

		ofstream myfile;
  		myfile.open ("mejor_solucion.txt"); // colocar el nombre de la instancia!
  		int num_rutas = 1;
  		int id_cliente_actual = -1;
  		bool start = true;
  		for(int i = 0; i<solucion_length;i++){
  			id_cliente_actual = solucion.at(i).getId();
  			if(id_cliente_actual == 0){
  				if(!start){
  					myfile<<endl;
  				}
  				myfile <<"ROUTE #"<<num_rutas<<" : ";
  				num_rutas++;
  				start = false;
  			}
  			if(id_cliente_actual !=0){
  				myfile << id_cliente_actual <<" ";
  			}
  		}
 		myfile << "COST "<<costo<<endl;
  		myfile.close();
  		return 0;
	}









