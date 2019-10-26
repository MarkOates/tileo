

#include <adventures_of_beary/TileAtlasBuilder.hpp>


TileAtlasBuilder::TileAtlasBuilder(int tile_w, int tile_h, std::vector<TileIndexInfo> tile_index)
   : tile_w(tile_w)
   , tile_h(tile_h)
   , tile_index(tile_index)
{
}


TileAtlasBuilder::~TileAtlasBuilder()
{
}


ALLEGRO_BITMAP *TileAtlasBuilder::build()
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


