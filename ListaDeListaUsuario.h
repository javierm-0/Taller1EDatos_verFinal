#pragma once
#include <iostream>

#include "NodoListaUsuario.h"
using namespace std;

//es una clase que representa una lista enlazada doble donde cada nodo es otra lista enlazada doble
//es usada para que cada 'Software' tenga una lista de amigos para cada usuario que este usando dicho 'Software'
class ListaDeListaUsuario{
    private:
        NodoListaUsuario *first,*last;//en ingles para diferenciarlos un poco
    public:
        ListaDeListaUsuario();
        //~ListaDeListaUsuario(); //destructor(pendiente)
        void insertNode(NodoListaUsuario*);
        ListaUsuario* findListByName(string);
        bool isUserHere(string);
        NodoListaUsuario* deleteFirst();
        void VoidList();
        
        

};
//constructor de la lista de listas de usuario
ListaDeListaUsuario::ListaDeListaUsuario(){
    this->first = NULL;
    this->last = NULL;
}

//Se deberia llamar a esta funcion cuando un usuario nuevo ingresa a un software
//Se inserta un nuevo nodo por orden de llegada(al final)
//Se inserta una nueva lista de amigos
void ListaDeListaUsuario::insertNode(NodoListaUsuario *newNode){
    if(this->findListByName(newNode->getNombreUsuario())){
        cout<<"Este usuario ya ingreso"<<endl;
        return;
    }

    if(first == NULL){
        first = newNode;
        last = newNode;
    }
    else{
        last->setNextNode(newNode);
        newNode->setPrevNode(last);
        last = newNode;
    }
}

//Se ingresa el nombre de un usuario que pertenezca al listado de usuarios que el software tiene registrado
//retorna su listado de amigos
//retorna NULL en caso de no encontrarlo o que no pertenezca al listado de ese software
ListaUsuario* ListaDeListaUsuario::findListByName(string input){
    NodoListaUsuario *aux = first;
    while(aux != NULL){
        if(aux->getNombreUsuario() == input){
            return aux->getListaDeAmigos();
        }
        aux = aux->getNextNode();
    }
    return NULL;
}

//retorna un bool
//true: ya existe un listado de amigos designado para este usuario
//false: no tiene listado aun, se debe crear
bool ListaDeListaUsuario::isUserHere(string userName){
    NodoListaUsuario *aux = first;
    while(aux != NULL){
        if(aux->getNombreUsuario() == userName){
            return true;
        }
        aux = aux->getNextNode();
    }
    return false;
}
//elimina el primer NodoListaUsuario
//retorna el actual primero despues de eliminar el primero
//retorna NULL cuando no haya primero
NodoListaUsuario* ListaDeListaUsuario::deleteFirst(){
    NodoListaUsuario *aux = first;
    if(first == NULL){
        return NULL;
    }

    if(first->getNextNode() == NULL){
        first = NULL;
        aux->~NodoListaUsuario();
        return first;//retorna NULL
    }

    first = first->getNextNode();
    first->setPrevNode(NULL);
    aux->~NodoListaUsuario();
    return first;
}


void ListaDeListaUsuario::VoidList(){
    NodoListaUsuario *aux = first;
    while(aux != NULL){
        aux = this->deleteFirst();
    }
}