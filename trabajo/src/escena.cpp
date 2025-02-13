

#include "ig-aux.h"
#include "escena.h"

#include "objeto3d.h"
#include "malla-ind.h"
#include "malla-revol.h"
#include "practicas.h"
#include "camara.h"
#include "materiales-luces.h"
#include "seleccion.h"
#include "modelo-jer.h"
#include "latapeones.h"

using namespace std;




// -----------------------------------------------------------------------------------------------

Escena::Escena()
{
   // COMPLETAR: Práctica 4: inicializar 'col_fuentes' y 'material_ini'
   // ...

   col_fuentes = new Col2Fuentes();
   material_ini = new Material(0.3, 0.6, 0.1, 2);
   // COMPLETAR: Práctica 5: hacer 'push_back' de varias camaras perspectiva u ortogonales,
   // (sustituir la cámara orbital simple ('CamaraOrbitalSimple') por varias cámaras de 3 modos ('Camara3Modos')
   camaras.push_back( new Camara3Modos(true,{5.0, 1.0, 1.0}, 1.0, {2.0, 1.0, 1.0}, 50.0)); // Vista de frente perspectiva
   camaras.push_back( new Camara3Modos(false,{6.5, 6.5, 6.5}, 1.0, {4.0, 4.0, 4.0}, 70.0)); // Vista alzado ortogonal
   camaras.push_back( new Camara3Modos(true, {4.0, 3.0, 1.0}, 1.0, {2.0, 1.0, 4.0}, 80.0)); // Vista perfil perspectiva
}
// -----------------------------------------------------------------------------------------------
// visualiza la escena en la ventana actual, usando la configuración especificada en 'cv'

void Escena::visualizarGL( ContextoVis & cv )
{
   // recuperar el cauce actual de 'cv' en 'cauce', activarlo
   Cauce * cauce = cv.cauce_act ; assert( cauce != nullptr );
   cauce->activar() ;

   // recuperar la cámara actual de esta escena y  fijar las matrices 'modelview'
   // y 'projection' en el cauce gráfico (es decir: activar la cámara actual)
   CamaraInteractiva * camara = camaras[ind_camara_actual] ; assert( camara != nullptr );
   const float ratio_vp = float(cv.ventana_tam_y)/float(cv.ventana_tam_x) ;
   camara->fijarRatioViewport( ratio_vp );
   camara->activar( *cauce ) ;


   // dibujar los ejes, si procede
   if ( cv.dibujar_ejes  )
      DibujarEjesSolido( *cauce ) ;

   // fijar el color por defecto en el cauce para dibujar los objetos
   // if ( cv.fondo_blanco && ! cv.iluminacion )
   //    glColor3f( 0.0, 0.0, 0.0 );
   // else
   //    glColor3f( 1.0, 1.0, 1.0 );
   glColor3f( 1.0, 1.0, 1.0 );

   // COMPLETAR: Práctica 1: Configurar el cauce en función de:
   //    cv.sombr_plano (true/false)              --> usar fijarModoSombrPlano (método del 'cauce')
   //    cv.modo_visu   (puntos,lineas o relleno) --> usar glPolygonMode
   cauce->fijarModoSombrPlano(cv.sombr_plano);

   GLenum modo_visuGL;

   switch (cv.modo_visu){
      case ModosVisu::relleno:
         modo_visuGL = GL_FILL;
         break;

      case ModosVisu::lineas:
         modo_visuGL = GL_LINE;
         break;

      case ModosVisu::puntos:
         modo_visuGL = GL_POINT;
         break;
   }

   glPolygonMode(GL_FRONT_AND_BACK, modo_visuGL);

   if ( cv.iluminacion )
   {
      // COMPLETAR: Práctica 4: activar evaluación del MIL (y desactivar texturas)
      // * habilitar evaluación del MIL en el cauce (fijarEvalMIL)
      // * activar la colección de fuentes de la escena
      // * activar el material inicial
      // ....
      cauce->fijarEvalMIL(true);
      col_fuentes->activar(*cauce);

      if (material_ini != nullptr){
         cv.material_act = material_ini;
         material_ini->activar(*cauce);
      }
   }
   else // si la iluminación no está activada, deshabilitar MIL y texturas
   {  cauce->fijarEvalMIL( false );
      cauce->fijarEvalText( false );
   }

   // recuperar el objeto actual de esta escena
   Objeto3D * objeto = objetos[ind_objeto_actual] ; assert( objeto != nullptr );

   // COMPLETAR: Práctica 1: visualizar el objeto actual ('objeto')
   objeto->visualizarGL(cv);


   if ( cv.visualizar_normales && !cv.modo_seleccion )
      visualizarNormales( cv );


   // si hay un FBO, dibujarlo (opcional...)


}





// -----------------------------------------------------------------------------------------------
// pasa la cámara actual a la siguiente

void Escena::siguienteCamara()
{
   assert( ind_camara_actual < camaras.size() );
   ind_camara_actual = (ind_camara_actual+1 ) % camaras.size();
   cout << "Cámara actual cambiada a: " << (ind_camara_actual+1) << " (de " << camaras.size() << ")" << endl ;
}

// -----------------------------------------------------------------------------------------------
// pasa el objeto actual al siguiente

void Escena::siguienteObjeto()
{
   if ( objetos.size() == 0 )
      return ;
   assert( ind_objeto_actual < objetos.size() );
   ind_objeto_actual = (ind_objeto_actual+1 ) % objetos.size();
   cout << "Objeto actual cambiado a: " << objetoActual()->leerNombre()
        << " (" << (ind_objeto_actual+1) << "/" << objetos.size() << ")." << endl  ;
}

// -----------------------------------------------------------------------------------------------
// devuelve puntero al objeto actual

Objeto3D * Escena::objetoActual()
{
   assert( ind_objeto_actual < objetos.size() );
   assert( objetos[ind_objeto_actual] != nullptr );
   return objetos[ind_objeto_actual] ;
}
// -----------------------------------------------------------------------------------------------
// devuelve un puntero a la cámara actual

CamaraInteractiva * Escena::camaraActual()
{
   assert( ind_camara_actual < camaras.size() );
   assert( camaras[ind_camara_actual] != nullptr );
   return camaras[ind_camara_actual] ;
}
// -----------------------------------------------------------------------------------------------
// devuelve un puntero a la colección de fuentes actual

ColFuentesLuz * Escena::colFuentes()
{
   assert( col_fuentes != nullptr );
   return col_fuentes ;
}

void Escena::visualizarNormales (ContextoVis & cv){
   // recuperar el objeto raiz de esta escena y comprobar que está ok.
   bool ilum_ant = cv.iluminacion ;
   assert( cv.cauce_act != nullptr );
   Objeto3D * objeto = objetos[ind_objeto_actual] ; assert( objeto != nullptr );

   // configurar el cauce:
   cv.cauce_act->fijarEvalMIL( false );
   cv.cauce_act->fijarEvalText( false );
   cv.cauce_act->fijarModoSombrPlano( true ); // sombreado plano
   glLineWidth( 1.5 ); // ancho de líneas (se queda puesto así)
   glColor4f( 1.0, 0.7, 0.4, 1.0 ); // color de las normales

   // configurar el contexto de visualizacion
   cv.visualizando_normales = true ;   // hace que MallaInd::visualizarGL visualize las normales.
   cv.iluminacion           = false ;

   // visualizar objeto actual
   objetos[ind_objeto_actual]->visualizarGL( cv );

   // restaurar atributos cambiados en el contexto de visualización
   cv.visualizando_normales = false ;
   cv.iluminacion = ilum_ant ;
}

// -----------------------------------------------------------------------------------------------

Escena1::Escena1()
{
   cout << "Creando objetos de escena 1 .... " << flush ;

   // añadir el objeto 'Cubo' a la lista de objetos de esta escena:
   objetos.push_back( new Cubo() );

   // COMPLETAR: Práctica 1: creación del resto objetos de la práctica 1
   // Añadir objetos al vector 'objetos', con:
   //     objetos.push_back( new .... )
   // .........
   objetos.push_back(new Tetraedro());
   objetos.push_back(new CuboColores());


   cout << "hecho." << endl << flush ;
}

// -------------------------------------------------------------------------
// COMPLETAR: Práctica 2
// Añadir la implementación del constructor de la clase Escena2 para construir
// los objetos que se indican en los guiones de las práctica 2
// .......

Escena2::Escena2()
{
   cout << "Creando objetos de escena 2 .... " << flush ;

   // añadir objetos a la lista de objetos de esta escena:
   objetos.push_back(new MallaPLY("../recursos/plys/ant.ply"));
   objetos.push_back(new MallaPLY("../recursos/plys/beethoven.ply"));
   objetos.push_back(new MallaPLY("../recursos/plys/big_dodge.ply"));
   objetos.push_back(new MallaRevolPLY("../recursos/plys/lata-pcue.ply", 20));
   objetos.push_back(new MallaRevolPLY("../recursos/plys/lata-pinf.ply", 20));
   objetos.push_back(new MallaRevolPLY("../recursos/plys/lata-psup.ply", 20));
   objetos.push_back(new MallaRevolPLY("../recursos/plys/peon.ply", 20));
   objetos.push_back(new Cilindro(10, 30));
   objetos.push_back(new Cono(15, 35));
   objetos.push_back(new Esfera(10, 40));

   cout << "hecho." << endl << flush ;
}

// -------------------------------------------------------------------------
// COMPLETAR: Práctica 3
// Añadir la implementación del constructor de la clase Escena3 para construir
// los objetos que se indican en los guiones de las práctica 3
// .......
Escena3::Escena3(){
   cout << "Creando objetos de escena 3 .... " << flush ;

   objetos.push_back(new C());

   cout << "hecho." << endl << flush ;
}


// ----------------------------------------------------------------------
// COMPLETAR: Práctica 4
// Añadir la implementación del constructor de la clase Escena4 para construir
// los objetos que se indican en los guiones de las práctica 4
// .......

Escena4::Escena4(){
   cout << "Creando objetos de escena 4 .... " << flush ;

   objetos.push_back(new LataPeones());
   objetos.push_back(new NodoCubo24());

   cout << "hecho." << endl << flush ;
}

// ----------------------------------------------------------------------
// COMPLETAR: Práctica 5
// Añadir la implementación del constructor de la clase Escena5 para construir
// los objetos que se indican en los guiones de las práctica 5
// .......
Escena5::Escena5(){
   cout << "Creando objetos de escena 5 .... " << flush ;

   objetos.push_back(new VariasLatasPeones());

   cout << "hecho." << endl << flush ;
}