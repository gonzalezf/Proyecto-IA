# Algoritmo Genetico con 2 operadores para Open Vehicle Routing Problem
Proyecto de Inteligencia Artificial, UTFSM Campus San Joaquín 2016-2

#Creado por Felipe Andrés González Pizarro

/*///////////////////////////////////////////////////////////////
//------EJECUCION E INFORMACION IMPORTANTE-----------------------
///////////////////////////////////////////////////////////////*/

Antes de ejecutar, deben existir las siguientes carpetas en el mismo directorio donde se encuentra el archivo main.cpp:
- instances
- out

Los archivos cpp distribuyen de forma más ordenda los métodos de las clases.
- La clase Helper está definida en el archivo helper.h y sus métodos están programados en helper.cpp
- La clase AlgoritmoGenetico está definida en el archivo algoritmogenetico.h y sus métodos están programados en 
algoritmogenetico.cpp

La sintáxis básica para ejecutar el algoritmo con el makefile es:

make INSTANCE={instancia}

El parámetro INSTANCE es obligatorio y hace referencia a una instancia que exista en 

./instances/{instancia}.txt

A modo de ejemplo, para probar el algoritmo con la instancia "vrpnc1.txt", se debe 
ingresr en linea de comando:

make INSTANCE=vrpnc1


La mejor solución encontrada hasta el momento en la carpeta ./out/ llamado:

"mejor_solucion.txt"

El código fuente se encuentra disponible en linea en https://github.com/gonzalezf/Proyecto-IA







