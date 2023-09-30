#pragma once

#include <iostream>

#include "Software.h"
using namespace std;
//es una clase derivada de Software
class SoftwareOfimatica : public Software{
    private:
        string *documentos;//puntero de string
        int cantidadDocumentos;//cantidad de documentos actuales en el Software de Ofimatica
    public:
        SoftwareOfimatica(string,string,int,int);
        ~SoftwareOfimatica();
        void crearDocumento(string);
        int getCantidadDocumentos();
        bool eliminarDocumento(string);
        string verDocumentos();
        string ToString();
        string getObjectName();
};

//constructor del SoftwareOfimatica
SoftwareOfimatica::SoftwareOfimatica(string softwareName,string devName,int clasificacionEdad, int precio):Software(softwareName,devName,clasificacionEdad,precio){
    this->documentos = new string[100];
    this->cantidadDocumentos = 0;
}

//destructor de SoftwareOfimatica
SoftwareOfimatica::~SoftwareOfimatica(){}

//recibe un string que represente el documento y lo almacena en un arreglo
void SoftwareOfimatica::crearDocumento(string nuevoDocumento){
    string *point = this->documentos;
    if(this->cantidadDocumentos < 100){
        //tratando al puntero como un arreglo se envia la accion de guardar el string del nuevo documento
        //en la ultima posicion desocupada
        point[cantidadDocumentos] = nuevoDocumento;
        this->cantidadDocumentos++;
    }
    else{
        cout<<"Error. capacidad excedida, elimine algun otro documento antes de agregar mas"<<endl;
    }
}
//getter: retorna la cantidad de documentos creados hasta ahora en el Software
int SoftwareOfimatica::getCantidadDocumentos(){return this->cantidadDocumentos;}

//elimina un documento
//necesita un string que represente el documento
//antes de correr esta funcion se debe mostrar los documentos actuales para facilitar la visualizacion
//true: documento borrado
//false: no se encuentra dicho documento
bool SoftwareOfimatica::eliminarDocumento(string documentoAborrar){
    string *point = this->documentos;
    int i = 0; //inicializo en 0 para ocupar este numero mas adelante
    for(i = 0;i < this->cantidadDocumentos;i++){
        if(point[i] == documentoAborrar){
            break;//lo encontro
        }
    }
    if(i == this->cantidadDocumentos){//esto solo es posible si nunca entro al break
    //implicando que no se pudo encontrar
        cout<<"No se encuentra el documento"<<endl;
        return false;
    }

    for(int k = i;k < this->cantidadDocumentos;k++){
        point[k] = point[k+1];//copia el actual con el sigt
    }
    this->cantidadDocumentos--;
    return true;
}

//retorna un string conteniendo todos los documentos generados por este SoftwareOfimatica
string SoftwareOfimatica::verDocumentos(){
    string r = "";
    string *point = this->documentos;
    for(int i = 0;i < this->cantidadDocumentos;i++){
        r += point[i]+"\n";
    }
    return r;
}

//retorna los datos de su clase padre+ la cantidad de documentos de esta clase derivada
string SoftwareOfimatica::ToString(){
    return this->ToStringPadre()+", cantidad de documentos: "+to_string(this->cantidadDocumentos);
}
//retorna el tipo de objeto (SoftwareOfimatica)
string SoftwareOfimatica::getObjectName(){return "SoftwareOfimatica";} 