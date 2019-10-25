#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>


class TileMapMeshRenderer
{
private:
   ALLEGRO_VERTEX_BUFFER *vertex_buffer;
   std::vector<ALLEGRO_VERTEX> vtx;
   ALLEGRO_BITMAP *tile_atlas_bitmap;
   int width;
   int height;
   bool use_vtx;

public:
   TileMapMeshRenderer(ALLEGRO_BITMAP *tile_atlas_bitmap=nullptr);
   ~TileMapMeshRenderer();

   int get_width();
   int get_height();
   int infer_num_tiles();

   void render(int camera_x, int camera_y);
};


