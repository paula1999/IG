
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
   const int m = perfil.size();
   const int n = num_copias;
   int k;
   Matriz4f matrizRot;

   // Calculo las normales
   vector<Tupla3f> normalArista;
   Tupla3f aux;

   for (int i = 0; i < perfil.size(); i++){
      aux = perfil[i+1] - perfil[i];
      aux = {aux[Y], -aux[X], 0.0};

      if (aux.lengthSq() > 0)
         normalArista.push_back(aux.normalized());
      else 
         normalArista.push_back(aux);
   }

   for (int i = 0; i < perfil.size(); i++)
      nor_ver.push_back({0.0, 0.0, 0.0});

   if (normalArista[0].lengthSq() != 0)
      nor_ver[0] = normalArista[0].normalized();

   for (int i = 1; i < perfil.size()-1; i++){
      nor_ver[i] = normalArista[i] + normalArista[i-1];

      if (nor_ver[i].lengthSq() != 0)
         nor_ver[i] = nor_ver[i].normalized();
   }

   if (normalArista[perfil.size()-2].lengthSq() != 0)
      nor_ver[perfil.size()-1] = normalArista[perfil.size()-2];

   // Calculo las coordenadas de textura
   vector<float> d, t;
   float suma_total = 0, suma = 0;

   for (int i = 0; i < m-1; i++)
      d.push_back(sqrt((perfil[i+1][0]-perfil[i][0])*(perfil[i+1][0]-perfil[i][0]) + (perfil[i+1][1]-perfil[i][1])*(perfil[i+1][1]-perfil[i][1]) + (perfil[i+1][2]-perfil[i][2])*(perfil[i+1][2]-perfil[i][2])));

   for (int i = 0; i < m-1; i++)
      suma_total += d[i];

   for (int i = 0; i < m-1; i++){
      t.push_back(suma/suma_total);
      suma += d[i];
   }

   t.push_back(1.0);
   


   // COMPLETAR: Práctica 2: completar: creación de la malla....


   // Creación de la tabla de vértices
   for (int i = 0; i < n; i++){
      for (int j = 0; j < m; j++){
         float angulo = 360.0*i/(n-1);
         matrizRot = MAT_Rotacion(angulo, 0.0, 1.0, 0.0);
         vertices.push_back(matrizRot*perfil[j]);
         cc_tt_ver.push_back({(float)i/(n-1), 1-t[j]});

         if (i != 0)
            nor_ver.push_back(matrizRot*nor_ver[j]);
      }
   }

   // Creación de la tabla de triángulos
   for (int i = 0; i < (n-1); i++){
      for (int j = 0; j < (m-1); j++){
         k = i*m + j;
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

   ponerNombre("Cilindro");

   for (int i = 0; i < num_verts_per; i++)
      perfil.push_back({1, (float)i/(num_verts_per-1), 0});

   inicializar(perfil, nperfiles);
}

//Constructor: crea el perfil original y llama a inicializar
// la base tiene el centro en el origen, el radio y la altura son 1
Cilindro2::Cilindro2 (const int num_verts_per, const unsigned nperfiles){
   std::vector<Tupla3f> perfil;

   ponerNombre("Cilindro");

   for (int i = 0; i < num_verts_per; i++)
      perfil.push_back({0.25, (float)i/(num_verts_per-1), 0});

   inicializar(perfil, nperfiles);
}

//Constructor: crea el perfil original y llama a inicializar
// la base tiene el centro en el origen, el radio y la altura son 1
Cono::Cono (const int num_verts_per, const unsigned nperfiles){
   std::vector<Tupla3f> perfil;

   ponerNombre("Cono");

   for(int i = 0; i < num_verts_per; i++)
      perfil.push_back({1-(float)i/(num_verts_per-1),(float)i/(num_verts_per-1),0});

   inicializar(perfil, nperfiles);
}

//Constructor: crea el perfil original y llama a inicializar
// la base tiene el centro en el origen, el radio es la unidad
Esfera::Esfera (const int num_verts_per, const unsigned nperfiles){
   std::vector<Tupla3f> perfil;
   Tupla3f q;
   float angulo;

   ponerNombre("Esfera");

   perfil.push_back({0.0, -1.0, 0.0});

   for (int i = 1; i < num_verts_per; i++){
      angulo = 180.0*i/(num_verts_per-1);
      q = MAT_Rotacion(angulo, 0.0, 0.0, 1.0) * perfil[0];
      perfil.push_back(q);
   }

   inicializar(perfil, nperfiles);
}


