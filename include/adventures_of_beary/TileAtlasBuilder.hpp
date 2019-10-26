#pragma once


#include <allegro5/allegro.h>


class TileAtlasBuilder
{
private:

public:
   TileAtlasBuilder();
   ~TileAtlasBuilder();

   ALLEGRO_BITMAP *build();
};



