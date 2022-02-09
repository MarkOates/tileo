

#include <Tileo/Atlas.hpp>

#include <sstream>
#include <iostream>


namespace Tileo
{
// this vertex structure is something that could be used in the future when adding
// lighting features

/*
   typedef struct
   {
   float x, y, z;
   float texture_u, texture_v;
   float normal_u, normal_v;
   float height_u, height_v;
   float height;
   ALLEGRO_COLOR color;
   } ALLEGRO_TILE_VERTEX;




   ALLEGRO_VERTEX_ELEMENT elems[] = {
   {ALLEGRO_PRIM_POSITION, ALLEGRO_PRIM_FLOAT_3, offsetof(ALLEGRO_VERTEX_WITH_NORMAL, x)},
   {ALLEGRO_PRIM_TEX_COORD, ALLEGRO_PRIM_FLOAT_2, offsetof(ALLEGRO_VERTEX_WITH_NORMAL, texture_u)},
   {ALLEGRO_PRIM_USER_ATTR, ALLEGRO_PRIM_FLOAT_2, offsetof(ALLEGRO_VERTEX_WITH_NORMAL, normal_u)},
   {ALLEGRO_PRIM_USER_ATTR, ALLEGRO_PRIM_FLOAT_2, offsetof(ALLEGRO_VERTEX_WITH_NORMAL, height_u)},
   {ALLEGRO_PRIM_COLOR_ATTR, 0, offsetof(ALLEGRO_VERTEX_WITH_NORMAL, color)},
   {ALLEGRO_PRIM_USER_ATTR, ALLEGRO_PRIM_FLOAT_3, offsetof(ALLEGRO_VERTEX_WITH_NORMAL, nx)},
   {0, 0, 0}
   };

   ALLEGRO_VERTEX_DECLARATION *vertex_declaration = al_create_vertex_decl(elems, sizeof(ALLEGRO_VERTEX_WITH_NORMAL));
   */


Atlas::Atlas()
   : bitmap(nullptr)
   , tile_index()
{
}


Atlas::~Atlas()
{
   std::cout << "[~Atlas()] WARNING: tile atlas may contain a bitmap (and potentially depenedencies "
             << "reliant on it) that has not been properly freed. This destruction mechanism has not yet "
             << "been properly implemented."
             << std::endl;
}


ALLEGRO_BITMAP *Atlas::get_bitmap()
{
   return bitmap;
}


int Atlas::get_tile_index_size()
{
   return tile_index.size();
}


void Atlas::clear()
{
   std::cout << "[Atlas::clear()] WARNING: this feature is destroying a bitmap that potentially may "
             << "have depenedencies (as sub-bitmaps). This destruction mechanism has not yet been properly "
             << "implemented."
             << std::endl;

   for (unsigned i=0; i<tile_index.size(); i++) al_destroy_bitmap(tile_index[i].get_sub_bitmap());
   if (bitmap) al_destroy_bitmap(bitmap);
   bitmap = NULL;
   tile_index.clear();
}


// load will *copy* the bitmap that you pass into it.  You probably would want to al_destroy_bitmap after loading;
void Atlas::duplicate_bitmap_and_load(ALLEGRO_BITMAP *tileset, int tile_width, int tile_height, int spacing)
{
   if (!tileset)
   {
      std::cout << "[Atlas::load()] ERROR: the ALLEGRO_BITMAP provided is NULL" << std::endl;
   }

   // clear the existing contents of this tile atlas (if any)
   clear();

   bitmap = al_clone_bitmap(tileset);

   int tile_step_x = tile_width + spacing;
   int tile_step_y = tile_height + spacing;

   int num_columns = al_get_bitmap_width(bitmap) / tile_step_x;
   int num_rows = al_get_bitmap_height(bitmap) / tile_step_y;
   tile_index.resize(num_columns * num_rows);

   for (unsigned index_num=0; index_num<tile_index.size(); index_num++)
   {
      int x1 = (index_num % num_columns) * tile_step_x + spacing;
      int y1 = (index_num / num_columns) * tile_step_y + spacing;
      int x2 = x1 + tile_width;
      int y2 = y1 + tile_height;

      tile_index[index_num].set_index_num(index_num);
      tile_index[index_num].set_bitmap_source(nullptr);
      tile_index[index_num].set_sub_bitmap(al_create_sub_bitmap(bitmap, x1, y1, x2-x1, y2-y1));
      tile_index[index_num].set_u1(x1);
      tile_index[index_num].set_v1(y1);
      tile_index[index_num].set_u2(x2);
      tile_index[index_num].set_v2(y2);
   }
}


void Atlas::draw_tile_to_atlas(ALLEGRO_BITMAP *tile, int tile_num, ALLEGRO_COLOR color)
{
   // ok, this is a serious bit of a hack.  It will only work when the tiles are spaced with spaces of 1 px.
   if (!tile) return;

   std::cout << " - Drawing to tile " << tile_num << " - " << std::endl;

   if (!bitmap)
   {
      std::cout << "[Atlas::draw_to_tile_atlas()] ERROR: the ALLEGRO_BITMAP provided is NULL" << std::endl;
      return;
   }

   for (int index_num=0; index_num<(int)tile_index.size(); index_num++)
   {
      if (index_num != tile_num) continue;

      ALLEGRO_STATE previous_state;
      al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP);
      al_set_target_bitmap(tile_index[index_num].get_sub_bitmap());

      al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));
      al_draw_tinted_bitmap(tile, color, 0, 0, 0);

      al_restore_state(&previous_state);
      /*
         tile_index[index_num].index_num = index_num;
         tile_index[index_num].bitmap_source = NULL;
         tile_index[index_num].sub_bitmap = al_create_sub_bitmap(bitmap, x1, y1, x2-x1, y2-y1);
         tile_index[index_num].u1 = x1;
         tile_index[index_num].v1 = y1;
         tile_index[index_num].u2 = x2;
         tile_index[index_num].v2 = y2;
         */
   }
}


bool Atlas::get_tile_uv(int index_num, int *u1, int *v1, int *u2, int *v2)
{
   if (index_num < 0 || index_num >= (int)tile_index.size()) return false;

   *u1 = tile_index[index_num].get_u1();
   *v1 = tile_index[index_num].get_v1();
   *u2 = tile_index[index_num].get_u2();
   *v2 = tile_index[index_num].get_v2();

   return true;
}


ALLEGRO_BITMAP* Atlas::get_bitmap(int index_num)
{
   if (index_num < 0 || index_num >= (int)tile_index.size())
   {
      std::stringstream error_message;
      error_message << "Can not Atlas::get_bitmap on index_num " << index_num << ".";
      throw std::runtime_error(error_message.str());
   }

   return tile_index[index_num].get_sub_bitmap();
}


} // namespace Tileo


