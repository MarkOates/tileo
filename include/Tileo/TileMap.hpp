#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <vector>


namespace Tileo
{
   class TileMap
   {
   private:
      int width;
      int height;
      std::vector<int> tiles;

   public:

      TileMap();
      ~TileMap();

      int get_width();
      int get_height();
      int infer_num_tiles();
      bool is_dimensionless();

      int get_tile(int tile_x, int tile_y);
      bool set_tile(int tile_x, int tile_y, int value);
      std::pair<int, int> get_coordinates_from_contiguous_number(int contiguous_tile_num);

      void resize(int w, int h);
   };
}


