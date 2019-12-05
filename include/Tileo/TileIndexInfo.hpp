#pragma once


#include <allegro5/allegro.h>


namespace Tileo
{
   class TileIndexInfo
   {
   private:
      int index_num;
      ALLEGRO_BITMAP* bitmap_source;
      ALLEGRO_BITMAP* sub_bitmap;
      int u1;
      int v1;
      int u2;
      int v2;

   public:
      TileIndexInfo(int index_num=-1, ALLEGRO_BITMAP* bitmap_source=nullptr, ALLEGRO_BITMAP* sub_bitmap=nullptr, int u1=0, int v1=0, int u2=0, int v2=0);
      ~TileIndexInfo();

      void set_index_num(int index_num);
      void set_bitmap_source(ALLEGRO_BITMAP* bitmap_source);
      void set_sub_bitmap(ALLEGRO_BITMAP* sub_bitmap);
      void set_u1(int u1);
      void set_v1(int v1);
      void set_u2(int u2);
      void set_v2(int v2);

      int get_index_num();
      ALLEGRO_BITMAP* get_bitmap_source();
      ALLEGRO_BITMAP* get_sub_bitmap();
      int get_u1();
      int get_v1();
      int get_u2();
      int get_v2();
   };
}



