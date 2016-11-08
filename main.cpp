using namespace std;
#include "algoritmogenetico.h"
#include "nodocliente.h"
/* Para compilar
g++ -Wall main.cpp helper.cpp algoritmogenetico.cpp nodocliente.cpp
./a.out vrpnc1
*/

//Pasos de Algoritmo Genetico
//Inicializacion, población inicial aleatorioa
// Evaluación, guardar de forma temporal mejor solucion en tmp
//realizar hasta criterio de termino, Crossover y mutuacion (ver probabilidades)
//evaluar cada resultado, ingresar mejor solucion en tmp, reemplazar si es mejor que la anterior en resultado final


//Definición de parametros

#define PMUTATION 0.2 //porcentaje mutacion 
#define PXOVER 0.8 //Porcentaje crossover  // solo este importa
#define TAMANO_POBLACION 10000
#define NUM_ELITISMO 20 // cantidad de "mejores soluciones que se seleccionan de una poblacion "
#define NUM_GENERACIONES_STOP 100
 // cantidad de soluciones 




int main(int argc, char **argv){


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
    //helper.LeerInstancia(path);
  }

  //INICIALIZAR POBLACION
  vector<vector<NodoCliente> > poblacionInicial  = AG.InicializarPoblacion(TAMANO_POBLACION,path); // Se obtiene población con la cual trabajar
  //AG.LeerPoblacion(poblacionInicial);
  //ELITISMO

  vector<vector<NodoCliente> > next_poblacion; // ESE ELEMENTO DEBE REDEFINIRSE VARIAS VECES, VER SI FUNCIONA, ELIMINAR TODO Y VOLVER A LLENAR

  for(int generacion_actual= 0; generacion_actual <NUM_GENERACIONES_STOP;generacion_actual++){ //CRITERIO DE TERMINO, SE GENERACION NUM_GENERACIONES_STOP GENERACIONES
    if(generacion_actual==0){
      //sacar mejores generaciones de poblacion inicial
        next_poblacion  = AG.ObtenerMejoresSoluciones(poblacionInicial,NUM_ELITISMO); // AGregar nuevas soluciones
        double costo_poblacion = AG.CostoPoblacion(poblacionInicial);
        cout << "Costo poblacion Inicial = "<<costo_poblacion<<endl;
          //SELECCIONAR 2 SOLUCIONES DE LA POBLACION ANTERIOR PARA REALIZAR TRANSFORMACION
        for(int i = 0; i< (100);i++){ //DEFINIR CANTIDAD DE VECES QUE SE REALIZARNA TRANSFORMACIONES

          //diversificacion;
          vector<NodoCliente> solucion1 = AG.ObtenerSolucionPorRuleta(poblacionInicial,costo_poblacion); //Mejorar
          vector<NodoCliente> solucion2 = AG.ObtenerSolucionPorRuleta(poblacionInicial,costo_poblacion); // SOluciones iguales

          //REALIZAR MUTACIONES Y CRUZAMIENTO EN BASE A PROBABILIDAD, AGREGAR RESULTADO A LA POBLACION INICIAL.Verificar que sea factible!!

          double num_random_operador = (rand() % 100 + 1)/100.0;     // este numero determina si se cruza o no

          if(num_random_operador<PXOVER){
            // REALIZAR CRUZAMIENTO

            vector<vector<NodoCliente> > soluciones_mutadas = AG.Cruzamiento(solucion1,solucion2); //COMPROBAR QUE EFECTIVAMENTE CRUZA y que es una solucion factible, SE PODRIA crear una funcion que descarte si resultado no es factible o que quite los 0 y comience a rellenar de nuevo
            //Agregar hijos a la poblacion nueva que se esta generando.
            next_poblacion.push_back(soluciones_mutadas.at(0)); // se inserta hijo a la siguiente generacion
            next_poblacion.push_back(soluciones_mutadas.at(1));
          }
          else{
            vector<NodoCliente> solucion_mutada_1 = AG.Mutacion(solucion1); // Comprobar que efectivamente muta y no cambia solamente valores de una copia.
            vector<NodoCliente> solucion_mutada_2 = AG.Mutacion(solucion2);
            next_poblacion.push_back(solucion_mutada_1);
            next_poblacion.push_back(solucion_mutada_2);

          }

        }
    }
    else{
        vector<vector<NodoCliente> > ultima_generacion = AG.ObtenerMejoresSoluciones(next_poblacion,NUM_ELITISMO);
        double costo_poblacion = AG.CostoPoblacion(next_poblacion);
        for(int i = 0; i< (100);i++){ //DEFINIR CANTIDAD DE VECES QUE SE REALIZARNA TRANSFORMACIONES

          //diversificacion;
          vector<NodoCliente> solucion1 = AG.ObtenerSolucionPorRuleta(next_poblacion,costo_poblacion); //Mejorar
          vector<NodoCliente> solucion2 = AG.ObtenerSolucionPorRuleta(next_poblacion,costo_poblacion); // SOluciones iguales

          //REALIZAR MUTACIONES Y CRUZAMIENTO EN BASE A PROBABILIDAD, AGREGAR RESULTADO A LA POBLACION INICIAL.Verificar que sea factible!!

          double num_random_operador = (rand() % 100 + 1)/100.0;     // este numero determina si se cruza o no

          if(num_random_operador<PXOVER){
            // REALIZAR CRUZAMIENTO

            vector<vector<NodoCliente> > soluciones_mutadas = AG.Cruzamiento(solucion1,solucion2); //COMPROBAR QUE EFECTIVAMENTE CRUZA y que es una solucion factible, SE PODRIA crear una funcion que descarte si resultado no es factible o que quite los 0 y comience a rellenar de nuevo
            //Agregar hijos a la poblacion nueva que se esta generando.
            ultima_generacion.push_back(soluciones_mutadas.at(0)); // se inserta hijo a la siguiente generacion
            ultima_generacion.push_back(soluciones_mutadas.at(1));
          }
          else{
            vector<NodoCliente> solucion_mutada_1 = AG.Mutacion(solucion1); // Comprobar que efectivamente muta y no cambia solamente valores de una copia.
            vector<NodoCliente> solucion_mutada_2 = AG.Mutacion(solucion2);
            ultima_generacion.push_back(solucion_mutada_1);
            ultima_generacion.push_back(solucion_mutada_2);

          }

        }
        next_poblacion = ultima_generacion; // UPDATE, VER SI FUNCIONA! ES ESCENCIAL!
    }

    //Escribir mejor solucion de la generacion actual en carpeta temporal!

  }//fin del for (num_generaciones = criterio de temrino) 
  //ESCRIBIR MEJOR SOLUCION DE LA ULTIMA GENERACION

  vector<NodoCliente> mejor_solucion_encontrada = AG.ObtenerMejoresSoluciones(next_poblacion,1).at(0); //SOLO QUEREMOS LA MEJOR
  double costo_mejor_solucion_encontrada = AG.CostoSolucion(mejor_solucion_encontrada);
  AG.EscribirMejorSolucion(mejor_solucion_encontrada,costo_mejor_solucion_encontrada);
  return 0;
}