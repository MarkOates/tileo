

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


bool TileMap::set_tile(TileAtlas &tile_atlas, TileMapMeshRenderer &mesh_renderer, int tile_x, int tile_y, int tile_index)
   // if the tile is set to a negative number, then the tiles[tile_index] will be set to that number, but
   // the image will be the bitmap at index 0
{
   if (tile_x < 0 || (tile_x >= width)) return false;
   if (tile_y < 0 || (tile_y >= height)) return false;

   tiles[tile_x + tile_y * width] = tile_index;

   mesh_renderer.set_tile_to_mesh(tile_atlas, tile_x, tile_y, tile_index);

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


void TileMap::resize(TileMapMeshRenderer &mesh_renderer, int w, int h, int tile_w, int tile_h)
{
   // set the width and height of our map
   width = w;
   height = h;

   // resize and clear the tiles
   tiles.assign(width * height, 0);

   mesh_renderer.resize_mesh(w, h, tile_w, tile_h);
}


