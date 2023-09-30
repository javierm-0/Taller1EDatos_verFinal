#include <iostream>
#include <limits>
#include <string>

using namespace std;
#include "UsuarioMenor.h"
#include "UsuarioAdmin.h"
#include "UsuarioNormal.h"

#include "Biblioteca.h"

#include "SoftwareGame.h"
#include "SoftwareNavegador.h"
#include "SoftwareOfimatica.h"
#include "SoftwareProduccion.h"
#include "SoftwareSeguridad.h"
#include "SoftwareSocial.h"


//funcion usada para determinar si el input esta dentro de las opciones disponibles
bool pertenece(string* arregloBase, string input, int longitud){
    string *pointer = arregloBase;
    for(int i = 0;i < longitud;i++){
        if(pointer[i] == input){
            return true;
        }
    }
    return false;
}

//Se encarga de controlar el acceso al programa de manejo de software
//USUARIO: log in correcto, puede continuar
//NULL: log in incorrecto, debe reintentar o crearse una nueva cuenta
//necesita la lista de usuarios preregistrados(prepoblados) para corroborar en la lista que los datos ingresados sean correctos
Usuario* menuOpOneLOGIN(ListaUsuario* usuariosRegistrados){
    string name,pass;
    bool nameCheck,passCheck;
    cout<<"Ingrese nombre"<<endl; getline(cin,name);
    nameCheck = usuariosRegistrados->searchUsuario(name);
    if(!nameCheck){
        cout<<"No existe usuario con tal nombre"<<endl;
        return NULL;
    }
    cout<<"Ingrese password"<<endl; getline(cin,pass);
    passCheck = usuariosRegistrados->searchByPassUsuario(pass,name);
    if(!passCheck){
        cout<<"La password es incorrecta"<<endl;
        return NULL;
    }
    cout<<"nombre y password correctos"<<endl;
    cout<<"Bienvenido: "<<name<<endl;
    Usuario* userRepresentado = usuariosRegistrados->searchAndReturnUsuario(name);
    return userRepresentado;
}



//crea un nuevo usuario
//la edad debe como ser mayor que 1 y menor que 130
Usuario* menuOpZeroCreateUser(ListaUsuario* usuariosRegistrados){
    string name = "",pass = "";
 
    int age = 0;
    do//inicia la primera vez en el codigo dentro del while
    {
        cout<<"ingrese edad: "<<endl;
        bool error = !(cin>>age);//true: se intento meter string donde deberia ser int //false:(casi)todo bien
        if(error){//si activa la alerta limpia el cin
            cout<<"Ha ingresado un string o un numero float en vez de un numero entero"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //elimina los n caracteres que esten en el input
        }
        else{//si el error fue por el rango entonces solo se debe avisar
            if(age >= 130){
                cout<<"esa edad es imposiblemente alta"<<endl;
                }
            else if(age <= 1){
                cout<<"demasiado joven"<<endl;
                }
        }
    } while (age <= 1 || age > 130);//y comprueba la condicion para continuar repitiendose o salir
    
    cin.ignore();
    while(name == ""){
        cout<<"nombre: "<<endl; getline(cin,name);
    }
    while(pass == ""){
        cout<<"pass: "<<endl; getline(cin,pass);
    }

    cout<<"su nombre sera: "<<name<<", su pass sera: "<<pass<<", y su edad descrita es: "<<age<<endl;
    if(age >= 18){
        string mail = ""; string terminacionCOM = ""; string terminacionCL = "";
        while(mail == ""){
            cout<<"Ingrese su correo"<<endl; getline(cin,mail);
            //[len-4] = . ; [len-3] = c ; [len-2] = o ; [len-1] = m;
            terminacionCOM = terminacionCOM + mail[mail.length()-4] + mail[mail.length()-3] + mail[mail.length()-2] + mail[mail.length()-1];
            //[len-3] = . ; [len-2] = c ;[len-1] = l;
            terminacionCL = terminacionCL + mail[mail.length()-3] + mail[mail.length()-2] +mail[mail.length()-1];
            if(terminacionCOM != ".com" && terminacionCL != ".cl"){
                mail += ".com";
            }
        }
        cout<<"su correo sera guardado como: "<<mail<<endl;
        UsuarioNormal *nuevoUsuario = new UsuarioNormal(name,pass,age,mail);
        usuariosRegistrados->insertUsuario(nuevoUsuario);
        cout<<"cuenta completada y registrada(18+)"<<endl;
        cout<<"Bienvenido: "<<name<<endl;
        return nuevoUsuario;
    }
    else if (age < 18){
        UsuarioMenor *nuevoUser = new UsuarioMenor(name,pass,age);
        cout<<"cuenta completada y registrada(-18)"<<endl;
        cout<<"Bienvenido: "<<name<<endl;
        return nuevoUser;
    }
}

//retornara el software si es una opcion valida para el tipo de usuario
//retornara NULL sino
//se puede aprovechar el 'NULL' para informar que 
Software* elegirSoftware(Biblioteca* instalados,Usuario* usuarioActual){
    string nameSoftware = "";
    Software* softwareSeleccionado = NULL;//NULL determina que el software elegido no es valido
    //ya sea porque el nombre no coincide o porque el usuario no tiene permitido usar dicho software(seguridad)
    cout<<"mostrando opciones de Software instalado\n"<<endl;
    cout<<instalados->mostrarDatos(usuarioActual)<<endl;;
    cout<<"Ingrese el nombre del software(debe coincidir con alguno de los mostrados)"<<endl;
    getline(cin,nameSoftware);
    softwareSeleccionado = instalados->retornarSoftwarePorNombre(usuarioActual,nameSoftware);
    if(softwareSeleccionado == NULL){
        cout<<"No se pudo elegir ese Software o no esta instalado aun"<<endl;
        return NULL;
    }
    softwareSeleccionado->agregarUsuarioAlSoftware(usuarioActual,softwareSeleccionado);
    if(softwareSeleccionado->getObjectName() == "SoftwareSeguridad" && usuarioActual->getObjectName() != "UsuarioAdmin"){
        cout<<"Acceso denegado"<<endl;
        return NULL;
    }


    if(softwareSeleccionado->getObjectName() == "SoftwareSocial"){//si es SoftwareSocial
        //confio en que es un SoftwareSocial y hago casting
        SoftwareSocial *social = static_cast<SoftwareSocial*>(softwareSeleccionado);
        //debo crear el listado de amigos para el nuevo usuario
        //el cual solo lo creara si este usuario no existe todavia en la lista de listados del software
        social->crearListadoParaNuevoUsuario(usuarioActual);
        }
    
    return softwareSeleccionado;
}

//Se pide el nombre del software de la tienda para instalarlo en la computadora
void instalarSoftware(Biblioteca* instalados,Biblioteca* tienda,Usuario* usuarioActual){
    cout<<"Software disponible: \n"<<endl;
    cout<<instalados->softwareNoInstalado(tienda,usuarioActual)<<endl;
    cout<<"\nIngrese nombre del software que desea instalar"<<endl;
    string softwareAInstalar = "";
    getline(cin,softwareAInstalar);
    if(instalados->instalarSoftware(tienda,usuarioActual,softwareAInstalar)){
        cout<<"Se ha instalado correctamente: "<<softwareAInstalar<<endl;
    }
    else{
        cout<<"No existe el software o ya fue instalado"<<endl;
    }
}

//Se debe ingresar la pass de todos los usuarios que hayan usado este software
//como forma de pedir permiso para desintalar el Software de esta computadora
void desinstalarSoftware(Biblioteca* instalados,Usuario* usuarioActual){
    string nombreSoftware = "";
    cout<<instalados->mostrarDatos(usuarioActual);
    cout<<"Ingrese nombre del software que desea desintalar"<<endl;
    getline(cin,nombreSoftware);//guarda el nombreDelSoftware
    if(usuarioActual->getObjectName() == "UsuarioAdmin"){//un admin ya tiene autoridad suficiente para desintalar software
        if(instalados->desinstalarSoftware(nombreSoftware)){
            cout<<"Debido a la autoridad del status de ADMIN"<<endl;
            cout<<"Se ha desinstalado: "<<nombreSoftware<<endl;
        }
    }
    else{
        bool autoridad = true;
        Software *softwareSeleccionado = instalados->retornarSoftwarePorNombre(usuarioActual,nombreSoftware);
        cout<<"Debe ingresar la pass de los siguientes usuarios para obtener autoridad y borrar el Software:"<<endl;
        cout<<softwareSeleccionado->verNombreUsuarios();
        for(int i = 0;i < softwareSeleccionado->getUsuariosActuales()->getCantidadUsuario(); i++){
            string respuestaPass = "";
            getline(cin,respuestaPass);
            Usuario *usuarioDelSoftware = softwareSeleccionado->getUsuariosActuales()->getUsuarioFromPosition(i);
            if(respuestaPass != usuarioDelSoftware->getPassWord()){//debe ingresar cada pass
                autoridad = false;
                cout<<"pass incorrecta: no se desintalara"<<endl;
                string logIntentoDesintalar = "* "+usuarioActual->getUserName()+" intento desintalar: "+softwareSeleccionado->getSoftwareName();        
                softwareSeleccionado->crearMasLogs(logIntentoDesintalar);
                break;
            }
        }
        if(autoridad){
            if(instalados->desinstalarSoftware(nombreSoftware)){
            cout<<"Se ha desinstalado: "<<nombreSoftware<<endl;
            }
        }
    }
}

//resume en un menu los metodos de un software de juegos
void metodoGames(Usuario* usuarioActual,SoftwareGame* gameSoftware){
    string navegando = ""; bool isAdmin = usuarioActual->getObjectName() == "UsuarioAdmin";

    while (navegando != "-1")
    {
        if(isAdmin){//si es admin
            cout<<"Ingrese '0' para ver los logs de "<<gameSoftware->getSoftwareName()<<endl;//opcion de ver los logs
        }
        cout<<"Ingrese '1' para crear nueva partida"<<endl;
        cout<<"Ingrese '2' para ver las partidas creadas"<<endl;
        cout<<"Ingrese '3' para borrar partida"<<endl;
        cout<<"Ingrese '-1' para regresar al submenu anterior"<<endl;
        getline(cin,navegando);
        if(navegando == "0" && isAdmin){
            cout<<"cargando logs de: "<<gameSoftware->getSoftwareName()<<endl;
            cout<<gameSoftware->verLogs()<<endl;
        }
        else if(navegando == "1"){
            string nuevaPartida = "";
            cout<<"Ingrese cualquier nombre para su nueva partida"<<endl;
            getline(cin,nuevaPartida);
            if(nuevaPartida == ""){
                cout<<"Excepto un unico 'enter'"<<endl;
            }
            else{
                gameSoftware->crearPartida(nuevaPartida);
                string logPartida = "* "+usuarioActual->getUserName()+" ha creado la partida: "+nuevaPartida;
                gameSoftware->crearMasLogs(logPartida);
            }
        }
        else if(navegando == "2"){
            cout<<"Mostrando partidas"<<endl;
            string logVerPartida = "* "+usuarioActual->getUserName()+" ha solicitado ver las partidas";
            cout<<gameSoftware->verPartidas()<<endl;
            gameSoftware->crearMasLogs(logVerPartida);
        }
        else if(navegando == "3"){
            cout<<gameSoftware->verPartidas()<<endl;
            cout<<"Que partida desea borrar: "<<endl;
            string partidaABorrar = "";
            getline(cin,partidaABorrar);
            if(gameSoftware->borrarPartida(partidaABorrar)){
                string logDelete = "* "+usuarioActual->getUserName()+" ha borrado la partida: "+partidaABorrar;
                gameSoftware->crearMasLogs(logDelete);//se guarda el nombre X que borro Y partida del juego
            }
        }
        else if(navegando == "-1"){
            return;//salir del menu de juegos
        }
        else{
            cout<<"respuesta invalida"<<endl;
        }
    }
    
}

//resume en un menu los metodos de un software de navegador
void metodoNavegador(Usuario* usuarioActual,SoftwareNavegador* navigatorSoftware){
    string navegando = ""; bool isAdmin = usuarioActual->getObjectName() == "UsuarioAdmin";

    while (navegando != "-1")
    {
        if(isAdmin){//si es admin
            cout<<"Ingrese '0' para ver los logs de "<<navigatorSoftware->getSoftwareName()<<endl;//opcion de ver los logs
        }
        cout<<"Ingrese '1' para ingresar el nombre de una pagina visitada"<<endl;
        cout<<"Ingrese '2' para ver el historial"<<endl;
        cout<<"Ingrese '3' para borrar todo el historial"<<endl;
        cout<<"Ingrese '-1' para regresar al submenu anterior"<<endl;
        if(navegando == "0" && isAdmin){
            cout<<navigatorSoftware->verLogs();
        }
        else if(navegando == "1"){
            cout<<"Ingrese el nombre de la pagina visitada"<<endl;
            string pagina = "";
            getline(cin,pagina);
            string logHistorialUso = "* "+usuarioActual->getUserName()+" ha visitado la pagina "+pagina;
            navigatorSoftware->visitarPagina(pagina);
            navigatorSoftware->crearMasLogs(logHistorialUso);
        }
        else if(navegando == "2"){
            cout<<"Historial\n"<<endl;
            string logHistorialVer = "* "+usuarioActual->getUserName()+" ha solicitado ver el historial";
            cout<<navigatorSoftware->verHistorial()<<endl;

            navigatorSoftware->crearMasLogs(logHistorialVer);
        }
        else if(navegando == "3"){
            navigatorSoftware->borrarElementosDelHistorial(-1);
            string logHistorialDel = "* "+usuarioActual->getUserName()+" ha borrado el historial";
            cout<<"Se ha borrado todo el historial"<<endl;
            //excepto para el admin
            navigatorSoftware->crearMasLogs(logHistorialDel);
        }
        else if(navegando == "-1"){
            return;
        }
        else{
            cout<<"respuesta invalida"<<endl;
        }
    }
}

//resume en un menu los metodos de un software de ofimatica
void metodoOfimatica(Usuario* usuarioActual,SoftwareOfimatica* ofimaticaSoftware){
    string navegando = ""; bool isAdmin = usuarioActual->getObjectName() == "UsuarioAdmin";

    while (navegando != "-1")
    {
        if(isAdmin){//si es admin
            cout<<"Ingrese '0' para ver los logs de "<<ofimaticaSoftware->getSoftwareName()<<endl;//opcion de ver los logs
        }
        cout<<"Ingrese '1' para crear documento"<<endl;
        cout<<"Ingrese '2' para ver el numero de documentos creados"<<endl;
        cout<<"Ingrese '3' para ver los documentos creados"<<endl;
        cout<<"Ingrese '4' para borrar un documento"<<endl;
        cout<<"Ingrese '-1' para regresar al submenu anterior"<<endl;

        getline(cin,navegando);
        if(navegando == "0" && isAdmin){
            cout<<ofimaticaSoftware->verLogs()<<endl;
        }
        else if(navegando == "1"){
            cout<<"Ingrese nombre del documento"<<endl;
            string doc = "";
            getline(cin,doc);
            ofimaticaSoftware->crearDocumento(doc);
            string ofiLog = "* "+usuarioActual->getUserName()+" ha creado el documento: "+doc;
            ofimaticaSoftware->crearMasLogs(ofiLog);
        }
        else if(navegando == "2"){
            cout<<"Cantidad de documentos creados: "<<ofimaticaSoftware->getCantidadDocumentos()<<endl;
            string ofiLogVer = "* "+usuarioActual->getUserName()+" ha solicitado ver la cantidad de documentos";
            ofimaticaSoftware->crearMasLogs(ofiLogVer);
        }
        else if(navegando == "3"){
            cout<<"Documentos creados hasta ahora"<<endl;
            cout<<ofimaticaSoftware->verDocumentos()<<endl;
            string ofiLogVerDocs = "* "+usuarioActual->getUserName()+" ha solicitado ver todos los documentos";
            ofimaticaSoftware->crearMasLogs(ofiLogVerDocs);
        }
        else if(navegando == "4"){
            cout<<"Ingrese nombre del documento para borrar"<<endl;
            cout<<ofimaticaSoftware->verDocumentos();
            string paraBorrar = "";
            getline(cin,paraBorrar);
            if(ofimaticaSoftware->eliminarDocumento(paraBorrar)){
                string ofiLogBorrar = "* "+usuarioActual->getUserName()+" ha borrado el documento: "+paraBorrar;
                ofimaticaSoftware->crearDocumento(ofiLogBorrar);
            }
        }
        else if(navegando == "-1"){
            return;
        }
        else{
            cout<<"respuesta invalida"<<endl;
        }
    }
}

//resume en un menu los metodos de un software de Produccion
void metodoProduccion(Usuario* usuarioActual,SoftwareProduccion* productionSoftware){
    string navegando = ""; bool isAdmin = usuarioActual->getObjectName() == "UsuarioAdmin";

    while (navegando != "-1")
    {
        if(isAdmin){//si es admin
            cout<<"Ingrese '0' para ver los logs de "<<productionSoftware->getSoftwareName()<<endl;//opcion de ver los logs
        }

        cout<<"Ingrese '1' crear nuevo archivo de produccion"<<endl;
        cout<<"Ingrese '2' para ver los archivos de produccion"<<endl;
        cout<<"Ingrese '3' para eliminar un archivo de produccion"<<endl;
        cout<<"Ingrese '-1' para regresar al submenu anterior"<<endl;

        getline(cin,navegando);
        if(navegando == "0" && isAdmin){
            cout<<productionSoftware->verLogs()<<endl;
        }
        else if(navegando == "1"){
            cout<<"ingrese nombre del archivo"<<endl;
            string producto = "";
            getline(cin,producto);
            productionSoftware->agregarArchivoProduccion(producto);
        }
        else if(navegando == "2"){
            cout<<"Mostrando archivos de produccion: "<<endl;
            cout<<productionSoftware->verProduccion()<<endl;
        }
        else if(navegando == "3"){
            cout<<"Ingrese nombre del archivo (incluyendo la extension)"<<endl;
            string archivoABorrar = "";
            getline(cin,archivoABorrar);
            if(productionSoftware->eliminarArchivoProduccion(archivoABorrar)){
                string logsDel = "* "+usuarioActual->getUserName()+" ha eliminado el archivo: "+archivoABorrar;
                productionSoftware->crearMasLogs(logsDel);
            }
        }
        else if(navegando == "-1"){
            return;
        }
        else{
            cout<<"respuesta invalida"<<endl;
        }

    }
}

//resume en un menu los metodos de un software de seguridad
void metodoSeguridad(Usuario* usuarioActual,SoftwareSeguridad* seguridadSoftware){
    string navegando = ""; bool isAdmin = usuarioActual->getObjectName() == "UsuarioAdmin";
    if(!isAdmin){//si por alguna razon un usuario que no sea admin logra seleccionar un software con restriccion de admin
        cout<<"Acceso denegado"<<endl;
        return;
    }
    while (navegando != "-1")
    {
        cout<<"Ingrese '0' para ver los logs de "<<seguridadSoftware->getSoftwareName()<<endl;//opcion de ver los logs
        cout<<"Ingrese '1' agregar nueva muestra de malware"<<endl;
        cout<<"Ingrese '2' para ver las muestras de malware"<<endl;
        cout<<"Ingrese '3' para eliminar una muestra de malware"<<endl;
        cout<<"Ingrese '-1' para regresar al submenu anterior"<<endl;

        getline(cin,navegando);
        if(navegando == "0"){//no es necesario preguntar si es admin
            cout<<seguridadSoftware->verLogs()<<endl;
        }
        else if(navegando == "1"){
            cout<<"Ingrese el nombre de la nueva muestra de malware"<<endl;
            string malware = "";
            getline(cin,malware);
            seguridadSoftware->agregarMuestra(malware);
        }
        else if(navegando == "2"){
            cout<<"Mostrando listado de muestras"<<endl;
            cout<<seguridadSoftware->verMuestras()<<endl;
        }
        else if(navegando == "3"){
            cout<<"Ingrese nombre de la muestra a eliminar"<<endl;
            string malwareABorrar = "";
            getline(cin,malwareABorrar);
            seguridadSoftware->eliminarMuestra(malwareABorrar);
        }
        else if(navegando == "-1"){
            return;
        }
        else{
            cout<<"respuesta invalida"<<endl;
        }
    }
}

//resume en un menu los metodos de un software social
void metodoSocial(Usuario* usuarioActual,SoftwareSocial* socialSoftware){
    string navegando = ""; bool isAdmin = usuarioActual->getObjectName() == "UsuarioAdmin";

    while (navegando != "-1")
    {
        if(isAdmin){//si es admin
            cout<<"Ingrese '0' para ver los logs de "<<socialSoftware->getSoftwareName()<<endl;//opcion de ver los logs
        }
        cout<<"Ingrese '1' para agregar a un amigo"<<endl;
        cout<<"Ingrese '2' para ver amigos"<<endl;
        cout<<"Ingrese '3' para ver la cantidad de amigos"<<endl;
        cout<<"Ingrese '4' para eliminar amigo"<<endl;
        cout<<"Ingrese '-1' para regresar al submenu anterior"<<endl;
        getline(cin,navegando);
        if(navegando == "0" && isAdmin){
            cout<<socialSoftware->verLogs()<<endl;
        }
        else if(navegando == "1"){
            if(socialSoftware->verAmigosPosibles(usuarioActual) != "noHay"){
                cout<<socialSoftware->verAmigosPosibles(usuarioActual)<<endl;
                cout<<"Ingrese nombre del amigo"<<endl;
                string amigo = "";
                getline(cin,amigo);
                if(amigo == ""){
                    cout<<"No ingrese 'enter' sin antes escribir el nombre"<<endl;
                }


                if(amigo == usuarioActual->getUserName()){
                    cout<<"No puede agregarse como amigo a si mismo"<<endl;
                }
                else{
                    if(socialSoftware->agregarAmigo(amigo,usuarioActual->getUserName())){
                        socialSoftware->agregarAmigo(usuarioActual->getUserName(),amigo);
                    }
                }

            }
        }
        else if(navegando == "2"){
            cout<<"Amigos de "+usuarioActual->getUserName()+":"<<endl;
            cout<<socialSoftware->verAmigos(usuarioActual->getUserName());
            string logsVer = "* "+usuarioActual->getUserName()+" ha solicitado ver a sus amigos";
            socialSoftware->crearMasLogs(logsVer);
        }
        else if(navegando == "3"){
            cout<<"Cantidad de amigos de "+usuarioActual->getUserName()+":"<<socialSoftware->cuantosAmigosTiene(usuarioActual->getUserName())<<endl;
            string logsCant = "* "+usuarioActual->getUserName()+" ha solicitado ver su cantidad de amigos";
            socialSoftware->crearMasLogs(logsCant);
        }
        else if(navegando == "4"){
            cout<<"Ingrese nombre del amigo a eliminar"<<endl;
            string examigo = "";
            getline(cin,examigo);
            if(socialSoftware->eliminarAmigo(examigo,usuarioActual->getUserName())){
                socialSoftware->eliminarAmigo(usuarioActual->getUserName(),examigo);
                string logsDel = "* "+usuarioActual->getUserName()+" ha eliminado a "+examigo+" de su lista de amigos";
                socialSoftware->crearMasLogs(logsDel);
            }
            else{
                cout<<"No existe amigo con ese nombre para eliminar"<<endl;
            }
        }
        else if(navegando == "-1"){
            return;
        }
        else{
            cout<<"respuesta invalida"<<endl;
        }
    }
}

//funcion encargada de redirigir a las opciones de funcionalidad que cada software de diferente tipo tiene
void funcionalidadDeCadaSoftware(Usuario* usuarioActual,Software* softwareGenerico){
    string objName = softwareGenerico->getObjectName();//nombre del objeto
    if(objName == "SoftwareGame"){
        //confio en que el retorno de la funcion virtual getObjectName() sera sobreescrita por SoftwareGame
        //y hago casting
        SoftwareGame *game = static_cast<SoftwareGame*>(softwareGenerico);
        metodoGames(usuarioActual,game);
    }
    else if(objName == "SoftwareNavegador"){
        SoftwareNavegador *navegador = static_cast<SoftwareNavegador*>(softwareGenerico);
        metodoNavegador(usuarioActual,navegador);
    }
    else if(objName == "SoftwareOfimatica"){
        SoftwareOfimatica *ofimatica = static_cast<SoftwareOfimatica*>(softwareGenerico);
        metodoOfimatica(usuarioActual,ofimatica);
    }
    else if(objName == "SoftwareProduccion"){
        SoftwareProduccion *production = static_cast<SoftwareProduccion*>(softwareGenerico);
        metodoProduccion(usuarioActual,production);
    }
    else if(objName == "SoftwareSeguridad"){
        SoftwareSeguridad *seguridad = static_cast<SoftwareSeguridad*>(softwareGenerico);
        metodoSeguridad(usuarioActual,seguridad);
    }
    else if(objName == "SoftwareSocial"){
        SoftwareSocial *social = static_cast<SoftwareSocial*>(softwareGenerico);
        metodoSocial(usuarioActual,social);
    }
    else{
        cout<<"Error: tipo de software desconocido"<<endl;
        return;
    }
}


//prepobla con 15 usuarios(4 menores,1 admin, 10 normales)
//prepobla con 20 juegos(2 por cada genero)
//prepobla con 5 software de ofimatica
//prepobla con 4 software de produccion(1 de cada tipo,4 en total)
//prepobla con 6 software de seguridad (1 de cada tipo,6 en total)
//prepobla con 2 software sociales(1 para todo publico y otro para 18+)
//inicializa con 4 usuarios normales y 1 admin en el primer software social
//inicializa con 1 admin, 3 menores y 5 usuarios normales el segundo software social

//y asigna al menos 2 amigos para cada usuario inscrito en el software social 1 como en el social 2

void prepoblador(Biblioteca* bibliotecaGeneral,ListaUsuario* usuariosExistentes){
    //generos fijos
    string gameGenres[10] = {"FPS","MMO","PUZZLE","RPG","Platformer","Strategy","Action","Open World","Simulator","Horror"};
    string *generoJuego = &gameGenres[0];
    //tipos de produccion
    string productionType[4] = {"video","musica","streaming","foto"};
    //malware fijo
    string malwareType[6] = {"Ransomware","Spyware","botnets","rootkits","gusanos","troyanos"};


    //prepoblando de 15 usuarios(4 menores,1 admin, 10 usuarios normales)
    UsuarioMenor *menor1 = new UsuarioMenor("David","pass123",16);
    UsuarioMenor *menor2 = new UsuarioMenor("charmander","pass123",9);
    UsuarioMenor *menor3 = new UsuarioMenor("sephiroth","123",13);
    UsuarioMenor *menor4 = new UsuarioMenor("Carlos","pass123",17);

    UsuarioAdmin *admin1 = new UsuarioAdmin("elAdmin","123456",20,"eladmin@admin.com");

    UsuarioNormal *normal1 = new UsuarioNormal("Mateo","donthackplz",28,"mateo@user.com");
    UsuarioNormal *normal2 = new UsuarioNormal("Felipe","321",26,"felipe@user.com");
    UsuarioNormal *normal3 = new UsuarioNormal("Juan","111",27,"juan@user.com");
    UsuarioNormal *normal4 = new UsuarioNormal("Bruno","222",25,"bruno@user.com");
    UsuarioNormal *normal5 = new UsuarioNormal("Benjamin","333",22,"benjamin@user.com");
    UsuarioNormal *normal6 = new UsuarioNormal("Hugo","121",18,"hugo@user.com");
    UsuarioNormal *normal7 = new UsuarioNormal("Pablo","212",23,"pablo@user.com");
    UsuarioNormal *normal8 = new UsuarioNormal("Alejandro","131",24,"alejandro@user.com");
    UsuarioNormal *normal9 = new UsuarioNormal("Martin","313",20,"martin@user.com");
    UsuarioNormal *normal10 = new UsuarioNormal("Diego","777",21,"diego@user.com");


    usuariosExistentes->insertUsuario(admin1);

    usuariosExistentes->insertUsuario(menor1);
    usuariosExistentes->insertUsuario(menor2);
    usuariosExistentes->insertUsuario(menor3);
    usuariosExistentes->insertUsuario(menor4);

    usuariosExistentes->insertUsuario(normal1);
    usuariosExistentes->insertUsuario(normal2);
    usuariosExistentes->insertUsuario(normal3);
    usuariosExistentes->insertUsuario(normal4);
    usuariosExistentes->insertUsuario(normal5);
    usuariosExistentes->insertUsuario(normal6);
    usuariosExistentes->insertUsuario(normal7);
    usuariosExistentes->insertUsuario(normal8);
    usuariosExistentes->insertUsuario(normal9);
    usuariosExistentes->insertUsuario(normal10);

    //prepoblado con 15 usuarios
    //cuando se logea se deben ingresar los datos correspondientes para poder ingresar a alguna de estas cuentas
    //prepoblando de softwares

    //genero Platformer
    SoftwareGame *game1 = new SoftwareGame("SuperMario","Nintendo",4,8000,"Platformer");
    SoftwareGame *game2 = new SoftwareGame("Donkey Kong Country","Nintendo",8,14000,"Platformer");

    //genero FPS (ambos 18+)
    SoftwareGame *game3 = new SoftwareGame("CSGO","Valve",18,5000,"FPS");
    SoftwareGame *game4 = new SoftwareGame("Doom Eternal","id Software",18,9000,"FPS");
    //genero MMO
    SoftwareGame *game5 = new SoftwareGame("World of Warcraft","Blizzard",13,5500,"MMO");
    SoftwareGame *game6 = new SoftwareGame("FFXIV","Square Enix",13,6000,"MMO");
    //genero PUZZLE
    SoftwareGame *game7 = new SoftwareGame("Portal","Valve",10,10000,"PUZZLE");
    SoftwareGame *game8 = new SoftwareGame("Tetris","Alexey Pajitnov",4,2500,"PUZZLE");
    //genero RPG
    SoftwareGame *game9 = new SoftwareGame("Pokemon Ruby","Nintendo",4,12000,"RPG");
    SoftwareGame *game10 = new SoftwareGame("Pokemon Zafiro","Nintendo",4,12000,"RPG");
    //genero Strategy
    SoftwareGame *game11 = new SoftwareGame("AoM","Microsoft",14,17500,"Strategy");
    SoftwareGame *game12 = new SoftwareGame("AoE","Microsoft",14,12000,"Strategy");
    //genero Action
    SoftwareGame *game13 = new SoftwareGame("God of War","Santa Monica Studio",18,16500,"Action");
    SoftwareGame *game14 = new SoftwareGame("Mortal Kombat 1","NetherRealmStudios",18,15000,"Action");
    //genero Open World
    SoftwareGame *game15 = new SoftwareGame("Genshin Impact","HoYoverse",12,17000,"Open World");
    SoftwareGame *game16 = new SoftwareGame("GTA V","Rockstar North",18,19000,"Open World");
    //genero Simulator
    SoftwareGame *game17 = new SoftwareGame("Goat Simulator","Coffee Stain Studios",12,15500,"Simulator");
    SoftwareGame *game18 = new SoftwareGame("Goat Simulator 3","Coffee Stain Studios",12,14500,"Simulator");
    //genero Horror
    SoftwareGame *game19 = new SoftwareGame("Amnesia","Frictional Games",18,12000,"Horror");
    SoftwareGame *game20 = new SoftwareGame("Phasmophobia","Kinetic Games",18,12500,"Horror");
    

    bibliotecaGeneral->perteneceAgregarABiblioteca(game1,generoJuego,"Platformer",10);
    bibliotecaGeneral->perteneceAgregarABiblioteca(game2,generoJuego,"Platformer",10);
    bibliotecaGeneral->perteneceAgregarABiblioteca(game3,generoJuego,"FPS",10);
    bibliotecaGeneral->perteneceAgregarABiblioteca(game4,generoJuego,"FPS",10);
    bibliotecaGeneral->perteneceAgregarABiblioteca(game5,generoJuego,"MMO",10);
    bibliotecaGeneral->perteneceAgregarABiblioteca(game6,generoJuego,"MMO",10);
    bibliotecaGeneral->perteneceAgregarABiblioteca(game7,generoJuego,"PUZZLE",10);
    bibliotecaGeneral->perteneceAgregarABiblioteca(game8,generoJuego,"PUZZLE",10);
    bibliotecaGeneral->perteneceAgregarABiblioteca(game9,generoJuego,"RPG",10);
    bibliotecaGeneral->perteneceAgregarABiblioteca(game10,generoJuego,"RPG",10);
    bibliotecaGeneral->perteneceAgregarABiblioteca(game11,generoJuego,"Strategy",10);
    bibliotecaGeneral->perteneceAgregarABiblioteca(game12,generoJuego,"Strategy",10);
    bibliotecaGeneral->perteneceAgregarABiblioteca(game13,generoJuego,"Action",10);
    bibliotecaGeneral->perteneceAgregarABiblioteca(game14,generoJuego,"Action",10);
    bibliotecaGeneral->perteneceAgregarABiblioteca(game15,generoJuego,"Open World",10);
    bibliotecaGeneral->perteneceAgregarABiblioteca(game16,generoJuego,"Open World",10);
    bibliotecaGeneral->perteneceAgregarABiblioteca(game17,generoJuego,"Simulator",10);
    bibliotecaGeneral->perteneceAgregarABiblioteca(game18,generoJuego,"Simulator",10);
    bibliotecaGeneral->perteneceAgregarABiblioteca(game19,generoJuego,"Horror",10);
    bibliotecaGeneral->perteneceAgregarABiblioteca(game20,generoJuego,"Horror",10);
    //biblioteca prepoblada con 20 juegos

    SoftwareOfimatica *ofimatica1 = new SoftwareOfimatica("Excel","Microsoft",12,1200);
    SoftwareOfimatica *ofimatica2 = new SoftwareOfimatica("PowerPoint","Microsoft",12,800);
    SoftwareOfimatica *ofimatica3 = new SoftwareOfimatica("Word","Microsoft",12,1000);
    SoftwareOfimatica *ofimatica4 = new SoftwareOfimatica("OneNote","Microsoft",12,800);
    SoftwareOfimatica *ofimatica5 = new SoftwareOfimatica("Visio","Microsoft",12,800);

    
    bibliotecaGeneral->agregarABiblioteca(ofimatica1);
    bibliotecaGeneral->agregarABiblioteca(ofimatica2);
    bibliotecaGeneral->agregarABiblioteca(ofimatica3);
    bibliotecaGeneral->agregarABiblioteca(ofimatica4);
    bibliotecaGeneral->agregarABiblioteca(ofimatica5);
    //biblioteca prepoblada con 5 software de ofimatica

    SoftwareProduccion *production1 = new SoftwareProduccion("VLC","VideoLAN",18,2000,"video");
    SoftwareProduccion *production2 = new SoftwareProduccion("Zoom","Eric Yuan",18,2000,"streaming");
    SoftwareProduccion *production3 = new SoftwareProduccion("Adobe Lightroom","Mark Hamburg",18,2000,"foto");
    SoftwareProduccion *production4 = new SoftwareProduccion("Adobe Audition","Adobe Inc",18,2000,"musica");

    bibliotecaGeneral->perteneceAgregarABiblioteca(production1,productionType,"video",4);
    bibliotecaGeneral->perteneceAgregarABiblioteca(production2,productionType,"streaming",4);
    bibliotecaGeneral->perteneceAgregarABiblioteca(production3,productionType,"foto",4);
    bibliotecaGeneral->perteneceAgregarABiblioteca(production4,productionType,"musica",4);
    //biblioteca prepoblada con 4 software de produccion(todos para 18+)

    SoftwareNavegador *navegador1 = new SoftwareNavegador("Google Chrome","Google Inc",15,500);
    SoftwareNavegador *navegador2 = new SoftwareNavegador("FireFox","mozilla",15,500);
    
    bibliotecaGeneral->agregarABiblioteca(navegador1);
    bibliotecaGeneral->agregarABiblioteca(navegador2);
    //biblioteca prepoblada con 2 Software de navegacion

    //{"Ransomware","Spyware","botnets","rootkits","gusanos","troyanos"}
    SoftwareSeguridad *seguridad1 = new SoftwareSeguridad("Acronis","Serg Bell",99,1200,"Ransomware");
    SoftwareSeguridad *seguridad2 = new SoftwareSeguridad("Bitdefender","Florin Talpes",99,1200,"Spyware");
    SoftwareSeguridad *seguridad3 = new SoftwareSeguridad("ESET NOD32","ESET",99,1200,"botnets");
    SoftwareSeguridad *seguridad4 = new SoftwareSeguridad("MalwareBytes","MalwareBytes Inc",99,1200,"rootkits");
    SoftwareSeguridad *seguridad5 = new SoftwareSeguridad("Kaspersky","Kaspersky Lab",99,1200,"gusanos");
    SoftwareSeguridad *seguridad6 = new SoftwareSeguridad("Avast","Avast Software",99,1200,"troyanos");

    bibliotecaGeneral->perteneceAgregarABiblioteca(seguridad1,malwareType,"Ransomware",6);
    bibliotecaGeneral->perteneceAgregarABiblioteca(seguridad2,malwareType,"Spyware",6);
    bibliotecaGeneral->perteneceAgregarABiblioteca(seguridad3,malwareType,"botnets",6);
    
    bibliotecaGeneral->perteneceAgregarABiblioteca(seguridad4,malwareType,"rootkits",6);
    bibliotecaGeneral->perteneceAgregarABiblioteca(seguridad5,malwareType,"gusanos",6);
    bibliotecaGeneral->perteneceAgregarABiblioteca(seguridad6,malwareType,"troyanos",6);
    
    //biblioteca prepoblada con 6 Software de Seguridad

    SoftwareSocial *social1 = new SoftwareSocial("Twitter","Jack Dorsey",18,2500);
    SoftwareSocial *social2 = new SoftwareSocial("Facebook","Mark Zuckerberg",15,2000);

    

    bibliotecaGeneral->agregarABiblioteca(social1);
    bibliotecaGeneral->agregarABiblioteca(social2);
    //biblioteca prepoblada con 2 Software Social
    

    social1->agregarUsuarioAlSoftware(admin1,social1);
    social1->crearListadoParaNuevoUsuario(admin1);



    social1->agregarUsuarioAlSoftware(normal1,social1);
    social1->crearListadoParaNuevoUsuario(normal1);
    social1->agregarUsuarioAlSoftware(normal2,social1);
    social1->crearListadoParaNuevoUsuario(normal2);
    social1->agregarUsuarioAlSoftware(normal3,social1);
    social1->crearListadoParaNuevoUsuario(normal3);
    social1->agregarUsuarioAlSoftware(normal4,social1);
    social1->crearListadoParaNuevoUsuario(normal4);

    
    social1->agregarAmigo(normal1->getUserName(),admin1->getUserName());
    social1->agregarAmigo(admin1->getUserName(),normal1->getUserName());

    social1->agregarAmigo(normal2->getUserName(),admin1->getUserName());
    social1->agregarAmigo(admin1->getUserName(),normal2->getUserName());
    //admin1 es amigo de normal1 y normal2


    social1->agregarAmigo(normal3->getUserName(),normal1->getUserName());
    social1->agregarAmigo(normal1->getUserName(),normal3->getUserName());
    //normal1 es amigo de normal3 y admin1 y normal4

    social1->agregarAmigo(normal1->getUserName(),normal2->getUserName());
    social1->agregarAmigo(normal3->getUserName(),normal2->getUserName());
    //normal2 es amigo de normal1 y normal3 y normal4
    //normal3 es amigo de normal1 y normal2


    social1->agregarAmigo(normal1->getUserName(),normal4->getUserName());
    social1->agregarAmigo(normal4->getUserName(),normal1->getUserName());

    social1->agregarAmigo(normal2->getUserName(),normal4->getUserName());
    social1->agregarAmigo(normal4->getUserName(),normal2->getUserName());
    //normal4 es amigo de normal1 y normal2

    //inicializacion para software social2(para todo publico)
    social2->agregarUsuarioAlSoftware(admin1,social2);
    social2->crearListadoParaNuevoUsuario(admin1);

    social2->agregarUsuarioAlSoftware(menor1,social2);
    social2->crearListadoParaNuevoUsuario(menor1);
    social2->agregarUsuarioAlSoftware(menor2,social2);
    social2->crearListadoParaNuevoUsuario(menor2);
    social2->agregarUsuarioAlSoftware(menor3,social2);
    social2->crearListadoParaNuevoUsuario(menor3);

    social2->agregarUsuarioAlSoftware(normal1,social2);
    social2->crearListadoParaNuevoUsuario(normal1);
    social2->agregarUsuarioAlSoftware(normal4,social2);
    social2->crearListadoParaNuevoUsuario(normal4);
    social2->agregarUsuarioAlSoftware(normal5,social2);
    social2->crearListadoParaNuevoUsuario(normal5);
    social2->agregarUsuarioAlSoftware(normal6,social2);
    social2->crearListadoParaNuevoUsuario(normal6);
    social2->agregarUsuarioAlSoftware(normal7,social2);
    social2->crearListadoParaNuevoUsuario(normal7);

    social2->agregarAmigo(menor2->getUserName(),menor1->getUserName());
    social2->agregarAmigo(menor1->getUserName(),menor2->getUserName());

    social2->agregarAmigo(menor3->getUserName(),menor1->getUserName());
    social2->agregarAmigo(menor1->getUserName(),menor3->getUserName());
    //menor1 es amigo de menor2 y menor3


    social2->agregarAmigo(menor3->getUserName(),menor2->getUserName());
    social2->agregarAmigo(menor2->getUserName(),menor3->getUserName());
    //menor2 es amigo de menor1 y menor3
    //menor3 es amigo de menor1 y menor2

    social2->agregarAmigo(normal1->getUserName(),admin1->getUserName());
    social2->agregarAmigo(admin1->getUserName(),normal1->getUserName());

    social2->agregarAmigo(normal4->getUserName(),admin1->getUserName());
    social2->agregarAmigo(admin1->getUserName(),normal4->getUserName());
    //admin1 es amigo de normal1 y normal4 y normal6

    social2->agregarAmigo(normal4->getUserName(),normal1->getUserName());
    social2->agregarAmigo(normal1->getUserName(),normal4->getUserName());
    //normal1 es amigo de admin1 y normal4

    social2->agregarAmigo(normal4->getUserName(),normal5->getUserName());
    social2->agregarAmigo(normal5->getUserName(),normal4->getUserName());
    //normal4 es amigo de admin1 y normal1 y normal5 y normal7

    social2->agregarAmigo(normal6->getUserName(),normal5->getUserName());
    social2->agregarAmigo(normal5->getUserName(),normal6->getUserName());
    //normal5 es amigo de normal4 y normal6 y normal7

    social2->agregarAmigo(admin1->getUserName(),normal6->getUserName());
    social2->agregarAmigo(normal6->getUserName(),admin1->getUserName());
    //normal6 es amigo de normal5 y admin1

    social2->agregarAmigo(normal4->getUserName(),normal7->getUserName());
    social2->agregarAmigo(normal7->getUserName(),normal4->getUserName());

    social2->agregarAmigo(normal5->getUserName(),normal7->getUserName());
    social2->agregarAmigo(normal7->getUserName(),normal5->getUserName());
    //normal7 es amigo de normal4 y normal5
}


int main(){
    //generos fijos
    string gameGenres[10] = {"FPS","MMO","PUZZLE","RPG","Platformer","Strategy","Action","Open World","Simulator","Horror"};
    string *generoJuego = &gameGenres[0];
    //tipos de produccion
    string productionType[4] = {"video","musica","streaming","foto"};
    //malware fijo
    string malwareType[6] = {"Ransomware","Spyware","botnets","rootkits","gusanos","troyanos"};

    

    Biblioteca *bibliotecaPC = new Biblioteca();
    ListaUsuario *usuariosActuales = new ListaUsuario();
    
    

    Biblioteca *tienda = new Biblioteca();

    prepoblador(tienda,usuariosActuales);
    prepoblador(bibliotecaPC,usuariosActuales);

    SoftwareGame *game21 = new SoftwareGame("Octopath","Square Enix",12,28000,"RPG");
    SoftwareGame *game22 = new SoftwareGame("Fire Emblem","Koei Tecmo",12,13000,"RPG");

    tienda->perteneceAgregarABiblioteca(game21,gameGenres,"RPG",10);
    tienda->perteneceAgregarABiblioteca(game22,gameGenres,"RPG",10);

    Usuario *usuarioActual = NULL; Software *softwareActual = NULL;
    
    string navegabilidad = ""; string subMenuNavegar =""; string navegarFuncionalidades = "";
    string decorativo = "======================================";
    string decorativo2= "--------------------------------------";
    while(navegabilidad != "-1"){
        cout<<decorativo<<endl;
        cout<<"INICIO"<<endl;
        cout<<decorativo<<endl;
        cout<<"Ingrese '1' para entrar al log-in"<<endl;
        cout<<"Ingrese '0' para entrar a crear cuenta"<<endl;
        cout<<"Ingrese '-1' para terminar el programa"<<endl;
        getline(cin,navegabilidad);
        if(navegabilidad == "1"){
            cout<<"ingresando a LOG IN"<<endl;
            usuarioActual = menuOpOneLOGIN(usuariosActuales);
        }
        else if(navegabilidad == "0"){
            cout<<"ingresando a CREAR CUENTA"<<endl;
            usuarioActual = menuOpZeroCreateUser(usuariosActuales);
        }
        else if(navegabilidad == "-1"){
            cout<<"...terminando programa"<<endl;
            return 0;
        }
        else{
            cout<<"respuesta invalida, ingrese un numero dentro del rango permitido"<<endl;
        }


        //despues de logear se apunta al usuario que logeo
        //permitiendo que entre a esta condicion 
        if(usuarioActual != NULL){//luego de logear o crear cuenta se deja con un usuario que apunte al log actual
            while(subMenuNavegar != "-1"){
                    cout<<decorativo2<<endl;
                    cout<<"Usuario: "<<usuarioActual->getUserName()<<endl;
                    cout<<decorativo2<<"\n"<<endl;
                    cout<<"Ingrese '0' para instalar Software de la tienda"<<endl; 
                    cout<<"Ingrese '1' para elegir Software"<<endl;
                    cout<<"Ingrese '2' para desintalar Software"<<endl;
                    cout<<"Ingrese '-1' para deslogear"<<endl;
                    getline(cin,subMenuNavegar);
                    if(subMenuNavegar == "1"){
                        cout<<"Ingresando a ELEGIR SOFTWARE"<<endl;
                        softwareActual = elegirSoftware(bibliotecaPC,usuarioActual);//si se elige correctamente
                        //softwareActual sera distinto de NULL lo que permite el proximo if
                    }
                    else if(subMenuNavegar == "0"){
                        cout<<"Ingresando a INSTALAR SOFTWARE"<<endl;
                        instalarSoftware(bibliotecaPC,tienda,usuarioActual);
                    }
                    else if(subMenuNavegar == "2"){
                        cout<<"Ingresando a DESINTALAR SOFTWARE"<<endl;
                        desinstalarSoftware(bibliotecaPC,usuarioActual);
                    }
                    else if(subMenuNavegar == "-1"){
                        cout<<"Cerrando sesion..."<<endl;
                        cout<<"volviendo al inicio"<<endl;
                        //y ahora que deslogeo ya no deberia apuntar a ningun lado
                        usuarioActual = NULL;//ya no se cumple la condicion(hasta que relogee o se cree otra cuenta mas)
                        softwareActual = NULL;//por si elige un software y luego sale, el software no deberia seguir siendo apuntado
                        break;
                    }
                    else{
                        cout<<"respuesta invalida, ingrese un numero dentro del rango permitido"<<endl;
                    }
                    
                    if(softwareActual != NULL){
                        while(navegarFuncionalidades != "-1"){
                            cout<<decorativo2<<endl;
                            cout<<"Software: "<<softwareActual->getSoftwareName()<<endl;
                            cout<<decorativo2<<"\n"<<endl;
                            cout<<"Ingrese '1' para acceder a las funcionalidades de su Software elegido"<<endl;
                            //los logs estan incluidos entre las funcionalidad del Software
                            //pero solo si cumplen el status de ADMIN
                            cout<<"Ingrese '-1' para regresar al subMenu anterior y elegir otro software"<<endl;
                            
                            getline(cin,navegarFuncionalidades);
                            if(navegarFuncionalidades == "1"){
                                cout<<"Cargando funciones para el software seleccionado..."<<endl;
                                funcionalidadDeCadaSoftware(usuarioActual,softwareActual);
                            }
                            else if(navegarFuncionalidades == "-1"){
                                softwareActual = NULL;//vuelve a NULL para que forzar al usuario a que elija o instale nuevo software
                                break;
                            }
                            else{
                                cout<<"respuesta invalida, ingrese un numero dentro del rango permitido"<<endl;
                            }
                        }
                    }
                    navegarFuncionalidades = "";//reinicializar el tercer menu
                    //donde se muestra lo que la biblioteca tiene para este usuarioActual
                    //op0 instalar software, se debe mostrar el software disponible en tienda
                    //op-1 deslogear y regresar al menu
            }
        }
        //al salir del while subMenu, se debe
        //reinicializar con cualquier cosa que no sea '-1' para que el usuario pueda ir y volver al submenu
        subMenuNavegar = "";

    }


    return 0;
}