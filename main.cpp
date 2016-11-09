using namespace std;
#include "algoritmogenetico.h"
#include "nodocliente.h"

/* Para compilar
g++ -Wall main.cpp helper.cpp algoritmogenetico.cpp nodocliente.cpp
./a.out vrpnc1
*/

//ENCONTRAR MEJOR SOLUCION
/*/////////////////////////////////////////////////////////////
//\\\\\\\\\\\\\\\\\DESCRIPCION ALGORITMO\\\\\\\\\\\\\\\\\\\\
///////////////////////////////////////////////////////////////*/


//Se crea una poblacion inicial aleatoria. Cada solucion es factible.
// Cada solucion es evaluada, se elijen NUM_ELITISMO mejores soluciones y son parte de sig generacion
// Por seleccion de ruleta, se escogen 2 soluciones para crear Mutacion o CrossOver. Se realiza CANTIDAD_TRANSFORMACIONES veces
//Si solucion transformada es factible y es mejor que la peor solucion de generacion actual, se ingresa en sig generacion.
//EL proceso de escoger las K mejores soluciones de una generacion, transformarlas y agregarlas a una sig generacion, se realiza NUM_GENERACIONES:STOP veces
// De la ultima generacion se selecciona la mejor y se escribe en "mejor_resultado.txt"




//TAREAS
// COMPROBAR EFECTIVAMENTE QUE MUTA Y NO SOLAMENTE LO HACE FRENTE A UNA COPIA.
//comprobar efectivamente que cruaza
//agregar costo vehiculos - check
//transformaciones son factibles, - check 
//setear costo. - check

/*/////////////////////////////////////////////////////////////
//\\\\\\\\\\\\\\\\\Definición de parametros\\\\\\\\\\\\\\\\\\\\
///////////////////////////////////////////////////////////////*/
#define PXOVER 0.8 //Porcentaje crossover  - Mutación sera (1 - PXOVER)
#define TAMANO_POBLACION 10000 
#define NUM_ELITISMO 100 // cantidad de "mejores soluciones que se seleccionan de una poblacion "
#define NUM_GENERACIONES_STOP 50 // Criterio de Termino
#define COSTO_ACTIVACION_VEHICULO 20 
#define CANTIDAD_TRANSFORMACIONES 30
#define NUM_MAX_ITERACIONES 5000 // EN mutacion busca continuamente por posibles soluciones, a veces no existen mas. Esto nos saca del bucle




int main(int argc, char **argv){

  srand(time(0));

  cout << "Algoritmo Genetico con 2 operadores para Open Vehicle Routing Problem" << endl;
  cout << "Felipe González  P." << endl << endl;

  if(argc<2){
    cout << "Faltan parámetros." << endl << endl;
    cout << "Para ejecutar escribir" << endl;
    cout << "> make INSTANCE={instancia}" << endl << endl;
    cout << "Debe existir el archivo ./instances/{instancia}.txt" << endl << endl;
    cout << "Para más información, lea el archivo Readme.md" << endl << endl;
    return 0;
  } 

  //Definición de clases
  Helper helper;
  AlgoritmoGenetico AG;
  NodoCliente N; // LA DECLARO Y FUNCIONA, EN EL MAIN NO HAY PROBLEMA.
  

  stringstream p;
  string path = "";

  //Construir path para leer archivo
  p << "./instances/";
  p << argv[1];
  p <<".txt";
  path = p.str();


  if(!helper.ArchivoExiste(path)){
    cout << "No Existe la instancia " << argv[1] << endl;
    cout << "Archivo leido desde " << path <<endl<<endl;
    return 0;
  }
  else{
    cout << "Instacia" << argv[1] << " Existe" << endl;
    cout << "Archivo es leidos desde " << path <<endl<<endl;
    
  }


//OBTENER DATOS INSTANCIA
vector<int> datos_instancia = AG.GetDatosInstancia(path);
int tiempo_servicio_instancia = datos_instancia.at(2);
int capacidad_vehiculos_instancia = datos_instancia.at(0);
int tiempo_max_ruta_instancia = datos_instancia.at(1);

/*/////////////////////////////////////////////////////////////
//\\\\\\\\\\\\\\\\\INICIALIZAR POBLACION \\\\\\\\\\\\\\\\\\\\\\
///////////////////////////////////////////////////////////////*/

  
  vector<vector<NodoCliente> > poblacionInicial  = AG.InicializarPoblacion(TAMANO_POBLACION,path,COSTO_ACTIVACION_VEHICULO); // Se obtiene población con la cual trabajar
  vector<NodoCliente> peor_solucion_inicial = poblacionInicial.at(AG.ObtenerPeorSolucion(poblacionInicial));
  double costo_peor_solucion = peor_solucion_inicial.at(0).getDemanda();
  double costo_mejor_solucion = AG.ObtenerMejoresSoluciones(poblacionInicial,1).at(0).at(0).getDemanda();
  cout<<"Pob Inicial Aleatoria - "<<"Costo MS = "<<costo_mejor_solucion<<"Costo PS = "<<costo_peor_solucion<<endl;
  vector<vector<NodoCliente> > next_poblacion; // ESE ELEMENTO DEBE REDEFINIRSE VARIAS VECES, VER SI FUNCIONA, ELIMINAR TODO Y VOLVER A LLENAR
/*
////////////////////////7TAREA
//encontrar mejor solucion de poblacion inicial, escribirla
*/

  for(int generacion_actual= 0; generacion_actual <NUM_GENERACIONES_STOP;generacion_actual++){ //CRITERIO DE TERMINO, SE GENERACION NUM_GENERACIONES_STOP GENERACIONES
    if(generacion_actual==0){
      //sacar mejores generaciones de poblacion inicial
        next_poblacion  = AG.ObtenerMejoresSoluciones(poblacionInicial,NUM_ELITISMO);// AGregar nuevas soluciones
        //cout<<"LENGTH NEXT_POBLACION = MEJORES SOLUCIONES DEBIESE SER 100 , PERO ES = "<<next_poblacion.size()<<endl;
        double costo_poblacion = AG.CostoPoblacion(poblacionInicial);
        //cout << "Costo poblacion Inicial = "<<costo_poblacion<<endl;
          //SELECCIONAR 2 SOLUCIONES DE LA POBLACION ANTERIOR PARA REALIZAR TRANSFORMACION
        for(int i = 0; i< CANTIDAD_TRANSFORMACIONES ;i++){ //DEFINIR CANTIDAD DE VECES QUE SE REALIZARAN TRANSFORMACIONES

          bool mutacion_s1_factible = false;
          bool mutacion_s2_factible = false;
          bool cruzamiento_factible = false;
          //diversificacion;
          vector<NodoCliente> solucion1 = AG.ObtenerSolucionPorRuleta(poblacionInicial,costo_poblacion); //Mejorar

          vector<NodoCliente> solucion2 = AG.ObtenerSolucionPorRuleta(poblacionInicial,costo_poblacion); // SOluciones iguales
          //REALIZAR MUTACIONES Y CRUZAMIENTO EN BASE A PROBABILIDAD, AGREGAR RESULTADO A LA POBLACION INICIAL.Verificar que sea factible!!
          double num_random_operador = (rand() % 100 + 1)/100.0;     // numero entre 0.0 y 1.0 unciona, cada vez escoje uno distinto


          if(num_random_operador<=PXOVER){        // REALIZAR CRUZAMIENTO

            int iteraciones = 0;
            vector<vector<NodoCliente> > soluciones_cruzadas;
            while(!cruzamiento_factible && (iteraciones<NUM_MAX_ITERACIONES)){ //OBTENER SIEMPRE SOLUCIONES FACTIBLES! ver el costo computacional de esto
              iteraciones++;

              //cout<<"ITERACION = "<<iteraciones<<endl;
              //cout<<"PREVIA!!! id = "<<solucion1.at(0).getId()<<endl;;

              soluciones_cruzadas = AG.Cruzamiento(solucion1,solucion2); //COMPROBAR QUE EFECTIVAMENTE CRUZA y que es una solucion factible, SE PODRIA crear una funcion que descarte si resultado no es factible o que quite los 0 y comience a rellenar de nuevo
              cout<<"OJO!!! id = "<<soluciones_cruzadas.at(0).at(0).getId()<<endl;;

              double costo_hijo_1 = AG.EvaluarCalidad(soluciones_cruzadas.at(0),tiempo_servicio_instancia, capacidad_vehiculos_instancia, tiempo_max_ruta_instancia, COSTO_ACTIVACION_VEHICULO); 
              double costo_hijo_2 = AG.EvaluarCalidad(soluciones_cruzadas.at(1),tiempo_servicio_instancia, capacidad_vehiculos_instancia, tiempo_max_ruta_instancia, COSTO_ACTIVACION_VEHICULO);  
              //cout<<"C"<<endl;

            
              if(costo_hijo_1 != -1 && costo_hijo_2 != -1 && (costo_hijo_1 < costo_peor_solucion) && (costo_hijo_2 < costo_peor_solucion)){
                cruzamiento_factible = true;
                //AG.SetCostoSolucion(soluciones_cruzadas.at(0),costo_hijo_1); //OJO! SE SUPONE QUE EL PRIMER NODO ES ID = 0
                NodoCliente & prueba1 = soluciones_cruzadas.at(0).at(0);
                prueba1.setDemanda(costo_hijo_1);
                //cout<<"ID DEPOSITO HIJO 1 = "<<prueba1.getId()<<endl;
                //cout<<" COSTO ES = "<<soluciones_cruzadas.at(0).at(0).getDemanda()<<" pero es = "<<costo_hijo_1<<endl;
                //AG.SetCostoSolucion(soluciones_cruzadas.at(1),costo_hijo_2);

                NodoCliente & prueba2 = soluciones_cruzadas.at(1).at(0);
                prueba2.setDemanda(costo_hijo_2);
                //cout<<"ID DEPOSITO HIJO 2 = "<<prueba2.getId(); // ESTA RETORNANDO OTRA ID DEL DEPOSITO!
                //cout<<" COSTO ES = "<<soluciones_cruzadas.at(1).at(0).getDemanda()<<" pero es = "<<costo_hijo_2<<endl;


                //cout<<"D"<<endl;

              }
              //cout<<"E"<<endl;

            }
            //Agregar hijos a la poblacion nueva que se esta generando.
            //cout<<"F"<<endl;

            next_poblacion.push_back(soluciones_cruzadas.at(0)); // se inserta hijo a la siguiente generacion
            next_poblacion.push_back(soluciones_cruzadas.at(1));
            //cout<<"H"<<endl;

            
          }
          else{ // Realiza mutacion
             //cout<<"COSTO PREVIO MUTACION = "<<AG.CostoSolucion(solucion1)<<endl;
            //cout<<"cant next_poblacion!"<<next_poblacion.size()<<endl;
            //cout<<"4"<<endl;
            int iteracion = 0;
            while(!mutacion_s1_factible && iteracion< NUM_MAX_ITERACIONES ){
              iteracion++;
              vector <NodoCliente>  solucion_mutada_1 = AG.Mutacion(solucion1); // Comprobar que efectivamente muta y no cambia solamente valores de una copia.
              double costo_mutacion_1 = AG.EvaluarCalidad(solucion_mutada_1,tiempo_servicio_instancia, capacidad_vehiculos_instancia, tiempo_max_ruta_instancia, COSTO_ACTIVACION_VEHICULO);  

              if(costo_mutacion_1 != -1 && (costo_mutacion_1 < costo_peor_solucion)){ // solucion factible y "buena"
                mutacion_s1_factible = true;
                 NodoCliente & prueba = solucion_mutada_1.at(0);
                 prueba.setDemanda(costo_mutacion_1); 


                //cout <<"COMPROBACION CAMBIO SET COSTO MUTACION, demanda = "<<solucion_mutada_1.at(0).getDemanda()<<" costo_mutacion_1 "<<costo_mutacion_1<<endl;
                 //LO DE ARRIBA SI ESTA FUNCIONANDO 3:37! 
                if(mutacion_s1_factible){
                  next_poblacion.push_back(solucion_mutada_1);

                } 
              }
            }
            iteracion = 0;
            while(!mutacion_s2_factible && iteracion < NUM_MAX_ITERACIONES){
              //cout<<"B"<<iteracion++<<endl;
              iteracion++;
              vector <NodoCliente>  solucion_mutada_2 = AG.Mutacion(solucion2);
              double costo_mutacion_2 = AG.EvaluarCalidad(solucion_mutada_2,tiempo_servicio_instancia, capacidad_vehiculos_instancia, tiempo_max_ruta_instancia, COSTO_ACTIVACION_VEHICULO);  
              if(costo_mutacion_2 != -1 && (costo_mutacion_2 < costo_peor_solucion)){
                mutacion_s2_factible = true;
                NodoCliente & prueba = solucion_mutada_2.at(0);
                prueba.setDemanda(costo_mutacion_2);

                if(mutacion_s2_factible){
                  next_poblacion.push_back(solucion_mutada_2);              
                }
              }
            }            
          }
          //cout<<"5"<<endl;
          
        }
        //Aqui se tiene una nueva generacion
        costo_peor_solucion = next_poblacion.at(AG.ObtenerPeorSolucion(next_poblacion)).at(0).getDemanda();
       // cout<<"Id cliente DE PEOR SOLUCION EN GENERACION = "<<next_poblacion.at(AG.ObtenerPeorSolucion(next_poblacion)).at(0).getCoordenadaX();
        //cout<<"Id cliente MEJOR SOLUCION EN GENERACION = "<<AG.ObtenerMejoresSoluciones(next_poblacion,1).at(0).at(0).getCoordenadaX();
        vector<NodoCliente> mejor_solucion = AG.ObtenerMejoresSoluciones(next_poblacion,1).at(0);
        costo_mejor_solucion = mejor_solucion.at(0).getDemanda();
        cout<<"GENERACION = "<<generacion_actual<<" SIZE "<<next_poblacion.size()<<" Costo Mejor Solucion = "<<costo_mejor_solucion<<"Costo Peor Solucion = "<<costo_peor_solucion<<endl;
        AG.EscribirMejorSolucion(mejor_solucion,costo_mejor_solucion); //Informar mejor solucion
    }
    else{
        vector<vector<NodoCliente> > ultima_generacion = AG.ObtenerMejoresSoluciones(next_poblacion,NUM_ELITISMO);
        double costo_poblacion = AG.CostoPoblacion(next_poblacion);
        for(int i = 0; i< CANTIDAD_TRANSFORMACIONES ;i++){ //DEFINIR CANTIDAD DE VECES QUE SE REALIZARNA TRANSFORMACIONES
          bool mutacion_s1_factible = false;
          bool mutacion_s2_factible = false;
          bool cruzamiento_factible = false;

          //diversificacion;
          vector<NodoCliente> solucion1 = AG.ObtenerSolucionPorRuleta(next_poblacion,costo_poblacion); //Mejorar
          //cout<<"SIZE S1 = "<<solucion1.size()<<endl;
          vector<NodoCliente> solucion2 = AG.ObtenerSolucionPorRuleta(next_poblacion,costo_poblacion); // SOluciones iguales
          //          cout<<"SIZE S2 = "<<solucion2.size()<<endl;


          //REALIZAR MUTACIONES Y CRUZAMIENTO EN BASE A PROBABILIDAD, AGREGAR RESULTADO A LA POBLACION INICIAL.Verificar que sea factible!!

          double num_random_operador = (rand() % 100 + 1)/100.0;     // este numero determina si se cruza o no

          if(num_random_operador<=PXOVER){
            // REALIZAR CRUZAMIENTO
            
            vector<vector<NodoCliente> > soluciones_cruzadas;
            while(!cruzamiento_factible){
              
              soluciones_cruzadas = AG.Cruzamiento(solucion1,solucion2); //COMPROBAR QUE EFECTIVAMENTE CRUZA y que es una solucion factible, SE PODRIA crear una funcion que descarte si resultado no es factible o que quite los 0 y comience a rellenar de nuevo
              double costo_hijo_1 = AG.EvaluarCalidad(soluciones_cruzadas.at(0),tiempo_servicio_instancia, capacidad_vehiculos_instancia, tiempo_max_ruta_instancia, COSTO_ACTIVACION_VEHICULO); 
              double costo_hijo_2 = AG.EvaluarCalidad(soluciones_cruzadas.at(1),tiempo_servicio_instancia, capacidad_vehiculos_instancia, tiempo_max_ruta_instancia, COSTO_ACTIVACION_VEHICULO);  
            
              if(costo_hijo_1 != -1 && costo_hijo_2 != -1 && (costo_hijo_1 < costo_peor_solucion) && (costo_hijo_2 < costo_peor_solucion)){
                cruzamiento_factible = true;
                AG.SetCostoSolucion(soluciones_cruzadas.at(0),costo_hijo_1); // ver si efectivamente cambia el costo
                AG.SetCostoSolucion(soluciones_cruzadas.at(1),costo_hijo_2);
                //cout <<"COMPROBACION CAMBIO SET COSTO CRUZAMIENTO, demanda = "<<soluciones_cruzadas.at(0).at(0).getDemanda()<<" costo_hijo_1 "<<costo_hijo_1<<endl;
              }
            }

            //Agregar hijos a la poblacion nueva que se esta generando.
            ultima_generacion.push_back(soluciones_cruzadas.at(0)); // se inserta hijo a la siguiente generacion
            ultima_generacion.push_back(soluciones_cruzadas.at(1));
            
          }
          else{
            int iteracion = 0;
            vector<NodoCliente> solucion_mutada_1;
            vector<NodoCliente> solucion_mutada_2;

            while(!mutacion_s1_factible && (iteracion<NUM_MAX_ITERACIONES)){
              iteracion++;
              solucion_mutada_1 = AG.Mutacion(solucion1); // Comprobar que efectivamente muta y no cambia solamente valores de una copia.

              double costo_mutacion_1 = AG.EvaluarCalidad(solucion_mutada_1,tiempo_servicio_instancia, capacidad_vehiculos_instancia, tiempo_max_ruta_instancia, COSTO_ACTIVACION_VEHICULO);  
              if(costo_mutacion_1 != -1 && (costo_mutacion_1 < costo_peor_solucion)){
                mutacion_s1_factible = true;
                NodoCliente & prueba = solucion_mutada_1.at(0);
                prueba.setDemanda(costo_mutacion_1);


              }
            }
            iteracion = 0; //evita bucles cuando no haya combinaciones posibles
            while(!mutacion_s2_factible && (iteracion < NUM_MAX_ITERACIONES)){
              iteracion++;
              solucion_mutada_2 = AG.Mutacion(solucion2);
              double costo_mutacion_2 = AG.EvaluarCalidad(solucion_mutada_1,tiempo_servicio_instancia, capacidad_vehiculos_instancia, tiempo_max_ruta_instancia, COSTO_ACTIVACION_VEHICULO);  
              if(costo_mutacion_2 != -1 && (costo_mutacion_2 < costo_peor_solucion)){
                mutacion_s2_factible = true;
                NodoCliente & prueba = solucion_mutada_2.at(0);
                prueba.setDemanda(costo_mutacion_2);
              }
            }

            if(mutacion_s1_factible && mutacion_s2_factible){
              ultima_generacion.push_back(solucion_mutada_1);
              ultima_generacion.push_back(solucion_mutada_2);              
            }

          }//FIN DEL ESE

        }// FIN DEL FOR
        next_poblacion.clear(); // limpiar todo de el vector
        next_poblacion = ultima_generacion; // UPDATE, VER SI FUNCIONA! ES ESCENCIAL!

        costo_peor_solucion = next_poblacion.at(AG.ObtenerPeorSolucion(next_poblacion)).at(0).getDemanda();
        costo_mejor_solucion = AG.ObtenerMejoresSoluciones(next_poblacion,1).at(0).at(0).getDemanda();
        cout<<"GENERACION = "<<generacion_actual<<" Costo Mejor Solucion = "<<costo_mejor_solucion<<"Costo Peor Solucion = "<<costo_peor_solucion<<endl;
    }

    //Escribir mejor solucion de la generacion actual en carpeta temporal!

  }//fin del for (num_generaciones = criterio de temrino) 
  //ESCRIBIR MEJOR SOLUCION DE LA ULTIMA GENERACION

  vector<NodoCliente> mejor_solucion_encontrada = AG.ObtenerMejoresSoluciones(next_poblacion,1).at(0); //SOLO QUEREMOS LA MEJOR
  double costo_mejor_solucion_encontrada = AG.CostoSolucion(mejor_solucion_encontrada);
  cout<<"-------------Se ha finalizado el Algoritmo ----------------------------!"<<endl;
  AG.EscribirMejorSolucion(mejor_solucion_encontrada,costo_mejor_solucion_encontrada);
  return 0;
}