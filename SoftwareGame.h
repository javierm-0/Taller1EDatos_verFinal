#pragma once

#include <iostream>

#include "Software.h"
using namespace std;
//es una clase derivada de Software
class SoftwareGame : public Software{
    private:
        string *partidas;//reserva hasta 100 partidas a la vez
        string genero;//genero del juego
        int cantidadPartidas;//cantidad de partidas creadas por todos los usuarios en el software
    public:
        SoftwareGame(string,string,int,int,string);
        ~SoftwareGame();
        string getGenero();
        string ToString();
        void crearPartida(string);
        string verPartidas();
        bool borrarPartida(string);
        string getObjectName();
};

//constructor de SoftwareGame
SoftwareGame::SoftwareGame(string softwareName,string devName,int clasificacionEdad, int precio, string genero):Software(softwareName,devName,clasificacionEdad,precio){
    this->genero = genero;
    this->partidas = new string[100];
    this->cantidadPartidas = 0;
}
//destructor de SoftwareGame
SoftwareGame::~SoftwareGame(){}

//getter
string SoftwareGame::getGenero(){return this->genero;}

//toString
//imprime las caracteristicas de la clase padre(ToStringPadre()) junto con las de la clase derivada
string SoftwareGame::ToString(){
    string texto = "";
    texto += this->ToStringPadre()+" ,genero: "+this->genero;
    return texto;
}

//crea una nueva partida
//limitado hasta 100 partidas
void SoftwareGame::crearPartida(string nuevaPartida){
    if(cantidadPartidas < 100){
        this->partidas[cantidadPartidas] = nuevaPartida;
        this->cantidadPartidas++;
    }
    else{
        cout<<"Error. se debe eliminar al menos 1 partida antes de continuar creando partidas"<<endl;
    }
}

//mostrar todas las partidas en el software hasta ahora
string SoftwareGame::verPartidas(){
    string r = "";
    string *point = this->partidas;
    for(int i = 0;i < this->cantidadPartidas;i++){
        r += point[i]+"\n";
    }
    return r;
}

//elimina a partir del nombre de la partida
//para facilitar el menu deberia correr 'verPartidas()'
//antes de preguntarle por input para eliminar alguna partida
//true: encuentra y borra la partida
//false: no la encuentra
bool SoftwareGame::borrarPartida(string partidaABorrar){
    string *point = this->partidas;
    int i = 0;
    for(i =0;i < this->cantidadPartidas;i++){
        if(point[i] == partidaABorrar){
            break;
        }
    }
    if(i == this->cantidadPartidas){
        cout<<"No se pudo encontrar la partida"<<endl;
        return false;
    }
    for(int k = i;k < this->cantidadPartidas-1;k++){//desde que se encuentra el dato a eliminar, comienza la sobreescritura
        this->partidas[k] = this->partidas[k+1];//copia los datos del sigt en el actual
    }
    this->cantidadPartidas--;//deberia mostrar 1 menos ahora que fue eliminado
    return true;
}

//retorna el tipo de objeto(SoftwareGame)
string SoftwareGame::getObjectName(){return "SoftwareGame";}