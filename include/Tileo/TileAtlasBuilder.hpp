#pragma once


#include <Tileo/TileIndexInfo.hpp>
#include <allegro5/allegro.h>
#include <vector>


class TileAtlasBuilder
{
private:
   int tile_w;
   int tile_h;
   std::vector<Tileo::TileIndexInfo> tile_index;

public:
   TileAtlasBuilder(int tile_w=0, int tile_h=0, std::vector<Tileo::TileIndexInfo> tile_index={});
   ~TileAtlasBuilder();

   ALLEGRO_BITMAP *build();
};



