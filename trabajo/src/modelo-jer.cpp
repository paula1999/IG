
#include "modelo-jer.h"
#include "malla-ind.h"
#include "malla-revol.h"
#include "grafo-escena.h"
#include "ig-aux.h"
#include <math.h>

using namespace std;


C::C(){
    unsigned k;
    
    numParametros = 4;

    ponerNombre("Silla giratoria");  

    agregar(new ConectorPatas());

    // Primer soporte del asiento
    agregar(MAT_Traslacion(0.0, 0.12, 0.0));
    agregar(new Soporte_Asiento());
    
    // Segundo soporte del asiento
    k = agregar(MAT_Traslacion(0.0, 0.0, 0.0));
    traslacionSoporteAsiento = leerPtrMatriz(k);
    agregar(new Soporte_Asiento());

    agregar(MAT_Traslacion(0.0, 1.1, 0.0));
    k = agregar(MAT_Rotacion(0.0, 0.0, 1.0, 0.0));
    rotacionAsiento = leerPtrMatriz(k);
    agregar(new Asiento(rotacionRespaldo, traslacionRespaldo));
    
    ponerIdentificador(0);
}

unsigned C::leerNumParametros() const{
    return numParametros;
}

void C::actualizarEstadoParametro (const unsigned iParam, const float t_sec){
    assert(iParam < leerNumParametros());

    float trasl;

    switch(iParam){
        case 0:
            // Fijar inclinación del respaldo
            *rotacionRespaldo = MAT_Rotacion(sin(0.5*M_PI*t_sec)*10 - 10, 0.0, 0.0, 1.0);
            break;
        
        case 1:
            // Fijar traslación del soporte del respaldo
            trasl = 0.5*sin(M_PI*t_sec*0.5);
            *traslacionRespaldo = MAT_Traslacion(-0.2, 0.0, -1.0-trasl); 
            break;

        case 2:
            // Fijar rotación del asiento
            *rotacionAsiento = MAT_Rotacion(t_sec*60, 0.0, 1.0, 0.0); 
            break;

        case 3:
            // Fijar rotación del respaldo
            trasl = 0.5+0.5*sin(M_PI*t_sec*0.5);
            *traslacionSoporteAsiento = MAT_Traslacion(0.0, trasl, 0.0);
            break;
    }
}

Respaldo::Respaldo(){
    Cubo * cubo = new Cubo();
    unsigned k;
    
    agregar(MAT_Escalado(0.15, 1.0, 1.0));
    
    cubo->ponerColor({0.3, 0.7, 0.4});
    
    agregar(cubo);
    ponerIdentificador(1);
}

Soporte_Respaldo::Soporte_Respaldo(Matriz4f * &traslacionRespaldo){
    unsigned k;
    Cubo * cubo = new Cubo();

    agregar(MAT_Escalado(0.1, 1.0, 0.1));
    
    cubo->ponerColor({0.4, 0.2, 0.5});
    
    agregar(cubo);

    // Respaldo
    agregar(MAT_Escalado(11.0, 1.0, 11.0));
    agregar(MAT_Rotacion(90.0, 1.0, 0.0, 0.0));
    k = agregar(MAT_Traslacion(-0.2, 0.0, -0.6));
    traslacionRespaldo = leerPtrMatriz(k);
    agregar(new Respaldo());

    ponerIdentificador(2);
}

Conector_Bola::Conector_Bola (Matriz4f * &traslacionRespaldo){
    unsigned k;
    Esfera * esfera = new Esfera(40, 60);
    
    agregar(MAT_Escalado(0.28, 0.28, 0.28));
    
    esfera->ponerColor({0.5, 0.2, 1.0});
    
    agregar(esfera);

    // Soporte del respaldo
    agregar(MAT_Escalado(6.0, 6.0, 6.0));
    agregar(MAT_Traslacion(0.0, 1.1, 0.0));
    agregar(new Soporte_Respaldo(traslacionRespaldo));

    ponerIdentificador(3);
}

Conector_Asiento::Conector_Asiento(Matriz4f * &rotacionRespaldo, Matriz4f * &traslacionRespaldo){
    unsigned k;
    Cubo * cubo = new Cubo();

    agregar(MAT_Escalado(0.1, 0.1, 0.1));
    
    cubo->ponerColor({0.4, 0.2, 0.5});
    
    agregar(cubo);

    // Conector bola entre el asiento y el respaldo
    agregar(MAT_Traslacion(1.5, 0.0, 0.0));
    agregar(MAT_Escalado(5.0, 7.0, 5.0));
    k = agregar(MAT_Rotacion(0.0, 1.0, 0.0, 0.0));
    rotacionRespaldo = leerPtrMatriz(k);
    agregar(new Conector_Bola(traslacionRespaldo));

    ponerIdentificador(4);
}

Asiento::Asiento(Matriz4f * &rotacionRespaldo, Matriz4f * &traslacionRespaldo){
    Cubo * cubo = new Cubo();
    unsigned k;

    agregar(MAT_Escalado(1.0, 0.15, 1.0));    

    cubo->ponerColor({0.0, 0.7, 1.0});

    agregar(cubo);

    // Conector del asiento a la bola
    agregar(MAT_Escalado(1.0, 5.0, 1.0));  
    agregar(MAT_Traslacion(1.1, 0.0, 0.0));
    agregar(new Conector_Asiento(rotacionRespaldo, traslacionRespaldo));

    ponerIdentificador(5);
}

Soporte_Asiento::Soporte_Asiento(){
    Cilindro2 * cilindro = new Cilindro2(40, 60);
    
    cilindro->ponerColor({0.0, 0.0, 0.2});
    
    agregar(cilindro);

    ponerIdentificador(6);
}

ConectorPatas::ConectorPatas(){
    unsigned k;
    Esfera * esfera = new Esfera(40, 60);

    agregar(MAT_Escalado(0.25, 0.25, 0.25));

    esfera->ponerColor({0.5, 0.2, 1.0});

    agregar(esfera);

    // Pata 1
    agregar(MAT_Rotacion(90.0, 1.0, 0.0, 0.0));
    agregar(MAT_Traslacion(0.0, 0.2, 0.0));
    agregar(new Pata());

    // Pata 2
    agregar(MAT_Rotacion(90.0, 0.0, 0.0, 1.0));
    agregar(MAT_Traslacion(-0.2, 0.2, 0.0));
    agregar(new Pata());

    // Pata 3
    agregar(MAT_Rotacion(90.0, 0.0, 0.0, 1.0));
    agregar(MAT_Traslacion(-0.2, 0.2, 0.0));
    agregar(new Pata());
    
    // Pata 4
    agregar(MAT_Rotacion(90.0, 0.0, 0.0, 1.0));
    agregar(MAT_Traslacion(-0.2, 0.2, 0.0));
    agregar(new Pata());

    ponerIdentificador(0);
}

Pata::Pata(){
    Cilindro2 * cilindro = new Cilindro2(40, 60);

    agregar(MAT_Escalado(1.5, 4.0, 1.5));
    
    cilindro->ponerColor({0.0, 0.0, 0.0});

    agregar (cilindro);

    agregar(MAT_Escalado(1.0, -0.4, 1.1));
    agregar(MAT_Rotacion(-90.0, 1.0, 0.0, 0.0));
    agregar(MAT_Traslacion(0.0, -0.05, -2.5));
    agregar(new Rueda());

    ponerIdentificador(7);
}

Rueda::Rueda(){
    unsigned k;
    Esfera * esfera = new Esfera(40, 60);
    
    agregar(MAT_Escalado(0.28, 0.28, 0.28));
    
    esfera->ponerColor({0.5, 0.2, 1.0});
    
    agregar(esfera);

    ponerIdentificador(8);
}