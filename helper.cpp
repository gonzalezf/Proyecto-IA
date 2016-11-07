using namespace std;
#include "helper.h"
/*
void LeerInstancia(string path){
	std::ifstream infile("instances/"+path+".txt");

}
*/
bool Helper::ArchivoExiste(const std::string& name){
    ifstream f(name.c_str());
    return f.good();
}


void Helper::LeerInstancia(const std::string& fileName){
  string line;
  ifstream myfile (fileName.c_str());

  if (myfile)  // same as: if (myfile.good())
    {
    while (getline( myfile, line ))  // same as: while (getline( myfile, line ).good())
      {
      	cout <<"Linea = "<<line<<endl;

      }
    myfile.close();
    }
  else cout << "Imposible leer archivo" <<endl<<endl;

  return;
}



