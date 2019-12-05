

#include <Tileo/TileIndexInfo.hpp>



namespace Tileo
{


TileIndexInfo::TileIndexInfo()
   : index_num(-1)
   , bitmap_source(nullptr)
   , sub_bitmap(nullptr)
   , u1(0)
   , v1(0)
   , u2(0)
   , v2(0)
{
}


TileIndexInfo::~TileIndexInfo()
{
}


void TileIndexInfo::set_index_num(int index_num)
{
   this->index_num = index_num;
}


void TileIndexInfo::set_bitmap_source(ALLEGRO_BITMAP* bitmap_source)
{
   this->bitmap_source = bitmap_source;
}


void TileIndexInfo::set_sub_bitmap(ALLEGRO_BITMAP* sub_bitmap)
{
   this->sub_bitmap = sub_bitmap;
}


void TileIndexInfo::set_u1(int u1)
{
   this->u1 = u1;
}


void TileIndexInfo::set_v1(int v1)
{
   this->v1 = v1;
}


void TileIndexInfo::set_u2(int u2)
{
   this->u2 = u2;
}


void TileIndexInfo::set_v2(int v2)
{
   this->v2 = v2;
}


int TileIndexInfo::get_index_num()
{
   return index_num;
}


ALLEGRO_BITMAP* TileIndexInfo::get_bitmap_source()
{
   return bitmap_source;
}


ALLEGRO_BITMAP* TileIndexInfo::get_sub_bitmap()
{
   return sub_bitmap;
}


int TileIndexInfo::get_u1()
{
   return u1;
}


int TileIndexInfo::get_v1()
{
   return v1;
}


int TileIndexInfo::get_u2()
{
   return u2;
}


int TileIndexInfo::get_v2()
{
   return v2;
}


} // namespace Tileo


