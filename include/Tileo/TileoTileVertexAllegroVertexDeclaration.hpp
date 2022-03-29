#pragma once


#include <allegro5/allegro_primitives.h>


namespace Tileo
{
   class TileoTileVertexAllegroVertexDeclaration
   {
   private:
      ALLEGRO_VERTEX_DECL* vertex_declaration;
      bool initialized;
      bool destroyed;

   public:
      TileoTileVertexAllegroVertexDeclaration();
      ~TileoTileVertexAllegroVertexDeclaration();

      bool get_initialized();
      bool get_destroyed();
      ALLEGRO_VERTEX_DECL* get_vertex_declaration();
      void initialize();
      void destroy();
   };
}



