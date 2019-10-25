#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <string>


class TileMapMeshRenderer
{
private:
  ALLEGRO_VERTEX_BUFFER *vertex_buffer;
  ALLEGRO_BITMAP *tile_atlas_bitmap;
  int camera_x;
  int camera_y;

public:
   TileMapMeshRenderer(ALLEGRO_BITMAP *tile_atlas_bitmap=nullptr, int camera_x=0, int camera_y=0);
   ~TileMapMeshRenderer();

   void render();
};


