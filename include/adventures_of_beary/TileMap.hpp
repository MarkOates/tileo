#pragma once




#include <adventures_of_beary/TileAtlas.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <vector>




class TileMap
{
private:
   void set_tile_uv(int tile_x, int tile_y, int u1, int v1, int u2, int v2);

   ALLEGRO_VERTEX_BUFFER *vertex_buffer;
   std::vector<ALLEGRO_VERTEX> vtx;
   TileAtlas *tile_atlas;
   int width;
   int height;
   std::vector<int> tiles;

   bool use_vtx;

public:

   TileMap();

   void resize(int w, int h, int tile_w, int tile_h);
   void use_tile_atlas(TileAtlas *atlas);

   int get_width();
   int get_height();
   int get_num_tiles();
   int get_tile(int tile_x, int tile_y);
   bool set_tile(int tile_x, int tile_y, int tile_index);
   bool set_contiguous_tile_num(int contiguous_tile_num, int tile_index);

   void draw(int camera_x, int camera_y);
};




