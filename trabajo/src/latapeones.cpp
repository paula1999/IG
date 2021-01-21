
#include "latapeones.h"
#include "malla-ind.h"
#include "malla-revol.h"
#include "ig-aux.h"
#include "matrices-tr.h"
#include "grafo-escena.h"
#include "materiales-luces.h"
#include <math.h>

using namespace std;

LataPeones::LataPeones(){
    agregar(new Lata("Lata de Coca-Cola", "../recursos/imgs/lata-coke.jpg", 1)); // Lata coca cola
    agregar(MAT_Escalado(0.5, 0.5, 0.5));
    agregar(MAT_Traslacion(0.0, 0.0, 5.5));
    agregar(new PeonMadera()); // Peón de madera
    agregar(MAT_Traslacion(3.0, 0.0, 0.0));
    agregar(new PeonBlanco()); // Peón blanco
    agregar(MAT_Traslacion(3.0, 0.0, 0.0));
    agregar(new PeonNegro()); // Peón negro
    ponerNombre("Lata Peones");
    ponerIdentificador(0);
}

Lata::Lata(const string & nombre, const string & textura, int id){ 
    agregar(MAT_Escalado(3.0, 3.0, 3.0));
    agregar(new CuerpoLata(textura)); // Cuerpo de la lata con textura
    agregar(new TapaInfLata()); // Tapa superior de la lata
    agregar(new TapaSupLata()); // Tapa inferior de la lata
    ponerNombre(nombre);
    ponerIdentificador(id);
}

CuerpoLata::CuerpoLata(const string & textura){
    MallaRevolPLY * pcue = new MallaRevolPLY("../recursos/plys/lata-pcue.ply", 50);
    Textura * texturaPcue = new Textura(textura);    
    Material * materialPcue = new Material(texturaPcue, 0.5, 0.7, 0.9, 10);

    agregar(materialPcue);
    agregar(pcue);
    ponerNombre("Cuepo de la lata");
    ponerIdentificador(-1);
}

TapaInfLata::TapaInfLata(){
    MallaRevolPLY * pinf = new MallaRevolPLY("../recursos/plys/lata-pinf.ply", 50);
    Material * materialPinf = new Material(0.5, 0.7, 0.9, 10);

    agregar(materialPinf);
    agregar(pinf);
    ponerNombre("Tapa inferior de la lata");
    ponerIdentificador(-1);
}

TapaSupLata::TapaSupLata(){
    MallaRevolPLY * psup = new MallaRevolPLY("../recursos/plys/lata-psup.ply", 50);
    Material * materialPsup = new Material(0.5, 0.7, 0.9, 10);

    agregar(materialPsup);
    agregar(psup);
    ponerNombre("Tapa superior de la lata");
    ponerIdentificador(-1);
}

PeonMadera::PeonMadera(){
    MallaRevolPLY * peon = new MallaRevolPLY("../recursos/plys/peon.ply", 20);
    Textura * texturaPeon = new Textura("../recursos/imgs/text-madera.jpg");
    Material * materialPeon = new Material(texturaPeon, 0.5, 0.7, 0.9, 10);

    agregar(MAT_Traslacion(0.0, 1.4, 0.0));
    agregar(materialPeon);
    agregar(peon);
    ponerNombre("Peon de madera");
    ponerIdentificador(4);
}

PeonBlanco::PeonBlanco(){
    MallaRevolPLY * peon = new MallaRevolPLY("../recursos/plys/peon.ply", 20);
    Material * materialPeon = new Material(0.0, 1.0, 0.0, 10);

    agregar(MAT_Traslacion(0.0, 1.4, 0.0));
    peon->ponerColor({0.0, 0.0, 0.0});
    agregar(materialPeon);
    agregar(peon);
    ponerNombre("Peon blanco");
    ponerIdentificador(5);
}

PeonNegro::PeonNegro(){
    MallaRevolPLY * peon = new MallaRevolPLY("../recursos/plys/peon.ply", 20);
    Material * materialPeon = new Material(0.1, 0.1, 0.5, 10);

    agregar(MAT_Traslacion(0.0, 1.4, 0.0));
    peon->ponerColor({1.0, 1.0, 1.0});
    agregar(materialPeon);
    agregar(peon);
    ponerNombre("Peon negro");
    ponerIdentificador(6);
}

VariasLatasPeones::VariasLatasPeones(){
    agregar(new LataPeones()); // Lata Peones
    agregar(MAT_Traslacion(3.0, 0.0, 0.0));
    agregar(new Lata("Lata de Pepsi", "../recursos/imgs/lata-pepsi.jpg", 2)); // Lata pepsi
    agregar(MAT_Traslacion(3.0, 0.0, 0.0));
    agregar(new Lata("Lata de la UGR", "../recursos/imgs/window-icon.jpg", 3)); // Lata UGR
    ponerIdentificador(0);
    ponerNombre("Varias latas y peones");
}