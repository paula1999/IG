
// *********************************************************************
// **
// ** Informática Gráfica
// ** Declaraciones de la clase modejo-jer.h
// ** Paula Villanueva Nuñez
// *********************************************************************

#ifndef MODELO_JER_H
#define MODELO_JER_H

#include "grafo-escena.h"
#include "malla-ind.h"
#include "malla-revol.h"

// Practica 3

class C : public NodoGrafoEscena{
    private:
        Matriz4f * traslacionSoporteAsiento = nullptr;     // Matriz de traslación del soporte del asiento
        Matriz4f * traslacionRespaldo = nullptr;    // Matriz de traslación del soporte del respaldo
        Matriz4f * rotacionAsiento = nullptr;       // Matriz de rotación del asiento
        Matriz4f * rotacionRespaldo = nullptr;      // Matriz de rotación del respaldo
        unsigned numParametros;

    public:
        C();
        unsigned leerNumParametros() const;
        void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
};

class Respaldo : public NodoGrafoEscena{
    public:
        Respaldo(); // Constructor
};

class Soporte_Respaldo : public NodoGrafoEscena{
    public:
        Soporte_Respaldo(Matriz4f * &traslacionRespaldo); // Constructor
};

class Conector_Bola : public NodoGrafoEscena{
    public:
        Conector_Bola(Matriz4f * &traslacionRespaldo); // Constructor
};

class Conector_Asiento : public NodoGrafoEscena{
    public:
        Conector_Asiento(Matriz4f * &rotacionRespaldo, Matriz4f * &traslacionRespaldo); // Constructor
};

class Asiento : public NodoGrafoEscena{
    public:
        Asiento(Matriz4f * &rotacionAsiento, Matriz4f * &traslacionRespaldo); // Constructor
};

class Soporte_Asiento : public NodoGrafoEscena{
    public:
        Soporte_Asiento(); // Constructor
};

class ConectorPatas : public NodoGrafoEscena{
    public:
        ConectorPatas();
};

class Pata : public NodoGrafoEscena{
    public:
        Pata(); // Constructor
};

class Rueda : public NodoGrafoEscena{
    public:
        Rueda(); // Constructor
};

#endif // MODELO_JER_H