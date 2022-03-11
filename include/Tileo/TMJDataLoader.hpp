#pragma once


#include <string>
#include <vector>


namespace Tileo
{
   class TMJDataLoader
   {
   private:
      std::string filename;
      int tmx_width;
      int tmx_height;
      int tmx_tilewidth;
      int tmx_tileheight;
      int tilelayer_width;
      int tilelayer_height;
      std::vector<int> tiles;
      bool loaded;

   public:
      TMJDataLoader(std::string filename="filename-not-set.tmj");
      ~TMJDataLoader();

      int get_tmx_width();
      int get_tmx_height();
      int get_tmx_tilewidth();
      int get_tmx_tileheight();
      int get_tilelayer_width();
      int get_tilelayer_height();
      std::vector<int> get_tiles();
      bool get_loaded();
      bool load();
   };
}



