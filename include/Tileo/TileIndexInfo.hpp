#pragma once


#include <allegro5/allegro.h>


class TileIndexInfo
{
public:
   int index_num;

   ALLEGRO_BITMAP *bitmap_source;
   ALLEGRO_BITMAP *sub_bitmap;

   int u1, v1, u2, v2;

   TileIndexInfo();
};


