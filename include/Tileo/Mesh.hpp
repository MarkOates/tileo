#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <Tileo/Atlas.hpp>
#include <vector>


namespace Tileo
{
   class Mesh
   {
   private:
      Tileo::Atlas *atlas;
      ALLEGRO_VERTEX_BUFFER *vertex_buffer;
      std::vector<ALLEGRO_VERTEX> vertexes;
      //ALLEGRO_BITMAP *atlas_bitmap;
      int width;
      int height;
      bool use_primitive;
      bool initialized;

      void set_tile_uv(int tile_x, int tile_y, int u1, int v1, int u2, int v2);

   public:
      Mesh(Tileo::Atlas *atlas=nullptr); //ALLEGRO_BITMAP *atlas_bitmap=nullptr);
      ~Mesh();

      void initialize(int w, int h, int tile_w, int tile_h);

      int get_width();
      int get_height();
      int infer_num_tiles();

      bool set_tile(int tile_x, int tile_y, int tile_id);
      //void set_atlas_bitmap(ALLEGRO_BITMAP *atlast_bitmap); // this should probably be removed
      //void initialize(int w, int h, int tile_w, int tile_h);
   
      void render(); //int camera_x, int camera_y);
   };
}

