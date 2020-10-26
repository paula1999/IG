// *********************************************************************
// **
// ** Informática Gráfica, curso 2019-20
// ** Implementación de la clase 'MallaRevol'
// **
// *********************************************************************

#include "ig-aux.h"
#include "tuplasg.h"
#include "lector-ply.h"
#include "matrices-tr.h"
#include "malla-revol.h"
#include "math.h"

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<Tupla3f> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   // COMPLETAR: Práctica 2: completar: creación de la malla....
   const int m = perfil.size();
   const int n = num_copias;
   int k;
   Tupla3f q;

   // Creación de la tabla de vértices
   for (int i = 0; i < n; i++){
      for (int j = 0; j < m; j++){
         float angulo = 360.0*i/(n-1);
         q = MAT_Rotacion(angulo, 0.0, 1.0, 0.0) * perfil[j];
         vertices.push_back(q);
      }
   }

   // Creación de la tabla de triángulos
   for (int i = 0; i < (n-1); i++){
      for (int j = 0; j < (m-1); j++){
         k = i*m +j;
         triangulos.push_back({k, k+m, k+m+1});
         triangulos.push_back({k, k+m+1, k+1});
      }
   }



}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................
   vector<Tupla3f> perfil;
   LeerVerticesPLY(nombre_arch, perfil);
   inicializar(perfil, nperfiles);
}

//Constructor: crea el perfil original y llama a inicializar
// la base tiene el centro en el origen, el radio y la altura son 1

Cilindro::Cilindro (const int num_verts_per, const unsigned nperfiles){
   std::vector<Tupla3f> perfil;

   for (int i = 0; i < num_verts_per; i++)
      perfil.push_back({1, (float)i/(num_verts_per-1), 0});

   inicializar(perfil, nperfiles);
}

//Constructor: crea el perfil original y llama a inicializar
// la base tiene el centro en el origen, el radio y la altura son 1
Cono::Cono (const int num_verts_per, const unsigned nperfiles){
   std::vector<Tupla3f> perfil;

   for(int i = 0; i < num_verts_per; i++)
      perfil.push_back({1-(float)i/(num_verts_per-1),(float)i/(num_verts_per-1),0});

   inicializar(perfil, nperfiles);
}

//Constructor: crea el perfil original y llama a inicializar
// la base tiene el centro en el origen, el radio es la unidad
Esfera::Esfera (const int num_verts_per, const unsigned nperfiles){

}


