#pragma once
#include <iostream>

using namespace std;
#include "Software.h"
//clase del tipo NodoSoftware, es un Nodo que almacena 1 puntero a 1 Software
class NodoSoftware{
    private:
        Software *software;
        NodoSoftware *nextNode,*prevNode;
    public:
        NodoSoftware(Software*);
        ~NodoSoftware();
        Software *getSoftware();
        NodoSoftware *getNextNode();
        NodoSoftware *getPrevNode();
        void setNextNode(NodoSoftware*);
        void setPrevNode(NodoSoftware*);
    
};
//constructor
NodoSoftware::NodoSoftware(Software* software){
    this->software = software;
    this->nextNode = NULL;
    this->prevNode = NULL;
}
//destructor de Nodo Software
NodoSoftware::~NodoSoftware(){
    this->software->hardReset();
}

//getter y setter
Software* NodoSoftware::getSoftware(){return this->software;}

NodoSoftware* NodoSoftware::getNextNode(){return this->nextNode;}
NodoSoftware* NodoSoftware::getPrevNode(){return this->prevNode;}

void NodoSoftware::setNextNode(NodoSoftware *nextNode){
    this->nextNode = nextNode;
}

void NodoSoftware::setPrevNode(NodoSoftware *prevNode){
    this->prevNode = prevNode;
}

