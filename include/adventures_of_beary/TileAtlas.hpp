#pragma once




#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <vector>




class TileAtlas
{
private:
   class TileIndexInfo
   {
   public:
      int index_num;

      ALLEGRO_BITMAP *bitmap_source;
      ALLEGRO_BITMAP *sub_bitmap;

      int u1, v1, u2, v2;

      TileIndexInfo();
   };

public:
   std::vector<TileIndexInfo> tile_index;
   ALLEGRO_BITMAP *bitmap;

   void clear();
   static ALLEGRO_BITMAP *build_tile_atlas(int tile_w, int tile_h, std::vector<TileIndexInfo> &tile_index);
   void load(ALLEGRO_BITMAP *tileset, int tile_width, int tile_height, int spacing=0);
   void draw_tile_to_atlas(ALLEGRO_BITMAP *tile, int tile_num, ALLEGRO_COLOR color=al_map_rgba_f(1, 1, 1, 1));
   bool get_tile_uv(int index_num, int *u1, int *v1, int *u2, int *v2);
};




