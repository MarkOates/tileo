#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <Tileo/TileAtlas.hpp>
#include <vector>


namespace Tileo
{
   class Mesh
   {
   private:
      ALLEGRO_VERTEX_BUFFER *vertex_buffer;
      std::vector<ALLEGRO_VERTEX> vertexes;
      ALLEGRO_BITMAP *tile_atlas_bitmap;
      int width;
      int height;
      bool use_primitive;

      void set_tile_uv(int tile_x, int tile_y, int u1, int v1, int u2, int v2);

   public:
      Mesh(ALLEGRO_BITMAP *tile_atlas_bitmap=nullptr);
      ~Mesh();

      int get_width();
      int get_height();
      int infer_num_tiles();

      bool set_tile(Tileo::TileAtlas &tile_atlas, int tile_x, int tile_y, int tile_id);
      void set_tile_atlas_bitmap(ALLEGRO_BITMAP *tile_atlast_bitmap);
      void resize(int w, int h, int tile_w, int tile_h);
   
      void render(int camera_x, int camera_y);
   };
}


