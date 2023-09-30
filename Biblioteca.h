#pragma once
#include <iostream>
#include <string>

#include "ListaSoftware.h"


using namespace std;

//Biblioteca, se usa tanto para almacenar software instalado como para representar todos los softwares que se puedan instalar
class Biblioteca{
    private:
        ListaSoftware *softwareInstalado;
    public:
        Biblioteca();
        ~Biblioteca();
        ListaSoftware* getSoftwareInstalado();
        string mostrarDatos(Usuario*);
        string mostrarDatosMin();
        string mostrarDatosNormal();
        string mostrarDatosAdmin();
        void agregarABiblioteca(Software*);
        void perteneceAgregarABiblioteca(Software*,string*, string, int);
        Software* retornarSoftwarePorNombre(Usuario* ,string);

        Software* menorRetornarSoftware(string);
        Software* normalRetornarSoftware(string);
        Software* adminRetornarSoftware(string);
        
        bool desinstalarSoftware(string);

        bool instalarSoftware(Biblioteca*,Usuario*,string);
        string softwareNoInstalado(Biblioteca*,Usuario*);


};
//constructor de Biblioteca
Biblioteca::Biblioteca(){
    this->softwareInstalado = new ListaSoftware();
}
//destructor de Biblioteca
Biblioteca::~Biblioteca(){}
ListaSoftware* Biblioteca::getSoftwareInstalado(){return this->softwareInstalado;}

//recibe un usuario, y dependiendo de su tipo le entrega diferente informacion
string Biblioteca::mostrarDatos(Usuario* usuario){
    if(usuario->getObjectName() == "UsuarioNormal"){
        return mostrarDatosNormal();
    }
    else if(usuario->getObjectName() == "UsuarioMenor"){
        return mostrarDatosMin();
    }
    else if(usuario->getObjectName() == "UsuarioAdmin"){
        return mostrarDatosAdmin();
    }
    else{
        return "tipo de usuario desconocido";
    }
}

string Biblioteca::mostrarDatosMin(){
    return this->softwareInstalado->ToStringMin();
}

string Biblioteca::mostrarDatosNormal(){
    return this->softwareInstalado->ToStringNormal();
}

string Biblioteca::mostrarDatosAdmin(){
    return this->softwareInstalado->ToStringAdmin();
}
//recibe un Software, crea un nodo donde lo almacena en la listasoftware dentro de la biblioteca
//usar esta funcion en caso de no tener requisitos especificos
void Biblioteca::agregarABiblioteca(Software *softwareNuevo)
{   
    NodoSoftware *nodo = new NodoSoftware(softwareNuevo);
    this->softwareInstalado->insertSoftware(nodo);
}

//recibe un Software, crea un nodo, verifica si pertenece y lo almacena en la listasoftware dentro de la biblioteca
void Biblioteca::perteneceAgregarABiblioteca(Software *softwareNuevo,string *arregloBase, string input, int longitud){
    NodoSoftware *nodo = new NodoSoftware(softwareNuevo);
    bool verif = false;
    verif = this->softwareInstalado->insertSoftwarePertenece(nodo,arregloBase,input, longitud);
    if(!verif){
        nodo->~NodoSoftware();//si hubo un error en la creacion se debe destruir este nodo
    }
}

//recibe un usuario y determina que funcion debe tomar
//retorna un software que es apto para el usuarioActual
Software* Biblioteca::retornarSoftwarePorNombre(Usuario* usuario,string softwareNombre){
    if(usuario->getObjectName() == "UsuarioNormal"){
        return normalRetornarSoftware(softwareNombre);
    }
    else if(usuario->getObjectName() == "UsuarioMenor"){
        return menorRetornarSoftware(softwareNombre);
    }
    else if(usuario->getObjectName() == "UsuarioAdmin"){
        return adminRetornarSoftware(softwareNombre);
    }
    else{
        cout<<"Tipo de usuario desconocido"<<endl;
        return NULL;
    }
}

//desde la biblioteca envia la instruccion y obtiene el software especificado que es apto para todo publico
//excepto software para admin
//retornara NULL si no encuentra software cuyo nombre coincida, sea apto, y no sea exclusivo de admin
Software* Biblioteca::menorRetornarSoftware(string softwareNombre){
    return this->softwareInstalado->retornarSoftwareMin(softwareNombre);
}
//desde software de todo publico hasta +18
//excepto software para admin
//retornara NULL si no encuentra software cuyo nombre coincida y no sea exclusivo de admin
Software* Biblioteca::normalRetornarSoftware(string softwareNombre){
    return this->softwareInstalado->retornarSoftwareNormal(softwareNombre);
}
//sin restricciones de ningun tipo
//retornara NULL si no encuentra software cuyo nombre coincida
Software* Biblioteca::adminRetornarSoftware(string softwareNombre){
    return this->softwareInstalado->retornarSoftwareAdmin(softwareNombre);
}

//no crea logs porque el Software esta siendo eliminado junto con la opcion de ver los logs
//Elimina un software de la biblioteca a partir de su nombre
bool Biblioteca::desinstalarSoftware(string nombreSoftware){
    this->softwareInstalado->deleteSoftware(nombreSoftware);
}

//Instala software en el computador
//necesita saber cual es la tienda
//necesita conocer el usuario que envia la instruccion
//y el nombre de software buscado
//ejecuta un reset en el Software a desintalar
bool Biblioteca::instalarSoftware(Biblioteca *tienda,Usuario* usuarioActual,string nombreSoftware){
    //retorna el software de la tienda
    Software *softwareAInstalar = tienda->retornarSoftwarePorNombre(usuarioActual,nombreSoftware);
    if(softwareAInstalar == NULL){//no existe
        return false;
    }
    softwareAInstalar->hardReset();
    //lo inserta en el computador
    if(softwareAInstalar != NULL){
        NodoSoftware *newNodo = new NodoSoftware(softwareAInstalar);
        return this->softwareInstalado->insertSoftware(newNodo);
        
    }
    cout<<"Error: no se encuentra el Software o ya esta instalado: "<<nombreSoftware<<endl;
    return false;
}

string Biblioteca::softwareNoInstalado(Biblioteca *tienda,Usuario* usuarioActual){

    int edadActual = usuarioActual->getAge();//edad de usuarioUsuario(el que esta logeado ahora mismo)
    string r = "";//variable string a la que se concatenaran los amigos potenciales
    
    
    NodoSoftware *softwareTienda = tienda->getSoftwareInstalado()->getPrimero();//primer nodo del la tienda de software

    while(softwareTienda != NULL){
        if(this->softwareInstalado->searchSoftware(softwareTienda->getSoftware()->getSoftwareName()) == false){
            //si el software de la tienda no se encuentra instalado en la computadora
            if(usuarioActual->getObjectName() == "UsuarioAdmin"){
                r = r + softwareTienda->getSoftware()->getSoftwareName()+"\n";
            }
            else if(usuarioActual->getObjectName() == "UsuarioMenor"){
                if(softwareTienda->getSoftware()->getClasificacionEdad() < 18 && softwareTienda->getSoftware()->adminExclusive() == false){
                    r = r + softwareTienda->getSoftware()->getSoftwareName()+"\n";
                }
            }
            else if(usuarioActual->getObjectName() == "UsuarioNormal"){
                if(softwareTienda->getSoftware()->adminExclusive() == false){
                    r = r + softwareTienda->getSoftware()->getSoftwareName()+"\n";
                }
            }
            else{
                return "tipo de usuario desconocido";
            }
        }


        softwareTienda = softwareTienda->getNextNode();
    }
    
    if(r == ""){
        cout<<"No hay nada en la tienda que no tengas ya instalado"<<endl;
    }

    return r;
}
