#pragma once


#include <Tileo/Atlas.hpp>
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
      Tileo::Atlas* atlas;
      Tileo::Atlas* normal_atlas;
      std::vector<int> tile_ids;
      std::vector<int> normal_tile_ids;
      std::vector<TILEO_TILE_VERTEX> vertexes;
      bool initialized;
      bool destroyed;

   public:
      MeshWithNormals(int num_columns=0, int num_rows=0, float tile_width=1.0f, float tile_height=1.0f, Tileo::Atlas* atlas=nullptr, Tileo::Atlas* normal_atlas=nullptr);
      ~MeshWithNormals();

      void initialize();
      void destroy();
      void resize(int num_columns=1, int num_rows=1);
      bool set_tile(int tile_x=0, int tile_y=0, int tile_index_num=0);
      bool set_tile_uv(int tile_x=0, int tile_y=0, float u1=0.0f, int v1=0.0f, float u2=0.0f, int v2=0.0f);
      bool set_normal_tile_uv(int tile_x=0, int tile_y=0, float u1=0.0f, int v1=0.0f, float u2=0.0f, int v2=0.0f);
      void place_vertexes_into_tile_mesh_shape();
      void clear_and_reserve();
   };
}



