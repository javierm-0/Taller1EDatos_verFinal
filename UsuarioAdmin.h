#pragma once


#include <iostream>
#include "Usuario.h"

using namespace std;
//es una clase derivada de Usuario
class UsuarioAdmin : public Usuario{
    private:
        string mail;
    public:
        UsuarioAdmin(string,string,int,string);
        ~UsuarioAdmin();
        string getObjectName() override;
};
//constructor de UsuarioAdmin
UsuarioAdmin::UsuarioAdmin(string userName,string passWord,int age,string mail):Usuario(userName,passWord,age){
    this->mail = mail;
}
//destructor de UsuarioAdmin
UsuarioAdmin::~UsuarioAdmin(){}
//retorna el tipo de objeto(UsuarioAdmin)
string UsuarioAdmin::getObjectName() {return "UsuarioAdmin";}