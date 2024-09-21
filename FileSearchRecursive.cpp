#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Archivo{
    string name; //Nombre del archivo
};

struct Directorio {
    string name; //Nombre del directorio
    vector<Archivo> archivos; //Vector de archivos
    vector<Directorio> subdirectorio; //Vector de subdirectorios
};

bool findFile(Directorio& dir, string& path, string& target){ //Mutacion de path con el ampersand
    // Caso base
    for(auto arch: dir.archivos){ //Iteracion de archivos dentro de la raiz
        if(arch.name == target){ //Si el archivo es igual al target
            path += "/" + dir.name; //Se agrega el nombre del directorio a la ruta
            return true; //Se retorna verdadero
        }
    }

    for(auto subdir: dir.subdirectorio){ //Iteracion de subdirectorios dentro de la raiz
        string subdirpath = path + "/" + dir.name; //Se agrega el nombre del directorio a la ruta
        if(findFile(subdir, subdirpath, target)){
            path = subdirpath;
            return true;
        }
    }

    return false;
}

int main(){
    Directorio sistemaDeArchivos = {
   "root",
   {
           {"archivo1.txt"},
           {"archivo2.txt"}
   },
   {
           {
               "subdir1",
               {
                   {"archivo3.txt"},
               },
               {
                   {
                       "subdir2",
                       {
                           {"target.txt"},
                           {"archivo4.txt"}
                       },
                       {}
                   }
               }
           },
           {"archivo5.txt"}
   }
};

string target = "archivo3.txt";
string path = "";

cout << &sistemaDeArchivos << endl;

if(findFile(sistemaDeArchivos, path, target)){
    cout << "Archivo encontrado en: " << path << "/" << target << endl;
} else {
    cout << "Archivo no encontrado" << endl;
}
return 0;

};