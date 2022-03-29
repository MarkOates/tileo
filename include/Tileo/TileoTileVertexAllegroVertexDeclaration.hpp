#pragma once


#include <allegro5/allegro_primitives.h>


namespace Tileo
{
   class TileoTileVertexAllegroVertexDeclaration
   {
   private:
      ALLEGRO_VERTEX_DECL* vertex_declaration;
      bool initialized;
      bool destructed;

   public:
      TileoTileVertexAllegroVertexDeclaration();
      ~TileoTileVertexAllegroVertexDeclaration();

      bool get_initialized();
      bool get_destructed();
      ALLEGRO_VERTEX_DECL* get_vertex_declaration();
      void initialize();
      void destroy();
   };
}



