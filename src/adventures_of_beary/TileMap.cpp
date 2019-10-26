

#include <adventures_of_beary/TileMap.hpp>

#include <iostream>


TileMap::TileMap()
   : width(0)
   , height(0)
   , tiles()
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


std::pair<int, int> TileMap::get_coordinates_from_contiguous_number(int contiguous_tile_num)
{
   int tile_x = contiguous_tile_num % width;
   int tile_y = contiguous_tile_num / width;

   return std::pair<int, int>(tile_x, tile_y);
}


void TileMap::resize(TileMapMeshRenderer &mesh_renderer, int w, int h, int tile_w, int tile_h)
{
   // set the width and height of our map
   width = w;
   height = h;

   // resize and clear the tiles
   tiles.assign(width * height, 0);

   mesh_renderer.resize_mesh(w, h, tile_w, tile_h);
}


