#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <adventures_of_beary/TileAtlas.hpp>
#include <vector>


class TileMapMeshRenderer
{
private:
   ALLEGRO_VERTEX_BUFFER *vertex_buffer;
   std::vector<ALLEGRO_VERTEX> vtx;
   ALLEGRO_BITMAP *tile_atlas_bitmap;
   int width;
   int height;
   bool use_primitive;

   void set_tile_uv(int tile_x, int tile_y, int u1, int v1, int u2, int v2);

public:
   TileMapMeshRenderer(ALLEGRO_BITMAP *tile_atlas_bitmap=nullptr);
   ~TileMapMeshRenderer();

   int get_width();
   int get_height();
   int infer_num_tiles();

   bool set_tile_to_mesh(TileAtlas &tile_atlas, int tile_x, int tile_y, int tile_index);
   void resize_mesh(int w, int h, int tile_w, int tile_h);

   void render(int camera_x, int camera_y);
};


