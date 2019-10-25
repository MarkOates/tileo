#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string>


class TileMapMeshRenderer
{
private:
  ALLEGRO_VERTEX_BUFFER *vertex_buffer;
  ALLEGRO_BITMAP *tile_atlas_bitmap;
  int width;
  int height;

public:
   TileMapMeshRenderer(ALLEGRO_BITMAP *tile_atlas_bitmap=nullptr);
   ~TileMapMeshRenderer();

   void render(int camera_x, int camera_y);
};


