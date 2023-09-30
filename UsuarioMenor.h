#pragma once


#include <iostream>
#include "Usuario.h"

using namespace std;
//es una clase derivada de Usuario
class UsuarioMenor : public Usuario{
    public:
        UsuarioMenor(string,string,int);
        ~UsuarioMenor();
        string getObjectName() override;
};
//constructor de UsuarioMenor
UsuarioMenor::UsuarioMenor(string userName,string passWord,int age):Usuario(userName,passWord,age){}
//destructor de UsuarioMenor
UsuarioMenor::~UsuarioMenor(){}
//retorna el tipo de objeto(UsuarioMenor)
string UsuarioMenor::getObjectName(){return "UsuarioMenor";}