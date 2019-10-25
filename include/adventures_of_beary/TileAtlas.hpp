#pragma once




#include <adventures_of_beary/TileIndexInfo.hpp>
#include <allegro5/allegro.h>
#include <vector>




class TileAtlas
{
private:
   ALLEGRO_BITMAP *bitmap;
   void clear();

public:
   std::vector<TileIndexInfo> tile_index;

   static ALLEGRO_BITMAP *build_tile_atlas(int tile_w, int tile_h, std::vector<TileIndexInfo> &tile_index);
   void load(ALLEGRO_BITMAP *tileset, int tile_width, int tile_height, int spacing=0);
   void draw_tile_to_atlas(ALLEGRO_BITMAP *tile, int tile_num, ALLEGRO_COLOR color=al_map_rgba_f(1, 1, 1, 1));
   bool get_tile_uv(int index_num, int *u1, int *v1, int *u2, int *v2);
};




