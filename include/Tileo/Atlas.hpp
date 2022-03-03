#pragma once



#include <Tileo/TileIndexInfo.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <vector>


namespace Tileo
{
   class Atlas
   {
   private:
      ALLEGRO_BITMAP *bitmap;
      std::string bitmap_filename;
      std::vector<Tileo::TileIndexInfo> tile_index;

      void clear();

   public:
      Atlas();
      ~Atlas();

      void duplicate_bitmap_and_load(ALLEGRO_BITMAP *source_bitmap, int tile_width, int tile_height, int spacing=0);

      ALLEGRO_BITMAP *get_bitmap();
      std::string get_bitmap_filename() const;
      void set_bitmap_filename(std::string bitmap_filename="unset-bitmap-filename.png");
      int get_tile_index_size();

      void draw_tile_to_atlas(ALLEGRO_BITMAP *tile, int tile_num, ALLEGRO_COLOR color=al_map_rgba_f(1, 1, 1, 1));
      bool get_tile_uv(int index_num, int *u1, int *v1, int *u2, int *v2);
      ALLEGRO_BITMAP *get_bitmap(int index_num);
   };
}


