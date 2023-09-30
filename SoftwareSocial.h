#pragma once

#include <iostream>

#include "Software.h"
#include "ListaDeListaUsuario.h"
using namespace std;
//es una clase derivada de Software
class SoftwareSocial : public Software{
    private:
        ListaDeListaUsuario *todosLosListadosDeAmigos;//listaEnlazada que trabaja con las listas de amigos de todos los usuarios ingresados
    
    public:
        SoftwareSocial(string,string,int, int);
        ~SoftwareSocial();
        string verAmigos(string);
        bool agregarAmigo(string,string);
        bool eliminarAmigo(string,string);
        int cuantosAmigosTiene(string);
        bool crearListadoParaNuevoUsuario(Usuario*);
        string ToString();
        string getObjectName();
        string verAmigosPosibles(Usuario*);
};

//constructor de SoftwareSocial
SoftwareSocial::SoftwareSocial(string softwareName,string devName,int clasificacionEdad, int precio):Software(softwareName,devName,clasificacionEdad,precio){
    this->todosLosListadosDeAmigos = new ListaDeListaUsuario();
}
//destructor de SoftwareSocial
SoftwareSocial::~SoftwareSocial(){}

//solo necesito saber de quien es el listado, por eso necesito saber el nombre del usuario que esta solicitando ver su listado de amigos
string SoftwareSocial::verAmigos(string nombreUsuarioActual){
    //de todas las listas,cual es del usuario
    ListaUsuario* listadoAmigos = this->todosLosListadosDeAmigos->findListByName(nombreUsuarioActual);
    if(listadoAmigos == NULL){
        return "Error Fatal:Por alguna razon el usuario actual no tiene su propia lista de amigos";
    }
    return listadoAmigos->verUsuarios();
}

//desde el softwareSocial se llama la funcion para agregar a un amigo a partir de su nombre
//Se debe entregar tambien el nombre del usuario actual
//se crea un nuevo nodo para la lista enlazada unica de este usuario
//si el amigo ya existe en su listado no se agregara y se informara al respecto
//idealmente cuando A es amigo de B, B tambien es amigo de A
//por lo que hay que llamar a esta funcion dos veces cambiando unicamente quien es amigo y quien es usuario
//false: si se intenta agregar a un menor siendo mayor, o si un menor intenta agregar a un mayor
//o si no existe
bool SoftwareSocial::agregarAmigo(string nombreAmigo,string nombreUsuarioActual){
    Usuario *amigo = this->buscarUsuario(nombreAmigo);//creo un puntero que apunta a donde apunta la funcion buscar amigo
    //primero se debe preguntar y frenar en caso de NULL
    if(amigo == NULL){
        cout<<"Ese usuario no existe"<<endl;
        return false;
    }
    //y luego puedo preguntar si se estan cumpliendo las reglas establecidas
    Usuario *usuarioActual = this->buscarUsuario(nombreUsuarioActual);
    if(amigo->getAge() <18 && usuarioActual->getAge() > 18){
        cout<<"No se permite agregar a menores de edad"<<endl;
        return false;
    }
    if(usuarioActual->getAge() < 18 && amigo->getAge() >18){
        cout<<"No se permite que un menor de edad agrege a un mayor de edad"<<endl;
        return false;
    }

    //este es el listado de amigos del usuarioActual
    ListaUsuario* listadoAmigos = this->todosLosListadosDeAmigos->findListByName(nombreUsuarioActual);
    if(listadoAmigos == NULL){
        cout<<"Error Fatal:Por alguna razon el usuario actual no tiene su propia lista de amigos"<<endl;
        return false;
    }
    NodoUsuario *nodoAmigo = new NodoUsuario(amigo);//crea el nodo con el puntero del amigo que encontro en la lista de usuarios en el software
    if(listadoAmigos->insertUsuario(nodoAmigo))
    {
        string logsNuevoAmigo = "* "+nombreUsuarioActual+" ha agregado a "+nombreAmigo+" como su amigo";
        this->crearMasLogs(logsNuevoAmigo);
        return true;
    }
    //finalmente lo agrega al listado de amigos del usuarioActual
}

//Se elimina un amigo de la lista de amigos del usuarioActual
//al igual que en agregarAmigo
//esta funcion se debe ejecutar 2 veces pero asegurando que la primera vez sea true
//true: se elimina
//false: no se encuentra(y no se elimina)
bool SoftwareSocial::eliminarAmigo(string nombreAmigo,string nombreUsuarioActual){
    ListaUsuario* listadoAmigos = this->todosLosListadosDeAmigos->findListByName(nombreUsuarioActual);
    if(listadoAmigos == NULL){
        cout<<"Error Fatal:Por alguna razon el usuario actual no tiene su propia lista de amigos"<<endl;
        return false;
    }
    return listadoAmigos->deleteUsuario(nombreAmigo);
}

//retorna la cantidad de amigos de un usuario
//idealmente que sea el usuario actual que logeo en el software
int SoftwareSocial::cuantosAmigosTiene(string nombreUsuarioActual){
    ListaUsuario* listadoAmigos = this->todosLosListadosDeAmigos->findListByName(nombreUsuarioActual);
    return listadoAmigos->getCantidadUsuario();
}

//crea logs, crea un listado nuevo designado para este usuario y retorna true
//retorna false si el usuario ya tiene un listado asignado a su nombre
bool SoftwareSocial::crearListadoParaNuevoUsuario(Usuario *usuarioActual){
    if(this->todosLosListadosDeAmigos->isUserHere(usuarioActual->getUserName())){
        return false;//el usuario ya esta incluido con un listado propio
    }
    //el usuario necesita un listado
    ListaUsuario *listadoAmigos = new ListaUsuario();//se crea el listado
    NodoListaUsuario *nodoListado = new NodoListaUsuario(listadoAmigos,usuarioActual->getUserName());//se crea el nodo
    this->todosLosListadosDeAmigos->insertNode(nodoListado);//se agrega el nodo que contiene el listado
    //ahora dicho usuario deberia tener su listado preparado para poder agregar amigos
    this->crearMasLogs("*Se ha designado una lista enlazada para el usuario: "+usuarioActual->getUserName());
    return true;
}

//toString
//imprime las caracteristicas de la clase padre(ToStringPadre()) junto con las de la clase derivada
//en este caso no tiene diferencias
string SoftwareSocial::ToString(){
    return this->ToStringPadre();
}

//retorna el tipo de objeto: SoftwareSocial
string SoftwareSocial::getObjectName(){return "SoftwareSocial";}


//teniendo el software directamente
//evalua el tipo de Usuario
//y decide que amigos que este usuarioActual todavia no agrega pueda ver
//retorna "noHay" si es que no quedan mas amigos para agregar
string SoftwareSocial::verAmigosPosibles(Usuario* usuarioActual){
    int edadActual = usuarioActual->getAge();//edad de usuarioUsuario(el que esta logeado ahora mismo)
    string r = "";//variable string a la que se concatenaran los amigos potenciales
    ListaUsuario *listadoAmigos = this->todosLosListadosDeAmigos->findListByName(usuarioActual->getUserName());//listado del usuario logeado
    //this->getUsuariosActuales()->searchUsuario();
    NodoUsuario *usuarioRegistrado = getUsuariosActuales()->getPrimero();//apunta al primero de los usuarios registrados en software
    while(usuarioRegistrado != NULL){
        if(usuarioRegistrado->getUsuario()->getUserName() != usuarioActual->getUserName()){
            if(!(listadoAmigos->searchUsuario(usuarioRegistrado->getUsuario()->getUserName()))){
                //le pregunto si el usuario registrado en software no esta en la lista de amigos
                int edadOtroUsuario = usuarioRegistrado->getUsuario()->getAge();//se va actualizando el valor de la edad
                if(edadActual < 18 && edadOtroUsuario < 18 || edadActual >= 18 && edadOtroUsuario >= 18){//que ambos sean menores o ambos sean mayores
                    r = r+usuarioRegistrado->getUsuario()->getUserName()+"\n";
                }
            }
        }

        usuarioRegistrado = usuarioRegistrado->getNextNode();//actualizo el nodo para que avance
    }
   
    if(r == ""){
        cout<<"No hay ningun amigo potencial que no haya sido agregado para ver"<<endl;;
        return "noHay";
    }

    return r;
}