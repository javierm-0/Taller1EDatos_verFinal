#pragma once

#include <iostream>
#include "NodoSoftware.h"

using namespace std;

class ListaSoftware{
    private:
        NodoSoftware *primero,*ultimo;
        int cantidadSoftware;
    public:
        ListaSoftware();
        bool insertSoftware(NodoSoftware*);
        bool searchSoftware(string);
        int getCantidadSoftware();
        string ToStringMin();
        string ToStringNormal();
        string ToStringAdmin();
        bool insertSoftwarePertenece(NodoSoftware*,string*, string, int);
        bool pertenece(string*, string, int);//puntero de arreglo, comparado con input, para una longitud fija
        Software* retornarSoftwareMin(string);
        Software* retornarSoftwareNormal(string);
        Software* retornarSoftwareAdmin(string);

        bool deleteSoftware(string);
        NodoSoftware* getPrimero();
};


//constructor
ListaSoftware::ListaSoftware(){
    this->primero = NULL;
    this->ultimo = NULL;
    this->cantidadSoftware = 0;
}

//inserta un nuevo Software
//no se agregara un nuevoSoftware si ya existe otro con el mismo nombre de software
bool ListaSoftware::insertSoftware(NodoSoftware *newNode){
    if(searchSoftware(newNode->getSoftware()->getSoftwareName())){
        cout<<"El software de nombre: "<<newNode->getSoftware()->getSoftwareName()<<" ya existe en esta computadora"<<endl;
        cout<<"No se agregara"<<endl;
        return false;
    }
    
    if(primero == NULL){
        primero = newNode;
        ultimo = newNode;
        cantidadSoftware++;
    }
    else{
        ultimo->setNextNode(newNode);
        newNode->setPrevNode(ultimo);
        ultimo = newNode;
        cantidadSoftware++;
    }

    return true;
}



//searchSoftware:
//busca un software a partir de su nombre(softwareName)
//retorna true si existe dicho software
//retorna false luego de buscar por toda la lista
bool ListaSoftware::searchSoftware(string wantedSoftwareName){
    NodoSoftware *aux = primero;
    while(aux != NULL){
        if(aux->getSoftware()->getSoftwareName() == wantedSoftwareName){
            return true;
        }
        aux = aux->getNextNode();
    }
    return false;
    
}
//retorna la cantidad de software instalado en biblioteca
int ListaSoftware::getCantidadSoftware(){return this->cantidadSoftware;}

//llamar a esta funcion para mostrar informacion apta para todo publico
//debe mostrar software que sea de clasificacion para todo publico
//y debe no ser exclusivo de admin(como el software de seguridad)
string ListaSoftware::ToStringMin(){
    NodoSoftware *aux = primero;
    string r = "";
    while(aux != NULL){
        if(aux->getSoftware()->getClasificacionEdad() < 18 && aux->getSoftware()->adminExclusive() == false){//control de informacion
            r += aux->getSoftware()->ToString()+"\n";
        }
        aux = aux->getNextNode();
    } 
    return r;
}
//llamar a esta funcion para mostrar info para 18+ (incluyendo para todo publico)
string ListaSoftware::ToStringNormal(){
    NodoSoftware *aux = primero;
    string r = "";
    while(aux != NULL){
        if(aux->getSoftware()->adminExclusive() == false){//si no es info exclusiva de admin, podra verlo
            r += aux->getSoftware()->ToString()+"\n";
        }
        aux = aux->getNextNode();
    }
    return r;
}

//(funcion de admin) llamar a esta funcion para mostrar toda info sin ningun tipo de filtro
string ListaSoftware::ToStringAdmin(){
    NodoSoftware *aux = primero;
    string r = "";
    while(aux != NULL){
        r += aux->getSoftware()->ToString()+"\n";//acumula info y envia un '\n' para hacer espacio entre objeto
        aux = aux->getNextNode();
    }
    return r;
}

bool ListaSoftware::insertSoftwarePertenece(NodoSoftware* newNode,string* arregloBase, string input, int longitud){
    if(searchSoftware(newNode->getSoftware()->getSoftwareName())){
        cout<<"El software de nombre: "<<newNode->getSoftware()->getSoftwareName()<<" ya existe en esta computadora"<<endl;
        cout<<"No se agregara"<<endl;
        return false;
    }

    if(pertenece(arregloBase, input, longitud) == false){
        cout<<input<<" no pertenece a las opciones para la creacion de este Software, no se creara"<<endl;
        return false;
    }

    if(primero == NULL){
        primero = newNode;
        ultimo = newNode;
        cantidadSoftware++;
        return true;
    }
    
    ultimo->setNextNode(newNode);
    newNode->setPrevNode(ultimo);
    ultimo = newNode;
    cantidadSoftware++;
    return true;

}

//funcion usada para determinar si el input esta dentro de las opciones disponibles
//true: si pertenece, se puede crear
//false: no pertenece, no se debe crear
bool ListaSoftware::pertenece(string* arregloBase, string input, int longitud){
    string *pointer = arregloBase;
    for(int i = 0;i < longitud;i++){
        if(pointer[i] == input){
            return true;
        }
    }
    return false;
}

//retorna el software que coincida con el nombre ingresado y que sea apto para menores de 18
//restriccion de contenido de admin
Software* ListaSoftware::retornarSoftwareMin(string wantedSoftwareName){
    NodoSoftware *aux = primero;
    while(aux != NULL){
        if((aux->getSoftware()->getSoftwareName() == wantedSoftwareName) && aux->getSoftware()->getClasificacionEdad() < 18
        && aux->getSoftware()->adminExclusive() == false){
            //restriccion de edad y restriccion de admin
            return aux->getSoftware();
        }
        aux = aux->getNextNode();
    }
    return NULL;
}

//retorna el Software que coincida con el nombre ingresado
//restriccion de contenido de admin
Software* ListaSoftware::retornarSoftwareNormal(string wantedSoftwareName){
    NodoSoftware *aux = primero;
    while(aux != NULL){
        if((aux->getSoftware()->getSoftwareName() == wantedSoftwareName) && aux->getSoftware()->adminExclusive() == false){
            //restriccion de admin
            return aux->getSoftware();
        }
        aux = aux->getNextNode();
    }
    return NULL;
}

//retorna el software que coincida con el nombre ingresado
Software* ListaSoftware::retornarSoftwareAdmin(string wantedSoftwareName){
    NodoSoftware *aux = primero;
    while(aux != NULL){
        if((aux->getSoftware()->getSoftwareName() == wantedSoftwareName)){
            //sin restricciones
            return aux->getSoftware();
        }
        aux = aux->getNextNode();
    }
    return NULL;
}


bool ListaSoftware::deleteSoftware(string softwareName){
    NodoSoftware* aux = primero;
    if(aux == NULL){
        return false;
    }
    //si solo hay un nodo
    if(primero->getNextNode() == NULL){
        primero = NULL;
        aux->~NodoSoftware();
        return true;
    }

    //si es el primero
    if(aux->getSoftware()->getSoftwareName() == softwareName){
            primero->getNextNode()->setPrevNode(NULL);
            primero = primero->getNextNode();
            aux->~NodoSoftware(); 

            this->cantidadSoftware--;
            return true;
        }
    //si es el ultimo
    if(ultimo->getSoftware()->getSoftwareName() == softwareName){
        aux = ultimo;
        ultimo->getPrevNode()->setNextNode(NULL);
        ultimo = ultimo->getPrevNode();
        aux->~NodoSoftware();
        this->cantidadSoftware--;
        return true;
    }
    //si esta entre medio
    while(aux != NULL){
        if(aux->getSoftware()->getSoftwareName() == softwareName){
            aux->getPrevNode()->setNextNode(aux->getNextNode());
            aux->getNextNode()->setPrevNode(aux->getPrevNode());
            aux->~NodoSoftware();
            this->cantidadSoftware--;
            return true;
        }
        aux = aux->getNextNode();
    }
}

NodoSoftware* ListaSoftware::getPrimero(){return this->primero;}