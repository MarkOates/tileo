#pragma once


#include <string>
#include <vector>


namespace Tileo
{
   class TMJDataLoader
   {
   private:
      std::string filename;
      int num_columns;
      int num_rows;
      int tmx_tilewidth;
      int tmx_tileheight;
      int tilelayer_width;
      int tilelayer_height;
      std::vector<int> tiles;
      bool loaded;

   public:
      TMJDataLoader(std::string filename="filename-not-set.tmj");
      ~TMJDataLoader();

      int get_num_columns();
      int get_num_rows();
      int get_tmx_tilewidth();
      int get_tmx_tileheight();
      int get_tilelayer_width();
      int get_tilelayer_height();
      std::vector<int> get_tiles();
      bool get_loaded();
      bool load();
   };
}



