#pragma once

#include <iostream>

#include "ListaUsuario.h"

using namespace std;
//clase padre Software
class Software{
    private:
        string softwareName, devName;
        int clasificacionEdad;
        int precio;
        ListaUsuario *usuariosActuales;//todos los usuarios que han logeado en el software desde la ejecucion del programa
        string logs;//usado para acumular los 'logs' del software(solo un 'UsuarioAdmin' deberia poder ver esto)
    public:
        Software(string,string,int,int);
        ~Software();
        string getSoftwareName();
        int getClasificacionEdad();
        ListaUsuario *getUsuariosActuales();

        void agregarUsuarioAlSoftware(Usuario*,Software*);
        string ToStringPadre();
        bool adminExclusive();
        virtual string ToString() = 0;//funcion virtual que se implementara en las clases derivadas
        string verLogs();
        void crearMasLogs(string);

        Usuario *buscarUsuario(string);
        virtual string getObjectName() = 0;
        string verNombreUsuarios();
        void hardReset();
       

        

};
//constructor
Software::Software(string softwareName,string devName,int clasificacionEdad, int precio){
    this->softwareName = softwareName;
    this->devName = devName;
    this->clasificacionEdad = clasificacionEdad;
    this->precio = precio;
    this->usuariosActuales = new ListaUsuario();
    this->logs = "";
}
//destructor
Software::~Software(){
    this->usuariosActuales->~ListaUsuario();
}
//getter
string Software::getSoftwareName(){return this->softwareName;}
int Software::getClasificacionEdad(){return this->clasificacionEdad;}
//retorna la lista de los usuarios que han entrado al software
ListaUsuario* Software::getUsuariosActuales(){return this->usuariosActuales;}

//le agrega un usuario(derivado de usuario) al listado de usuarios que han usado dicho software
//crea logs al agregar correctamente un usuario
void Software::agregarUsuarioAlSoftware(Usuario* user,Software* softwareSeleccionado){
    NodoUsuario *userNode = new NodoUsuario(user);
    
    if(usuariosActuales->insertUsuario(userNode)){
        string logs = "El usuario: "+user->getUserName()+", ha ingresado al Software: "+softwareSeleccionado->getSoftwareName();
        softwareSeleccionado->crearMasLogs(logs);
    }
}

//Imprime las caracteristicas del objeto padre
string Software::ToStringPadre()
{
    if(this->adminExclusive()){//si solo el admin puede verlo
        return"nombre del software: "+this->softwareName+", nombre del desarrollador: "+this->devName+", clasificacion: ADMIN, precio: "+to_string(this->precio);
    }

    if(clasificacionEdad >= 18){
        return "nombre del software: "+this->softwareName+", nombre del desarrollador: "+this->devName+", clasificacion: 18+, precio: "+to_string(this->precio);
    }
    else{
        return "nombre del software: "+this->softwareName+", nombre del desarrollador: "+this->devName+", clasificacion: E for everyone, precio: "+to_string(this->precio);
    }
}

//funcion usada para preguntar si se puede acceder a la informacion
//false: todos pueden verlo
//true: solo el admin puede verlo
//por default false, en el 'SecuritySoftware' sera true
bool Software::adminExclusive(){return false;}

//retorna los logs(opcion solo deberia ser visible para admin)
string Software::verLogs(){return this->logs;}

//esta funcion ocurre de manera interna mientras el usuario logea en un Software
//y cuando se crean archivos
void Software::crearMasLogs(string nuevoLog){
    this->logs += nuevoLog + "\n";
}

//desde el software especifico retorna el puntero del usuario a partir de su nombre
//retornara NULL si no existe dicho usuario
Usuario* Software::buscarUsuario(string nombreUsuario){
    return this->usuariosActuales->searchAndReturnUsuario(nombreUsuario);
}

//retorna el nombre de los usuarios que han usado este Software
string Software::verNombreUsuarios(){
    return this->usuariosActuales->verUsuarios();
}

//Elimina logs y datos en el Software
void Software::hardReset(){
    this->logs = "";
    this->usuariosActuales->vaciarLaLista();
}