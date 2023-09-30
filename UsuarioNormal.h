#pragma once


#include <iostream>
#include "Usuario.h"

using namespace std;
//es una clase derivada de Usuario
class UsuarioNormal : public Usuario{
    private:
        string mail;
    public:
        UsuarioNormal(string,string,int,string);
        ~UsuarioNormal();
        string getObjectName() override;
};

//constructor de UsuarioNormal
UsuarioNormal::UsuarioNormal(string userName,string passWord,int age,string mail):Usuario(userName,passWord,age){
    this->mail = mail;
}
//destructor de UsuarioNormal
UsuarioNormal::~UsuarioNormal(){}
//retorna el tipo de objeto(UsuarioNormal)
string UsuarioNormal::getObjectName(){return "UsuarioNormal";}