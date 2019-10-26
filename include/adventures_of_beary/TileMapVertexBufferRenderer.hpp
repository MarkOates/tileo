#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <adventures_of_beary/TileAtlas.hpp>
#include <vector>


class TileMapVertexBufferRenderer
{
private:
   ALLEGRO_VERTEX_BUFFER *vertex_buffer;
   std::vector<ALLEGRO_VERTEX> vertexes;
   ALLEGRO_BITMAP *tile_atlas_bitmap;
   int width;
   int height;
   bool use_primitive;

   ALLEGRO_VERTEX *locked_vertex_buffer_vertex_pos;

   void lock_vertex_buffer(int start, int length);
   void unlock_vertex_buffer();
   void set_tile_uv(int tile_x, int tile_y, int u1, int v1, int u2, int v2);

public:
   TileMapVertexBufferRenderer(ALLEGRO_BITMAP *tile_atlas_bitmap=nullptr);
   ~TileMapVertexBufferRenderer();

   int get_width();
   int get_height();
   int infer_num_tiles();

   bool set_tile(TileAtlas &tile_atlas, int tile_x, int tile_y, int tile_index);
   void resize(int w, int h, int tile_w, int tile_h);

   void render(int camera_x, int camera_y);
};


