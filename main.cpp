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

  vector<vector<NodoCliente> > poblacion; // A esta se le agregara las mejores de la pob inicial y resultados de mutacion y cruzamiento
  //INICIALIZAR POBLACION
  vector<vector<NodoCliente> > poblacionInicial  = AG.InicializarPoblacion(TAMANO_POBLACION,path); // Se obtiene población con la cual trabajar
  //AG.LeerPoblacion(poblacionInicial);
  //ELITISMO
  vector<vector<NodoCliente> > tmp_mejores_soluciones_pob_inicial  = AG.ObtenerMejoresSoluciones(poblacionInicial,NUM_ELITISMO);
  double costo_poblacion = AG.CostoPoblacion(poblacionInicial);
  cout << "Costo poblacion = "<<costo_poblacion<<endl;

  //SELECCIONAR 2 SOLUCIONES DE LA POBLACION ANTERIOR PARA REALIZAR TRANSFORMACION
  for(int i = 0; i< (100);i++){

    //diversificacion;
    vector<NodoCliente> solucion1 = AG.ObtenerSolucionPorRuleta(poblacionInicial,costo_poblacion); //Mejorar
    vector<NodoCliente> solucion2 = AG.ObtenerSolucionPorRuleta(poblacionInicial,costo_poblacion); // SOluciones iguales

    //REALIZAR MUTACIONES Y CRUZAMIENTO EN BASE A PROBABILIDAD, AGREGAR RESULTADO A LA POBLACION INICIAL.Verificar que sea factible!!

    double num_random_operador = (rand() % 100 + 1)/100.0;     // este numero determina si se cruza o no

    if(num_random_operador<PXOVER){
      // REALIZAR CRUZAMIENTO

      vector<vector<NodoCliente> > soluciones_mutadas = AG.Cruzamiento(solucion1,solucion2);
    }
    else{
      vector<NodoCliente> solucion_mutada_1 = AG.Mutacion(solucion1); // Comprobar que efectivamente muta y no cambia solamente valores de una copia.
      vector<NodoCliente> solucion_mutada_2 = AG.Mutacion(solucion2);

    }

  }





  return 0;
}