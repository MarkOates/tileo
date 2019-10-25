#pragma once


#include <adventures_of_beary/TileAtlas.hpp>
#include <adventures_of_beary/TileMapMeshRenderer.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <vector>


class TileMap
{
private:
   ALLEGRO_VERTEX_BUFFER *vertex_buffer;
   std::vector<ALLEGRO_VERTEX> vtx;
   int width;
   int height;
   std::vector<int> tiles;

   bool use_vtx;

public:

   TileMap();
   ~TileMap();

   int get_width();
   int get_height();
   int infer_num_tiles();

   int get_tile(int tile_x, int tile_y);
   bool set_tile(TileAtlas &tile_atlas, TileMapMeshRenderer &mesh_renderer, int tile_x, int tile_y, int tile_index);
   //bool set_contiguous_tile_num(TileAtlas &tile_atlas, int contiguous_tile_num, int tile_index);

   void resize(TileMapMeshRenderer &mesh_renderer, int w, int h, int tile_w, int tile_h);
};


