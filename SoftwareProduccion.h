#pragma once

#include <iostream>

#include "Software.h"
using namespace std;
//es una clase derivada de Software
class SoftwareProduccion:public Software{
    private:
        string tipoArchivo;//'video','foto','streaming','musica'
        string *archivosGenerados;//puntero que apunta al principio de un arreglo donde se contienen los archivos generados en este software
        int cantidadArchivos;//cantidad de archivos de produccion generados(video,foto,streaming,musica)
    public:
        SoftwareProduccion(string,string,int,int,string);
        ~SoftwareProduccion();
        void agregarArchivoProduccion(string);
        string verProduccion();
        bool eliminarArchivoProduccion(string);
        string ToString();
        string getObjectName();
};

//constructor de SoftwareProduccion
SoftwareProduccion::SoftwareProduccion(string softwareName,string devName,int clasificacionEdad, int precio,string tipoArchivo):Software(softwareName,devName,clasificacionEdad,precio){
    this->tipoArchivo = tipoArchivo;
    this->archivosGenerados = new string[100];
    this->cantidadArchivos = 0;
}
//destructor de SoftwareProduccion
SoftwareProduccion::~SoftwareProduccion(){}

//genera un nuevo archivo al software
//se ingresa un string (ejemplo: "nombrevideo.mp4")
//la terminacion .mp4 idealmente se asignara despues de llamar a esta funcion
void SoftwareProduccion::agregarArchivoProduccion(string nuevaProduccion){
    string *point = this->archivosGenerados;
    if(tipoArchivo == "video" || tipoArchivo == "streaming"){
        nuevaProduccion += ".mp4";
    }
    else if(tipoArchivo == "foto"){
        nuevaProduccion += ".png";
    }
    else if(tipoArchivo == "musica"){
        nuevaProduccion += ".mp3";
    }
    else{
        cout<<"Error fatal: tipo desconocido"<<endl;
        return;
    }

    if(cantidadArchivos < 100){
        point[this->cantidadArchivos] = nuevaProduccion;
        this->cantidadArchivos++;
    }
    else{
        cout<<"error: capacidad excedida, elimine al menos un archivo de produccion antes de seguir generando"<<endl;
    }
}

//muestra todos los archivos en el software de produccion
string SoftwareProduccion::verProduccion(){
    string r = "";
    string *point = this->archivosGenerados;
    for(int i  = 0;i < this->cantidadArchivos;i++){
        r += point[i]+"\n";
    }
}

//elimina un archivo de produccion de este SoftwareProduccion
//metodo usado: sobreescritura/corrimiento
bool SoftwareProduccion::eliminarArchivoProduccion(string archivoABorrar){
    int i = 0;
    string *point = this->archivosGenerados;
    for(int i = 0;i < this->cantidadArchivos;i++){
        if(point[i] == archivoABorrar){
            break;
        }
    }
    if(i == this->cantidadArchivos){
        //en el momento en que !i < cantidadArchivos
        //quiere decir que a i se le tuvo que sumar otra vez mas
        //de manera que i al salir debe ser igual a this->cantidadArchivos
        //esto solo es posible si en ningun caso se cumplio la condicion en la comparacion de string
        cout<<"No se encuentra el archivo especificado"<<endl;
        return false;
    }
    for(int k = i;k < this->cantidadArchivos-1;k++){//desde el dato que se busca sobreescribir comienza el corrimiento
        point[k] = point[k+1];//el actual copia y guarda los datos del sigt
    }
    this->cantidadArchivos--;
    return true;
}

//retorna los datos de su clase padre + tipo de produccion de esta clase derivada
string SoftwareProduccion::ToString(){
    return this->ToStringPadre()+", tipo de produccion: "+this->tipoArchivo;
}
//retorna el tipo de objeto (SoftwareProduccion)
string SoftwareProduccion::getObjectName(){return "SoftwareProduccion";}