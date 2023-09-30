#pragma once
#include <iostream>
#include "Usuario.h"

using namespace std;
//clase del tipo NodoUsuario, es un Nodo que crea y almacena 1 puntero a 1 Usuario
class NodoUsuario{
    private:
        Usuario *usuario;
        NodoUsuario *nextNode,*prevNode;
    public:
        NodoUsuario(Usuario*);
        ~NodoUsuario();
        Usuario *getUsuario();
        NodoUsuario *getNextNode();
        NodoUsuario *getPrevNode();
        void setNextNode(NodoUsuario*);
        void setPrevNode(NodoUsuario*);
    
};

//constructor de NodoUsuario
NodoUsuario::NodoUsuario(Usuario *usuario){
    this->usuario = usuario;
    this->nextNode = NULL;
    this->prevNode = NULL;
}
//destructor del NodoUsuario
NodoUsuario::~NodoUsuario(){}
//getter y setter
Usuario* NodoUsuario::getUsuario(){return this->usuario;}
NodoUsuario* NodoUsuario::getNextNode(){return this->nextNode;}
NodoUsuario* NodoUsuario::getPrevNode(){return this->prevNode;}
void NodoUsuario::setNextNode(NodoUsuario* nextNode){
    this->nextNode = nextNode;
}
void NodoUsuario::setPrevNode(NodoUsuario* prevNode){
    this->prevNode = prevNode;
}