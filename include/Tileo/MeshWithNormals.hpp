#pragma once


#include <Tileo/TileoTileVertex.hpp>
#include <Tileo/TileoTileVertexAllegroVertexDeclaration.hpp>
#include <vector>


namespace Tileo
{
   class MeshWithNormals
   {
   private:
      Tileo::TileoTileVertexAllegroVertexDeclaration tileo_tile_vertex_allegro_vertex_declaration;
      int num_columns;
      int num_rows;
      float tile_width;
      float tile_height;
      std::vector<int> tile_ids;
      std::vector<int> normal_tile_ids;
      std::vector<TILEO_TILE_VERTEX> vertexes;
      bool initialized;
      bool destroyed;

   public:
      MeshWithNormals(int num_columns=0, int num_rows=0, float tile_width=1.0f, float tile_height=1.0f);
      ~MeshWithNormals();

      void initialize();
      void destroy();
      void resize(int num_columns=1, int num_rows=1);
      void clear_and_reserve();
   };
}



