#pragma once

#include <iostream>

#include "Software.h"
using namespace std;
//es una clase derivada de Software
class SoftwareNavegador : public Software{
    private:
        string *historial;//puntero a un arreglo de string
        int cantidadElementos;//cuantas paginas han sido registradas como visitadas hasta ahora
    public:
        SoftwareNavegador(string,string,int,int);
        ~SoftwareNavegador();
        string verHistorial();
        void visitarPagina(string);
        void borrarElementosDelHistorial(int);
        void hacerEspacio();
        string ToString();
        string getObjectName();
};

//constructor de SoftwareNavegador
SoftwareNavegador::SoftwareNavegador(string softwareName,string devName,int clasificacionEdad, int precio):Software(softwareName,devName,clasificacionEdad,precio){
    this->historial = new string[100];
    this->cantidadElementos = 0;
}

//destructor de SoftwareNavegador
SoftwareNavegador::~SoftwareNavegador(){}

//muestra linea por linea todo el historial que el navegador de este computador ha registrado
string SoftwareNavegador::verHistorial(){
    string r = "";
    string *point = this->historial;
    for(int i =0;i < this->cantidadElementos;i++){
        r += point[i]+"\n";
    }
    return r;
}

//mientras no colapse la memoria, agrega el nombre de la pagina visitada recientemente
void SoftwareNavegador::visitarPagina(string nombrePagina){
    string *point = historial;
    if(this->cantidadElementos < 100){
        point[this->cantidadElementos] = nombrePagina;
        this->cantidadElementos++;
    }
    else{
        cout<<"sugerencia: borrar algunos elementos del historial para hacer espacio"<<endl;
        cout<<"La pagina se ingresara de todos modos, pero el registro mas antiguo sera eliminado"<<endl;
        hacerEspacio();//al quitar el primero del arreglo la cantidad bajo a 99
        point[this->cantidadElementos] = nombrePagina;
        this->cantidadElementos++;//y aca volvio a ser 100
    }
}

//elimina los ultimos 'n' elementos guardados en el historial de este navegador
//como es un arreglo y solo se muestran los datos que existen
//ocultarlos tambien cuenta como borrarlos
//si se ingresa '-1' se 'borrara' todo el historial
void SoftwareNavegador::borrarElementosDelHistorial(int cantidad){
    if(cantidad == -1){
        this->cantidadElementos = 0;
        return;
    }
    this->cantidadElementos = this->cantidadElementos - cantidad;
}

//elimina el primer registro en el historial
//esta funcion solo deberia ser usada cuando se colapse la memoria
void SoftwareNavegador::hacerEspacio(){
    string *point = this->historial;
    for(int k = 0; k < this->cantidadElementos-1;k++){
        point[k] = point[k+1];
    }
    this->cantidadElementos--;
}

//retorna los datos de su clase padre
string SoftwareNavegador::ToString(){
    return this->ToStringPadre();
}
//retorna un string conteniendo el tipo de objeto(SoftwareNavegador)
string SoftwareNavegador::getObjectName(){return "SoftwareNavegador";}