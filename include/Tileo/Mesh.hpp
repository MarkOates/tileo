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
      std::vector<int> tile_ids;
      //ALLEGRO_BITMAP *atlas_bitmap;
      int num_columns;
      int num_rows;
      int tile_width;
      int tile_height;
      bool use_primitive;
      bool initialized;

      void set_tile_uv(int tile_x, int tile_y, int u1, int v1, int u2, int v2);

   public:
      Mesh(Tileo::Atlas *atlas=nullptr, int num_columns=0, int num_rows=0, int tile_width=1, int tile_heigh=1);
      ~Mesh();

      void initialize();

      std::vector<ALLEGRO_VERTEX> &get_vertexes_ref();

      int get_num_columns();
      int get_num_rows();
      int infer_num_tiles();

      bool set_tile(int tile_x, int tile_y, int tile_id);
      const int get_tile_id(int tile_x, int tile_y);
      const std::vector<int> get_tile_ids();
      //void set_atlas_bitmap(ALLEGRO_BITMAP *atlast_bitmap); // this should probably be removed
      //void initialize(int w, int h, int tile_w, int tile_h);
   
      void render(bool draw_frame=false); //int camera_x, int camera_y);
   };
}


