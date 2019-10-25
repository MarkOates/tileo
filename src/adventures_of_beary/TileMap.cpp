

#include <adventures_of_beary/TileMap.hpp>

#include <iostream>


void TileMap::set_tile_uv(int tile_x, int tile_y, int u1, int v1, int u2, int v2)
{
   int index_start = (tile_x * 6) + tile_y * (width*6);
   int &i = index_start;

   //ALLEGRO_VERTEX *vbuff = (ALLEGRO_VERTEX *)al_lock_vertex_buffer(vertex_buffer, index_start, 6, ALLEGRO_LOCK_WRITEONLY);
   ALLEGRO_VERTEX *vbuff = (ALLEGRO_VERTEX *)al_lock_vertex_buffer(vertex_buffer, index_start, 6, ALLEGRO_LOCK_WRITEONLY);
   if (!vbuff) std::cout << "could not lock vertex buffer" << std::endl;

   if (use_vtx) vtx[i+0].u = u1;
   if (use_vtx) vtx[i+0].v = v1;
   vbuff[0].u = u1;
   vbuff[0].v = v1;

   if (use_vtx) vtx[i+1].u = u1;
   if (use_vtx) vtx[i+1].v = v2;
   vbuff[1].u = u1;
   vbuff[1].v = v2;

   if (use_vtx) vtx[i+2].u = u2;
   if (use_vtx) vtx[i+2].v = v2;
   vbuff[2].u = u2;
   vbuff[2].v = v2;

   if (use_vtx) vtx[i+3].u = u2;
   if (use_vtx) vtx[i+3].v = v2;
   vbuff[3].u = u2;
   vbuff[3].v = v2;

   if (use_vtx) vtx[i+4].u = u2;
   if (use_vtx) vtx[i+4].v = v1;
   vbuff[4].u = u2;
   vbuff[4].v = v1;

   if (use_vtx) vtx[i+5].u = u1;
   if (use_vtx) vtx[i+5].v = v1;
   vbuff[5].u = u1;
   vbuff[5].v = v1;

   al_unlock_vertex_buffer(vertex_buffer);
}


TileMap::TileMap()
   : vertex_buffer(NULL)
   , vtx()
   , width(0)
   , height(0)
   , tiles()
   , use_vtx(false) // setting this to false will skip the creation of the ALLEGRO_VERTEX mesh
{}


TileMap::~TileMap()
{
}


int TileMap::get_width()
{
   return width;
}


int TileMap::get_height()
{
   return height;
}


int TileMap::infer_num_tiles()
{
   return width * height;
}


int TileMap::get_tile(int tile_x, int tile_y)
{
   if (tile_x < 0 || (tile_x >= width)) return -1;
   if (tile_y < 0 || (tile_y >= height)) return -1;

   return tiles[tile_x % width + tile_y * width];
}


bool TileMap::set_tile(TileAtlas &tile_atlas, int tile_x, int tile_y, int tile_index)
   // if the tile is set to a negative number, then the tiles[tile_index] will be set to that number, but
   // the image will be the bitmap at index 0
{
   if (tile_x < 0 || (tile_x >= width)) return false;
   if (tile_y < 0 || (tile_y >= height)) return false;

   tiles[tile_x + tile_y * width] = tile_index;

   set_tile_to_mesh(tile_atlas, tile_x, tile_y, tile_index);

   return true;
}


bool TileMap::set_tile_to_mesh(TileAtlas &tile_atlas, int tile_x, int tile_y, int tile_index)
{
   // if the tile index does not exist in the tile_atlas, break out
   if (tile_index >= (int)tile_atlas.get_tile_index().size()) return false;

   // if the tile_index is a negative number, use the number "0" instead
   // I'm not sure how/why this is the preferred approach.  I think negative numbers
   // should be allowed, any number should be allowed.  So this should be revisited
   if (tile_index < 0) tile_index = 0;

   // transfer the uv coordinates of the from the tile atlas bitmap to the mesh
   // {
      int u1, v1, u2, v2;
      tile_atlas.get_tile_uv(tile_index, &u1, &v1, &u2, &v2);
      set_tile_uv(tile_x, tile_y, u1, v1, u2, v2);
   // }

   return true;
}


//bool TileMap::set_contiguous_tile_num(TileAtlas &tile_atlas, int contiguous_tile_num, int tile_index)
//{
   //int tile_x = contiguous_tile_num % width;
   //int tile_y = contiguous_tile_num / width;
   //return set_tile(tile_atlas, tile_x, tile_y, tile_index);
//}


void TileMap::resize(int w, int h, int tile_w, int tile_h)
{
   // set the width and height of our map
   width = w;
   height = h;

   // resize and clear the tiles
   tiles.assign(width * height, 0);

   // resize the vtx vector
   vtx.clear();
   if (use_vtx) vtx.resize(width*height*6);

   // create a vertex_buffer
   if (vertex_buffer) al_destroy_vertex_buffer(vertex_buffer);
   vertex_buffer = al_create_vertex_buffer(NULL, NULL, width*height*6, ALLEGRO_PRIM_BUFFER_STATIC);
   if (!vertex_buffer) std::cout << "There was an error creating the vertex buffer" << std::endl;

   // lock the buffer before writing to it
   ALLEGRO_VERTEX *vbuff_begin = (ALLEGRO_VERTEX *)al_lock_vertex_buffer(vertex_buffer, 0, al_get_vertex_buffer_size(vertex_buffer), ALLEGRO_LOCK_WRITEONLY);
   if (!vbuff_begin) std::cout << "There was an error locking the vertex buffer" << std::endl;

   // place the vertexes in the mesh
   ALLEGRO_VERTEX *vbuff = vbuff_begin;
   int v = 0;
   int num_vertexes = width*height*6;
   for (; v<num_vertexes; v+=6, vbuff+=6)
   {
      long tile_num = v / 6;

      int x1 = (tile_num % width);
      int y1 = (tile_num / width);
      int x2 = x1 + 1;
      int y2 = y1 + 1;

      if (use_vtx) vtx[v+0].x = x1;
      if (use_vtx) vtx[v+0].y = y1;
      vbuff[0].x = x1;
      vbuff[0].y = y1;

      if (use_vtx) vtx[v+1].x = x1;
      if (use_vtx) vtx[v+1].y = y2;
      vbuff[1].x = x1;
      vbuff[1].y = y2;

      if (use_vtx) vtx[v+2].x = x2;
      if (use_vtx) vtx[v+2].y = y2;
      vbuff[2].x = x2;
      vbuff[2].y = y2;

      if (use_vtx) vtx[v+3].x = x2;
      if (use_vtx) vtx[v+3].y = y2;
      vbuff[3].x = x2;
      vbuff[3].y = y2;

      if (use_vtx) vtx[v+4].x = x2;
      if (use_vtx) vtx[v+4].y = y1;
      vbuff[4].x = x2;
      vbuff[4].y = y1;

      if (use_vtx) vtx[v+5].x = x1;
      if (use_vtx) vtx[v+5].y = y1;
      vbuff[5].x = x1;
      vbuff[5].y = y1;
   }

   // "scale" the vertexes to the tile_w and tile_h
   // and set other default values
   vbuff = vbuff_begin;
   v = 0;
   for (; v<num_vertexes; v++, vbuff++)
   {
      if (use_vtx) vtx[v].x *= tile_w;
      if (use_vtx) vtx[v].y *= tile_h;
      if (use_vtx) vtx[v].z = 0;
      if (use_vtx) vtx[v].color = al_map_rgba_f(1, 1, 1, 1);//color::mix(color::white, random_color(), 0.5);//color::transparent;
      vbuff[0].x *= tile_w;
      vbuff[0].y *= tile_h;
      vbuff[0].z = 0;
      vbuff[0].color = al_map_rgba_f(1, 1, 1, 1);//color::mix(color::white, random_color(), 0.5);
   }

   // unlock our buffer
   al_unlock_vertex_buffer(vertex_buffer);
}


void TileMap::draw(ALLEGRO_BITMAP *tile_atlas_bitmap, int camera_x, int camera_y)
{
   ALLEGRO_TRANSFORM prev, transform;
   al_copy_transform(&prev, al_get_current_transform());
   al_identity_transform(&transform);
   al_translate_transform(&transform, -camera_x, -camera_y);
   al_use_transform(&transform);

   //al_draw_prim(&vtx[0], NULL, tile_atlas->bitmap, 0, vtx.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   al_draw_vertex_buffer(vertex_buffer, tile_atlas_bitmap, 0, al_get_vertex_buffer_size(vertex_buffer), ALLEGRO_PRIM_TRIANGLE_LIST);

   al_use_transform(&prev);
}


