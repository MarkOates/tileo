#pragma once



#include <Tileo/TileIndexInfo.hpp>
#include <allegro5/allegro.h>
#include <vector>


namespace Tileo
{
   class TileAtlas
   {
   private:
      ALLEGRO_BITMAP *bitmap;
      std::vector<Tileo::TileIndexInfo> tile_index;

      void clear();

   public:
      TileAtlas();
      ~TileAtlas();

      ALLEGRO_BITMAP *get_bitmap();
      int get_tile_index_size();

      void load(ALLEGRO_BITMAP *tileset, int tile_width, int tile_height, int spacing=0);
      void draw_tile_to_atlas(ALLEGRO_BITMAP *tile, int tile_num, ALLEGRO_COLOR color=al_map_rgba_f(1, 1, 1, 1));
      bool get_tile_uv(int index_num, int *u1, int *v1, int *u2, int *v2);
      ALLEGRO_BITMAP *get_bitmap(int index_num);
   };
}


