#pragma once

#include <iostream>

#include "Software.h"
using namespace std;
//es una clase derivada de Software
class SoftwareSeguridad : public Software{
    private:
        string especialidad;//{"Ransomware","Spyware","botnets","rootkits","gusanos","troyanos"}
        string *tiposMalware;//info sobre la muestra de malware
        int cantidadMuestras;//cantidad de muestras de malware agregadas al software
    public:
        SoftwareSeguridad(string,string,int, int,string);
        ~SoftwareSeguridad();
        string verMuestras();
        void agregarMuestra(string);
        void eliminarMuestra(string);
        bool adminExclusive();
        string ToString();
        string getObjectName();
};

//constructor de SoftwareSeguridad
SoftwareSeguridad::SoftwareSeguridad(string softwareName,string devName,int clasificacionEdad, int precio,string especialidad):Software(softwareName,devName,clasificacionEdad,precio){
    this->tiposMalware = new string[100];
    this->cantidadMuestras = 0;
    this->especialidad = especialidad;

}

//destructor de SoftwareSeguridad
SoftwareSeguridad::~SoftwareSeguridad(){}

//retorna un string conteniendo todas las muestras que han sido agregadas a este Software de seguridad
string SoftwareSeguridad::verMuestras(){
    string r = "";
    string *point = this->tiposMalware;
    for(int i = 0;i < this->cantidadMuestras;i++){
        r += point[i]+"\n";
    }
    return r;
}

//agrega una nueva muestra de malware al arreglo
//se informara si la memoria es insuficiente para agregar otra muestra mas
void SoftwareSeguridad::agregarMuestra(string nuevaMuestra){
    string *point = this->tiposMalware;
    if(this->cantidadMuestras < 100){
        point[this->cantidadMuestras] = nuevaMuestra; 
        this->cantidadMuestras++;
    }
    else{
        cout<<"Capacidad de muestras alcanzada"<<endl;
        cout<<"elimine alguna muestra antes de continuar agregando"<<endl;
    }
}

//recibe como parametro el nombre de la muestra
//si la encuentra la elimina e informa sobre su correcta eliminacion
//sino informara que no se pudo encontrar
void SoftwareSeguridad::eliminarMuestra(string muestraABorrar){
    string *point = this->tiposMalware;
    int i = 0;
    for(i = 0;i < this->cantidadMuestras;i++){
        if(point[i] == muestraABorrar){
            break;
        }
    }
    if(i == this->cantidadMuestras){
        cout<<"No se pudo encontrar la muestra"<<endl;
        return;
    }
    for(int k = i; k < this->cantidadMuestras-1;k++){
        point[k] = point[k+1];
    }
    cout<<"Eliminado correctamente"<<endl;
    this->cantidadMuestras--;
}

//el software de seguridad solo puede ser visto por 'UsuarioAdmin'
bool SoftwareSeguridad::adminExclusive(){return true;}

//retorna los datos de su clase padre + la cantidad de muestras de malware de esta clase derivada
string SoftwareSeguridad::ToString(){
    return this->ToStringPadre()+", cantidad de muestras de malware recolectadas: "+to_string(this->cantidadMuestras);
}

//retorna el tipo de objeto(SoftwareSeguridad)
string SoftwareSeguridad::getObjectName(){return "SoftwareSeguridad";}