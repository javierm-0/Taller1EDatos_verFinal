#pragma once
#include <iostream>

#include "ListaUsuario.h"
using namespace std;
//es un nodo de ListaUsuario. representa los amigos de un usuario en un software
//para saber con mayor rapidez de quien son estos amigos tendra un string del usuario del que se habla
class NodoListaUsuario{
    private:
        ListaUsuario *listaDeAmigos;
        NodoListaUsuario *nextNode,*prevNode;
        string nombreUsuario;
        int cantidadAmigos;
    public:
        NodoListaUsuario(ListaUsuario*,string);
        ~NodoListaUsuario();
        ListaUsuario *getListaDeAmigos();
        string getNombreUsuario();
        NodoListaUsuario *getNextNode();
        NodoListaUsuario *getPrevNode();
        void setNextNode(NodoListaUsuario*);
        void setPrevNode(NodoListaUsuario*);
        void agregarAmigo(NodoUsuario*);

};
//constructor del Nodo de ListaUsuario, necesita el listado de amigos y su nombre de usuario
NodoListaUsuario::NodoListaUsuario(ListaUsuario* listaDeAmigos,string nombreUsuario){
    this->nextNode = NULL;
    this->prevNode = NULL;
    this->nombreUsuario = nombreUsuario;
    this->cantidadAmigos = 0;
    this->listaDeAmigos = listaDeAmigos;
}
//destructor del Nodo de ListaUsuario
//destruye tambien a la listaUsuario que esta dentro
NodoListaUsuario::~NodoListaUsuario(){
    this->listaDeAmigos->~ListaUsuario();
}

//getter
ListaUsuario* NodoListaUsuario::getListaDeAmigos(){return this->listaDeAmigos;}
//getter
string NodoListaUsuario::getNombreUsuario(){return this->nombreUsuario;}

//getter
NodoListaUsuario* NodoListaUsuario::getNextNode(){return this->nextNode;}
//getter
NodoListaUsuario* NodoListaUsuario::getPrevNode(){return this->prevNode;}
//setter
void NodoListaUsuario::setNextNode(NodoListaUsuario *nextNode){
    this->nextNode = nextNode;
}
//setter
void NodoListaUsuario::setPrevNode(NodoListaUsuario *prevNode){
    this->prevNode = prevNode;
}

//se llama directamente a la lista de amigos de un usuario
//para agregar a su nuevo amigo y se suma 1 a la cantidad de amigos
void NodoListaUsuario::agregarAmigo(NodoUsuario *newNode){
    this->listaDeAmigos->insertUsuario(newNode);
    this->cantidadAmigos++;
}