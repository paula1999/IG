
// *********************************************************************
// **
// ** Informática Gráfica
// ** Declaraciones de la clase lataPeones.h
// ** Paula Villanueva Nuñez
// *********************************************************************

#ifndef LATAPEONES_H
#define LATAPEONES_H

#include "grafo-escena.h"

using namespace std;

class LataPeones : public NodoGrafoEscena{
    public:
        LataPeones(); // Constructor
};

class Lata : public NodoGrafoEscena{
    public:
        Lata(const string & nombre, const string & textura, int id); // Constructor
};

class CuerpoLata : public NodoGrafoEscena{
    public:
        CuerpoLata(const string & textura); // Constructor
};

class TapaInfLata : public NodoGrafoEscena{
    public:
        TapaInfLata(); // Constructor
};

class TapaSupLata : public NodoGrafoEscena{
    public:
        TapaSupLata(); // Constructor
};

class PeonMadera : public NodoGrafoEscena{
    public:
        PeonMadera(); // Constructor
};

class PeonBlanco : public NodoGrafoEscena{
    public:
        PeonBlanco(); // Constructor
};

class PeonNegro : public NodoGrafoEscena{
    public:
        PeonNegro(); // Constructor
};

class VariasLatasPeones : public NodoGrafoEscena{
    public:
        VariasLatasPeones(); // Constructor
};

#endif // LATAPEONES_H