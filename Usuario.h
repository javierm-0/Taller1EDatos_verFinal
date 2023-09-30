#pragma once

#include <iostream>
using namespace std;


//clase padre Usuario
class Usuario{
    private:
        string userName,passWord;
        int age = 0;//usado para determinar entre usuario y menor
        //string mail;
        //bool logsAccess;//si es admin sera true, esto permite la visibilidad de logs en los softwares

    public:
        Usuario(string,string,int);
        ~Usuario();
        string getUserName();
        string getPassWord();
        int getAge();
        virtual string getObjectName()=0;//funcion virtual para saber el 'tipo' de objeto

    
};
//constructor
Usuario::Usuario(string userName,string passWord,int age){
    this->userName = userName;
    this->passWord = passWord;
    this->age = age;

}
//destructor
Usuario::~Usuario(){}
//getter
string Usuario::getUserName(){return this->userName;}
string Usuario::getPassWord(){return this->passWord;}
int Usuario::getAge(){return this->age;}
