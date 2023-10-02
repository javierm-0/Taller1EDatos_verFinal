# Taller1EDatos_verFinal
comandos desde el terminal de VSCode:
g++ -o taller1 taller1.cpp
./taller1
Nombre: Javier Ignacio Moraga Sanhueza
Rut: 20.028.499-2


Primer taller de Estructura de datos para entregar

creacion de objetos:
//generos fijos
string gameGenres[10] = {"FPS","MMO","PUZZLE","RPG","Platformer","Strategy","Action","Open World","Simulator","Horror"};
string *generoJuego = &gameGenres[0];
//tipos de produccion
string productionType[4] = {"video","musica","streaming","foto"};
//malware fijo
string malwareType[6] = {"Ransomware","Spyware","botnets","rootkits","gusanos","troyanos"};

Se instancia el objeto Biblioteca *bibliotecaPC = new Biblioteca();
Se instancia el objeto ListaUsuario *usuariosActuales = new ListaUsuario();

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

//se insertan 15 Usuarios en la lista ListaUsuario *usuariosExistentes
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
    
bibliotecaPC->perteneceAgregarABiblioteca(game1,generoJuego,"Platformer",10);
bibliotecaPC->perteneceAgregarABiblioteca(game2,generoJuego,"Platformer",10);
bibliotecaPC->perteneceAgregarABiblioteca(game3,generoJuego,"FPS",10);
bibliotecaPC->perteneceAgregarABiblioteca(game4,generoJuego,"FPS",10);
bibliotecaPC->perteneceAgregarABiblioteca(game5,generoJuego,"MMO",10);
bibliotecaPC->perteneceAgregarABiblioteca(game6,generoJuego,"MMO",10);
bibliotecaPC->perteneceAgregarABiblioteca(game7,generoJuego,"PUZZLE",10);
bibliotecaPC->perteneceAgregarABiblioteca(game8,generoJuego,"PUZZLE",10);
bibliotecaPC->perteneceAgregarABiblioteca(game9,generoJuego,"RPG",10);
bibliotecaPC->perteneceAgregarABiblioteca(game10,generoJuego,"RPG",10);
bibliotecaPC->perteneceAgregarABiblioteca(game11,generoJuego,"Strategy",10);
bibliotecaPC->perteneceAgregarABiblioteca(game12,generoJuego,"Strategy",10);
bibliotecaPC->perteneceAgregarABiblioteca(game13,generoJuego,"Action",10);
bibliotecaPC->perteneceAgregarABiblioteca(game14,generoJuego,"Action",10);
bibliotecaPC->perteneceAgregarABiblioteca(game15,generoJuego,"Open World",10);
bibliotecaPC->perteneceAgregarABiblioteca(game16,generoJuego,"Open World",10);
bibliotecaPC->perteneceAgregarABiblioteca(game17,generoJuego,"Simulator",10);
bibliotecaPC->perteneceAgregarABiblioteca(game18,generoJuego,"Simulator",10);
bibliotecaPC->perteneceAgregarABiblioteca(game19,generoJuego,"Horror",10);
bibliotecaPC->perteneceAgregarABiblioteca(game20,generoJuego,"Horror",10);
//biblioteca prepoblada con 20 juegos

SoftwareOfimatica *ofimatica1 = new SoftwareOfimatica("Excel","Microsoft",12,1200);
SoftwareOfimatica *ofimatica2 = new SoftwareOfimatica("PowerPoint","Microsoft",12,800);
SoftwareOfimatica *ofimatica3 = new SoftwareOfimatica("Word","Microsoft",12,1000);
SoftwareOfimatica *ofimatica4 = new SoftwareOfimatica("OneNote","Microsoft",12,800);
SoftwareOfimatica *ofimatica5 = new SoftwareOfimatica("Visio","Microsoft",12,800);

    
bibliotecaPC->agregarABiblioteca(ofimatica1);
bibliotecaPC->agregarABiblioteca(ofimatica2);
bibliotecaPC->agregarABiblioteca(ofimatica3);
bibliotecaPC->agregarABiblioteca(ofimatica4);
bibliotecaPC->agregarABiblioteca(ofimatica5);
//biblioteca prepoblada con 5 software de ofimatica

SoftwareProduccion *production1 = new SoftwareProduccion("VLC","VideoLAN",18,2000,"video");
SoftwareProduccion *production2 = new SoftwareProduccion("Zoom","Eric Yuan",18,2000,"streaming");
SoftwareProduccion *production3 = new SoftwareProduccion("Adobe Lightroom","Mark Hamburg",18,2000,"foto");
SoftwareProduccion *production4 = new SoftwareProduccion("Adobe Audition","Adobe Inc",18,2000,"musica");

bibliotecaPC->perteneceAgregarABiblioteca(production1,productionType,"video",4);
bibliotecaPC->perteneceAgregarABiblioteca(production2,productionType,"streaming",4);
bibliotecaPC->perteneceAgregarABiblioteca(production3,productionType,"foto",4);
bibliotecaPC->perteneceAgregarABiblioteca(production4,productionType,"musica",4);
//biblioteca prepoblada con 4 software de produccion(todos para 18+)

SoftwareNavegador *navegador1 = new SoftwareNavegador("Google Chrome","Google Inc",15,500);
SoftwareNavegador *navegador2 = new SoftwareNavegador("FireFox","mozilla",15,500);
    
bibliotecaPC->agregarABiblioteca(navegador1);
bibliotecaPC->agregarABiblioteca(navegador2);
//biblioteca prepoblada con 2 Software de navegacion

//{"Ransomware","Spyware","botnets","rootkits","gusanos","troyanos"}
SoftwareSeguridad *seguridad1 = new SoftwareSeguridad("Acronis","Serg Bell",99,1200,"Ransomware");
SoftwareSeguridad *seguridad2 = new SoftwareSeguridad("Bitdefender","Florin Talpes",99,1200,"Spyware");
SoftwareSeguridad *seguridad3 = new SoftwareSeguridad("ESET NOD32","ESET",99,1200,"botnets");
SoftwareSeguridad *seguridad4 = new SoftwareSeguridad("MalwareBytes","MalwareBytes Inc",99,1200,"rootkits");
SoftwareSeguridad *seguridad5 = new SoftwareSeguridad("Kaspersky","Kaspersky Lab",99,1200,"gusanos");
SoftwareSeguridad *seguridad6 = new SoftwareSeguridad("Avast","Avast Software",99,1200,"troyanos");

bibliotecaPC->perteneceAgregarABiblioteca(seguridad1,malwareType,"Ransomware",6);
bibliotecaPC->perteneceAgregarABiblioteca(seguridad2,malwareType,"Spyware",6);
bibliotecaPC->perteneceAgregarABiblioteca(seguridad3,malwareType,"botnets",6);
    
bibliotecaPC->perteneceAgregarABiblioteca(seguridad4,malwareType,"rootkits",6);
bibliotecaPC->perteneceAgregarABiblioteca(seguridad5,malwareType,"gusanos",6);
bibliotecaPC->perteneceAgregarABiblioteca(seguridad6,malwareType,"troyanos",6);
    
//biblioteca prepoblada con 6 Software de Seguridad

SoftwareSocial *social1 = new SoftwareSocial("Twitter","Jack Dorsey",18,2500);
SoftwareSocial *social2 = new SoftwareSocial("Facebook","Mark Zuckerberg",15,2000);

    

bibliotecaPC->agregarABiblioteca(social1);
bibliotecaPC->agregarABiblioteca(social2);
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
//normal1 es amigo de admin1 y normal;

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

Se instancia el objeto
Biblioteca *tienda = new Biblioteca();


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

//se insertan 15 Usuarios en la lista ListaUsuario *usuariosExistentes
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
    
tienda->perteneceAgregarABiblioteca(game1,generoJuego,"Platformer",10);
tienda->perteneceAgregarABiblioteca(game2,generoJuego,"Platformer",10);
tienda->perteneceAgregarABiblioteca(game3,generoJuego,"FPS",10);
tienda->perteneceAgregarABiblioteca(game4,generoJuego,"FPS",10);
tienda->perteneceAgregarABiblioteca(game5,generoJuego,"MMO",10);
tienda->perteneceAgregarABiblioteca(game6,generoJuego,"MMO",10);
tienda->perteneceAgregarABiblioteca(game7,generoJuego,"PUZZLE",10);
tienda->perteneceAgregarABiblioteca(game8,generoJuego,"PUZZLE",10);
tienda->perteneceAgregarABiblioteca(game9,generoJuego,"RPG",10);
tienda->perteneceAgregarABiblioteca(game10,generoJuego,"RPG",10);
tienda->perteneceAgregarABiblioteca(game11,generoJuego,"Strategy",10);
tienda->perteneceAgregarABiblioteca(game12,generoJuego,"Strategy",10);
tienda->perteneceAgregarABiblioteca(game13,generoJuego,"Action",10);
tienda->perteneceAgregarABiblioteca(game14,generoJuego,"Action",10);
tienda->perteneceAgregarABiblioteca(game15,generoJuego,"Open World",10);
tienda->perteneceAgregarABiblioteca(game16,generoJuego,"Open World",10);
tienda->perteneceAgregarABiblioteca(game17,generoJuego,"Simulator",10);
tienda->perteneceAgregarABiblioteca(game18,generoJuego,"Simulator",10);
tienda->perteneceAgregarABiblioteca(game19,generoJuego,"Horror",10);
tienda->perteneceAgregarABiblioteca(game20,generoJuego,"Horror",10);
//tienda prepoblada con 20 juegos

SoftwareOfimatica *ofimatica1 = new SoftwareOfimatica("Excel","Microsoft",12,1200);
SoftwareOfimatica *ofimatica2 = new SoftwareOfimatica("PowerPoint","Microsoft",12,800);
SoftwareOfimatica *ofimatica3 = new SoftwareOfimatica("Word","Microsoft",12,1000);
SoftwareOfimatica *ofimatica4 = new SoftwareOfimatica("OneNote","Microsoft",12,800);
SoftwareOfimatica *ofimatica5 = new SoftwareOfimatica("Visio","Microsoft",12,800);

    
tienda->agregarABiblioteca(ofimatica1);
tienda->agregarABiblioteca(ofimatica2);
tienda->agregarABiblioteca(ofimatica3);
tienda->agregarABiblioteca(ofimatica4);
tienda->agregarABiblioteca(ofimatica5);
//biblioteca prepoblada con 5 software de ofimatica

SoftwareProduccion *production1 = new SoftwareProduccion("VLC","VideoLAN",18,2000,"video");
SoftwareProduccion *production2 = new SoftwareProduccion("Zoom","Eric Yuan",18,2000,"streaming");
SoftwareProduccion *production3 = new SoftwareProduccion("Adobe Lightroom","Mark Hamburg",18,2000,"foto");
SoftwareProduccion *production4 = new SoftwareProduccion("Adobe Audition","Adobe Inc",18,2000,"musica");

tienda->perteneceAgregarABiblioteca(production1,productionType,"video",4);
tienda->perteneceAgregarABiblioteca(production2,productionType,"streaming",4);
tienda->perteneceAgregarABiblioteca(production3,productionType,"foto",4);
tienda->perteneceAgregarABiblioteca(production4,productionType,"musica",4);
//biblioteca prepoblada con 4 software de produccion(todos para 18+)

SoftwareNavegador *navegador1 = new SoftwareNavegador("Google Chrome","Google Inc",15,500);
SoftwareNavegador *navegador2 = new SoftwareNavegador("FireFox","mozilla",15,500);
    
tienda->agregarABiblioteca(navegador1);
tienda->agregarABiblioteca(navegador2);
//biblioteca prepoblada con 2 Software de navegacion

//{"Ransomware","Spyware","botnets","rootkits","gusanos","troyanos"}
SoftwareSeguridad *seguridad1 = new SoftwareSeguridad("Acronis","Serg Bell",99,1200,"Ransomware");
SoftwareSeguridad *seguridad2 = new SoftwareSeguridad("Bitdefender","Florin Talpes",99,1200,"Spyware");
SoftwareSeguridad *seguridad3 = new SoftwareSeguridad("ESET NOD32","ESET",99,1200,"botnets");
SoftwareSeguridad *seguridad4 = new SoftwareSeguridad("MalwareBytes","MalwareBytes Inc",99,1200,"rootkits");
SoftwareSeguridad *seguridad5 = new SoftwareSeguridad("Kaspersky","Kaspersky Lab",99,1200,"gusanos");
SoftwareSeguridad *seguridad6 = new SoftwareSeguridad("Avast","Avast Software",99,1200,"troyanos");

tienda->perteneceAgregarABiblioteca(seguridad1,malwareType,"Ransomware",6);
tienda->perteneceAgregarABiblioteca(seguridad2,malwareType,"Spyware",6);
tienda->perteneceAgregarABiblioteca(seguridad3,malwareType,"botnets",6);
    
tienda->perteneceAgregarABiblioteca(seguridad4,malwareType,"rootkits",6);
tienda->perteneceAgregarABiblioteca(seguridad5,malwareType,"gusanos",6);
tienda->perteneceAgregarABiblioteca(seguridad6,malwareType,"troyanos",6);
    
//biblioteca prepoblada con 6 Software de Seguridad

SoftwareSocial *social1 = new SoftwareSocial("Twitter","Jack Dorsey",18,2500);
SoftwareSocial *social2 = new SoftwareSocial("Facebook","Mark Zuckerberg",15,2000);

    

tienda->agregarABiblioteca(social1);
tienda->agregarABiblioteca(social2);
















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
//normal1 es amigo de admin1 y normal;

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


SoftwareGame *game21 = new SoftwareGame("Octopath","Square Enix",12,28000,"RPG");
SoftwareGame *game22 = new SoftwareGame("Fire Emblem","Koei Tecmo",12,13000,"RPG");

tienda->perteneceAgregarABiblioteca(game21,gameGenres,"RPG",10);
tienda->perteneceAgregarABiblioteca(game22,gameGenres,"RPG",10);

Usuario *usuarioActual = NULL; Software *softwareActual = NULL;
