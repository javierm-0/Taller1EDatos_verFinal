#pragma once

#include <iostream>
#include "NodoUsuario.h"
using namespace std;

//lista enlazada doble de NodoUsuario
class ListaUsuario{
    private:
        NodoUsuario *primero,*ultimo;
        int cantidadUsuario; //cantidad de usuarios en la lista
    public:
        ListaUsuario();
        ~ListaUsuario();
        NodoUsuario* getPrimero();
        bool insertUsuario(NodoUsuario*);
        bool insertUsuario(Usuario*);
        bool searchUsuario(string);
        bool searchByPassUsuario(string,string);
        bool deleteUsuario(string);
        Usuario* searchAndReturnUsuario(string);
        string verUsuarios();
        int getCantidadUsuario();
        Usuario* getUsuarioFromPosition(int);
        void vaciarLaLista();
        NodoUsuario* eliminarElPrimero();
        string verUsuariosSinRepeticion(ListaUsuario*);
};

//constructor de ListaUsuario
ListaUsuario::ListaUsuario(){
    this->primero = NULL;
    this->ultimo = NULL;
}
//destructor de ListaUsuario(destruye los nodos pero no deberia destruir el usuario interno)
ListaUsuario::~ListaUsuario(){
    NodoUsuario *aux = primero, *aux2 = primero;
    if(primero->getNextNode() != NULL){//hay mas de un nodo
        while(aux != NULL){
            aux2 = aux;//apunta al aux
            aux = aux->getNextNode();//aux avanza
            aux2->~NodoUsuario();//destruye el NodoUsuario anterior a aux
        }//y cuando aux sea NULL se acaba
    }
}

//getter
NodoUsuario* ListaUsuario::getPrimero(){return this->primero;}

//inserta un nuevo nodo Usuario
//no se agregara un nuevoUsuario si ya existe otro con el mismo userName
//true: usuario nuevo y se agrega
//false: usuario repetido y no se agrega
bool ListaUsuario::insertUsuario(NodoUsuario* newNode){
    if(searchUsuario(newNode->getUsuario()->getUserName())){
        cout<<"El usuario de nombre: "<<newNode->getUsuario()->getUserName()<<" ya existe"<<endl;
        cout<<"No se agregara"<<endl;
        return false;
    }

    
    
    if(primero == NULL){
        primero = newNode;
        ultimo = newNode;
        cantidadUsuario++;
        return true;
    }
    else{
        ultimo->setNextNode(newNode);
        newNode->setPrevNode(ultimo);
        ultimo = newNode;
        cantidadUsuario++;
        return true;
    }
}


//retorna un bool luego de comparar el input con todos los nombres de los usuarios
//true: existe un usuario con dicho nombre
//false: no existe un usuario con dicho nombre
bool ListaUsuario::searchUsuario(string wantedUserName){
    NodoUsuario* aux = primero;
    while(aux != NULL){
        if(aux->getUsuario()->getUserName() == wantedUserName){
            return true;
        }
        aux = aux->getNextNode();
    }
    return false;
    
}

//retorna un bool luego de comparar el input con todas las password de los usuarios
//true: existe un usuario con dicho nombre
//false: no existe un usuario con dicho nombre
bool ListaUsuario::searchByPassUsuario(string wantedUserPass,string userPassIsFrom){
    NodoUsuario* aux = primero;
    while(aux != NULL){
        if(aux->getUsuario()->getPassWord() == wantedUserPass && aux->getUsuario()->getUserName() == userPassIsFrom){
            return true;
        }
        aux = aux->getNextNode();
    }
    return false;
    
}

//saca a un nodo amigo/usuario de la lista y lo elimina de la memoria
//en el caso de las listas de amigos estan seran rellenadas con nodos creados para unicamente esa lista
//true: existe y lo elimina
//false: no lo encuentra
bool ListaUsuario::deleteUsuario(string nombreUser){
    NodoUsuario* aux = primero;
    if(aux == NULL){
        return false;
    }
    //si solo hay un nodo
    if(primero->getNextNode() == NULL){
        primero = NULL;
        aux->~NodoUsuario();
        return true;
    }

    //si es el primero
    if(aux->getUsuario()->getUserName() == nombreUser){
            primero->getNextNode()->setPrevNode(NULL);
            primero = primero->getNextNode();
            aux->~NodoUsuario();
            this->cantidadUsuario--;
            return true;
        }
    //si es el ultimo
    if(ultimo->getUsuario()->getUserName() == nombreUser){
        aux = ultimo;
        ultimo->getPrevNode()->setNextNode(NULL);
        ultimo = ultimo->getPrevNode();
        aux->~NodoUsuario();
        this->cantidadUsuario--;
        return true;
    }
    //si esta entre medio
    while(aux != NULL){
        if(aux->getUsuario()->getUserName() == nombreUser){
            aux->getPrevNode()->setNextNode(aux->getNextNode());
            aux->getNextNode()->setPrevNode(aux->getPrevNode());
            aux->~NodoUsuario();
            this->cantidadUsuario--;
            return true;
        }
        aux = aux->getNextNode();
    }
}

//retorna un puntero con la direccion del usuario que se esta buscando
//retorna NULL si no encuentra ningun usuario cuyo nombre de usuario coincida
Usuario* ListaUsuario::searchAndReturnUsuario(string wantedUserName){
    NodoUsuario* aux = primero;
    if(aux == NULL){
        cout<<"Esta vacio"<<endl;
        return NULL;
    }

    while(aux != NULL){
        if(aux->getUsuario()->getUserName() == wantedUserName){
            return aux->getUsuario();
        }
        aux = aux->getNextNode();
    }
    return NULL;
}

//retorna los nombres de los usuarios
string ListaUsuario::verUsuarios(){
    string r = "";
    NodoUsuario *aux = primero;
    while(aux != NULL){
        r = r+aux->getUsuario()->getUserName()+"\n";
        aux = aux->getNextNode();
    }

    if(r == ""){
        return "No hay ningun usuario/amigo para ver";
    }

    return r;
}

//retorna la cantidad de usuarios
int ListaUsuario::getCantidadUsuario(){return this->cantidadUsuario;}

//recibe un usuario, crea un nodo usuario y lo inserta
//no se agregara un nuevoUsuario si ya existe otro con el mismo userName
bool ListaUsuario::insertUsuario(Usuario* newUser){
    NodoUsuario *newNode = new NodoUsuario(newUser);
    if(searchUsuario(newNode->getUsuario()->getUserName())){
        return false;
    }
    if(primero == NULL){
        primero = newNode;
        ultimo = newNode;
        cantidadUsuario++;
        return true;
    }
    ultimo->setNextNode(newNode);
    newNode->setPrevNode(ultimo);
    ultimo = newNode;
    cantidadUsuario++;
    return true;
}

//con un contador va comparando si llego a la posicion indicada
//pos: posicion
Usuario* ListaUsuario::getUsuarioFromPosition(int pos){
    int contador = 0;
    NodoUsuario* aux = primero;
    if(aux == NULL){
        cout<<"Esta vacio"<<endl;
        return NULL;
    }

    while(aux != NULL){
        if(contador == pos){
            return aux->getUsuario();
        }
        contador++;
        aux = aux->getNextNode();
    }

    if(pos >= contador){//se quedo sin nodos y no llego a que contador sea igual a posicion dentro del while
        return NULL;
    }
}

//corre un while de eliminar el primer nodo hasta que el primer nodo sea NULL
void ListaUsuario::vaciarLaLista(){
    NodoUsuario* aux;
    while(aux != NULL){
        aux = this->eliminarElPrimero();//actualiza el valor de aux
    }
    if(aux == NULL){
        return;
    }
    
}

//elimina el primer nodo de la lista
//retorna el actual primer nodo de la lista luego de eliminar el primer nodo
//retornara NULL cuando no queden nodos
NodoUsuario* ListaUsuario::eliminarElPrimero(){
    NodoUsuario *aux = primero;
    if(primero == NULL){//si esta vacio
        return NULL;
    }

    if(primero->getNextNode() == NULL){//si solo hay 1 nodo
        primero = NULL;
        aux->~NodoUsuario();
        this->cantidadUsuario--;
        return primero;//retorna NULL
    }

    primero = primero->getNextNode();//si hay 2 o mas, actualiza el primero y elimina el antiguo primero
    primero->setPrevNode(NULL);//corta la referencia que el puntero hace al nodo anterior
    aux->~NodoUsuario();//llama al destructor que solo elimina el nodo, no lo que contenga porque sino me quedo sin usuario
    return primero;
}

string ListaUsuario::verUsuariosSinRepeticion(ListaUsuario* listadoAmigosDeActual){
    NodoUsuario *aux = primero;
    if(aux == NULL){
        return "No hay nada?";
    }
    while(aux != NULL){

    }
}