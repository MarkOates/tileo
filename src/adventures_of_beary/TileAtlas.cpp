

#include <adventures_of_beary/TileAtlas.hpp>

#include <iostream>


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


TileAtlas::TileAtlas()
   : bitmap(nullptr)
   , tile_index()
{
}


TileAtlas::~TileAtlas()
{
}


int TileAtlas::get_tile_index_size()
{
   return tile_index.size();
}


std::vector<TileIndexInfo> &TileAtlas::get_tile_index()
{
   return tile_index;
}


ALLEGRO_BITMAP *TileAtlas::build_tile_atlas(int tile_w, int tile_h, std::vector<TileIndexInfo> &tile_index)
{
   //al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_MIPMAP);

   ALLEGRO_STATE prev;
   al_store_state(&prev, ALLEGRO_STATE_TARGET_BITMAP);
   ALLEGRO_BITMAP *target = al_create_bitmap(1024, 1024);
   al_set_target_bitmap(target);

   al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));


   int step_x = tile_w + 2;
   int step_y = tile_h + 2;

   int num_rows = al_get_bitmap_height(target) / step_x;
   int num_cols = al_get_bitmap_width(target) / step_y;


   // step 1:
   // draw each tile onto the new tile_atlas bitmap, each with an extra padding of 1px

   for (int y=0; y<num_rows; y++)
      for (int x=0; x<num_cols; x++)
      {
         int index_num = x + y*num_cols;
         if (index_num >= (int)tile_index.size()) goto tile_drawing_finished;

         int draw_x = x*step_x + 1;
         int draw_y = y*step_y + 1;

         al_draw_bitmap(tile_index[index_num].sub_bitmap, draw_x, draw_y, 0);
      }

   tile_drawing_finished:


   // step 2:
   // "extrude" the pixels on the edges of each tile

   for (int y=0; y<num_rows; y++)
      for (int x=0; x<num_cols; x++)
      {
         int index_num = x + y*num_cols;
         if (index_num >= (int)tile_index.size()) goto edge_extruding_finished;

         int draw_x = x*step_x + 1;
         int draw_y = y*step_y + 1;


         // draw the top row of pixels
         al_set_clipping_rectangle(draw_x, draw_y-1, tile_w, 1);
         al_draw_bitmap(tile_index[index_num].sub_bitmap, draw_x, draw_y-1, 0);

         // draw the bottom row of pixels
         al_set_clipping_rectangle(draw_x, draw_y+tile_h, tile_w, 1);
         al_draw_bitmap(tile_index[index_num].sub_bitmap, draw_x, draw_y+1, 0);

         // draw the left row of pixels
         al_set_clipping_rectangle(draw_x-1, draw_y, 1, tile_h);
         al_draw_bitmap(tile_index[index_num].sub_bitmap, draw_x-1, draw_y, 0);

         // draw the right row of pixels
         al_set_clipping_rectangle(draw_x+tile_w, draw_y, 1, tile_h);
         al_draw_bitmap(tile_index[index_num].sub_bitmap, draw_x+1, draw_y, 0);


         // draw just the top-left pixel
         al_set_clipping_rectangle(draw_x-1, draw_y-1, 1, 1);
         al_draw_bitmap(tile_index[index_num].sub_bitmap, draw_x-1, draw_y-1, 0);

         // draw just the bottom-left pixel
         al_set_clipping_rectangle(draw_x-1, draw_y+tile_h, 1, 1);
         al_draw_bitmap(tile_index[index_num].sub_bitmap, draw_x-1, draw_y+1, 0);

         // draw just the top-right pixel
         al_set_clipping_rectangle(draw_x+tile_w, draw_y-1, 1, 1);
         al_draw_bitmap(tile_index[index_num].sub_bitmap, draw_x+1, draw_y-1, 0);

         // draw just the top-right pixel
         al_set_clipping_rectangle(draw_x+tile_w, draw_y+tile_h, 1, 1);
         al_draw_bitmap(tile_index[index_num].sub_bitmap, draw_x+1, draw_y+1, 0);
      }

   edge_extruding_finished:

   al_set_clipping_rectangle(0, 0, al_get_bitmap_width(target), al_get_bitmap_height(target));


   //
   // wrap it all up

   al_restore_state(&prev);


   // 
   // to solve an odd bug, the bitmap will be cloned so that OPENGL will correctly create the mipmaps
   ALLEGRO_BITMAP *cloned = al_clone_bitmap(target);
   al_destroy_bitmap(target);
   target = cloned;


   return target;
}


void TileAtlas::clear()
{
   for (unsigned i=0; i<tile_index.size(); i++) al_destroy_bitmap(tile_index[i].sub_bitmap);
   if (bitmap) al_destroy_bitmap(bitmap);
   bitmap = NULL;
   tile_index.clear();
}


// load will *copy* the bitmap that you pass into it.  You probably would want to al_destroy_bitmap after loading; 
void TileAtlas::load(ALLEGRO_BITMAP *tileset, int tile_width, int tile_height, int spacing)
{
   if (!tileset)
   {
      std::cout << "[TileAtlas::load()] ERROR: the ALLEGRO_BITMAP provided is NULL" << std::endl;
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

      tile_index[index_num].index_num = index_num;
      tile_index[index_num].bitmap_source = NULL;
      tile_index[index_num].sub_bitmap = al_create_sub_bitmap(bitmap, x1, y1, x2-x1, y2-y1);
      tile_index[index_num].u1 = x1;
      tile_index[index_num].v1 = y1;
      tile_index[index_num].u2 = x2;
      tile_index[index_num].v2 = y2;
   }
}


void TileAtlas::draw_tile_to_atlas(ALLEGRO_BITMAP *tile, int tile_num, ALLEGRO_COLOR color)
{
   // ok, this is a serious bit of a hack.  It will only work when the tiles are spaced with spaces of 1 px.
   if (!tile) return;

   std::cout << " - Drawing to tile " << tile_num << " - " << std::endl;

   if (!bitmap)
   {
      std::cout << "[TileAtlas::draw_to_tile_atlas()] ERROR: the ALLEGRO_BITMAP provided is NULL" << std::endl;
      return;
   }

   for (int index_num=0; index_num<(int)tile_index.size(); index_num++)
   {
      if (index_num != tile_num) continue;

      ALLEGRO_STATE previous_state;
      al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP);
      al_set_target_bitmap(tile_index[index_num].sub_bitmap);

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


bool TileAtlas::get_tile_uv(int index_num, int *u1, int *v1, int *u2, int *v2)
{
   if (index_num < 0 || index_num >= (int)tile_index.size()) return false;

   *u1 = tile_index[index_num].u1;
   *v1 = tile_index[index_num].v1;
   *u2 = tile_index[index_num].u2;
   *v2 = tile_index[index_num].v2;

   return true;
}


