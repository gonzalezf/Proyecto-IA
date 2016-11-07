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

#define PMUTATION 0.15 //porcentaje mutacion
#define PXOVER 0.8 //Porcentaje crossover
#define TAMANO_POBLACION 50
 // cantidad de soluciones 

//Cada genotipo es un miembro de la población con
// gene: rutas 
// fitness: the fitness (será igual al valor de la Funcion objetivo)
//Cada ruta es un gen
//genotipo es un conjunto de rutas




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


  return 0;
}