

#include <Tileo/Mesh.hpp>

#include <iostream> // for set_tile_uv


namespace Tileo
{

void Mesh::set_tile_uv(int tile_x, int tile_y, int u1, int v1, int u2, int v2)
{
   int id_start = (tile_x * 6) + tile_y * (width*6);
   int &i = id_start;

   ALLEGRO_VERTEX *vbuff =
      (ALLEGRO_VERTEX *)al_lock_vertex_buffer(vertex_buffer, id_start, 6, ALLEGRO_LOCK_WRITEONLY);
   if (!vbuff) std::cout << "could not lock vertex buffer" << std::endl;

   if (use_primitive) vertexes[i+0].u = u1;
   if (use_primitive) vertexes[i+0].v = v1;
   vbuff[0].u = u1;
   vbuff[0].v = v1;

   if (use_primitive) vertexes[i+1].u = u1;
   if (use_primitive) vertexes[i+1].v = v2;
   vbuff[1].u = u1;
   vbuff[1].v = v2;

   if (use_primitive) vertexes[i+2].u = u2;
   if (use_primitive) vertexes[i+2].v = v2;
   vbuff[2].u = u2;
   vbuff[2].v = v2;

   if (use_primitive) vertexes[i+3].u = u2;
   if (use_primitive) vertexes[i+3].v = v2;
   vbuff[3].u = u2;
   vbuff[3].v = v2;

   if (use_primitive) vertexes[i+4].u = u2;
   if (use_primitive) vertexes[i+4].v = v1;
   vbuff[4].u = u2;
   vbuff[4].v = v1;

   if (use_primitive) vertexes[i+5].u = u1;
   if (use_primitive) vertexes[i+5].v = v1;
   vbuff[5].u = u1;
   vbuff[5].v = v1;

   al_unlock_vertex_buffer(vertex_buffer);
}


Mesh::Mesh(Tileo::Atlas *atlas) //ALLEGRO_BITMAP *atlas_bitmap)
   : atlas(atlas)
   , vertex_buffer(nullptr)
   , vertexes()
   //, atlas_bitmap(atlas_bitmap)
   , width(0)
   , height(0)
   , use_primitive(false)
{
}


Mesh::~Mesh()
{
}


void Mesh::initialize(int w, int h, int tile_w, int tile_h)
{
   if (initialized)
   {
      throw std::runtime_error("[Tileo::Mesh] error: initialized must be false");
      //return false
   }

   // resize the vertexes vector
   vertexes.clear();
   if (use_primitive) vertexes.resize(width*height*6);

   // create a vertex_buffer
   if (vertex_buffer) al_destroy_vertex_buffer(vertex_buffer);
   vertex_buffer = al_create_vertex_buffer(NULL, NULL, width*height*6, ALLEGRO_PRIM_BUFFER_STATIC);
   if (!vertex_buffer) std::cout << "There was an error creating the vertex buffer" << std::endl;

   // lock the buffer before writing to it
   int vertex_buffer_size = al_get_vertex_buffer_size(vertex_buffer);
   ALLEGRO_VERTEX *vbuff_begin =
      (ALLEGRO_VERTEX *)al_lock_vertex_buffer(vertex_buffer, 0, vertex_buffer_size, ALLEGRO_LOCK_WRITEONLY);
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

      if (use_primitive) vertexes[v+0].x = x1;
      if (use_primitive) vertexes[v+0].y = y1;
      vbuff[0].x = x1;
      vbuff[0].y = y1;

      if (use_primitive) vertexes[v+1].x = x1;
      if (use_primitive) vertexes[v+1].y = y2;
      vbuff[1].x = x1;
      vbuff[1].y = y2;

      if (use_primitive) vertexes[v+2].x = x2;
      if (use_primitive) vertexes[v+2].y = y2;
      vbuff[2].x = x2;
      vbuff[2].y = y2;

      if (use_primitive) vertexes[v+3].x = x2;
      if (use_primitive) vertexes[v+3].y = y2;
      vbuff[3].x = x2;
      vbuff[3].y = y2;

      if (use_primitive) vertexes[v+4].x = x2;
      if (use_primitive) vertexes[v+4].y = y1;
      vbuff[4].x = x2;
      vbuff[4].y = y1;

      if (use_primitive) vertexes[v+5].x = x1;
      if (use_primitive) vertexes[v+5].y = y1;
      vbuff[5].x = x1;
      vbuff[5].y = y1;
   }

   // "scale" the vertexes to the tile_w and tile_h
   // and set other default values
   vbuff = vbuff_begin;
   v = 0;
   for (; v<num_vertexes; v++, vbuff++)
   {
      if (use_primitive) vertexes[v].x *= tile_w;
      if (use_primitive) vertexes[v].y *= tile_h;
      if (use_primitive) vertexes[v].z = 0;
      if (use_primitive) vertexes[v].color = al_map_rgba_f(1, 1, 1, 1);
      vbuff[0].x *= tile_w;
      vbuff[0].y *= tile_h;
      vbuff[0].z = 0;
      vbuff[0].color = al_map_rgba_f(1, 1, 1, 1);//color::mix(color::white, random_color(), 0.5);
   }

   // unlock our buffer
   al_unlock_vertex_buffer(vertex_buffer);

   // set as initialized
   initialized = true;
}


int Mesh::get_width()
{
   return width;
}


int Mesh::get_height()
{
   return height;
}


int Mesh::infer_num_tiles()
{
   return width * height;
}


bool Mesh::set_tile(int tile_x, int tile_y, int tile_id)
{
   if (!atlas) throw std::runtime_error("[Tileo::Mesh] error: atlas must not be nullptr");
   // if the tile index does not exist in the atlas, break out
   if (tile_id >= (int)atlas->get_tile_index_size()) return false;

   // if the tile_id is a negative number, use the number "0" instead
   // I'm not sure how/why this is the preferred approach.  I think negative numbers
   // should be allowed, any number should be allowed.  So this should be revisited
   if (tile_id < 0) tile_id = 0;

   // transfer the uv coordinates of the from the tile atlas bitmap to the mesh
   // {
      int u1, v1, u2, v2;
      atlas->get_tile_uv(tile_id, &u1, &v1, &u2, &v2);
      set_tile_uv(tile_x, tile_y, u1, v1, u2, v2);
   // }

   return true;
}



 //void Mesh::set_atlas_bitmap(ALLEGRO_BITMAP *atlas_bitmap)
 //{
 //   this->atlas_bitmap = atlas_bitmap;
 //}



void Mesh::render() //int camera_x, int camera_y)
{
   if (!atlas) throw std::runtime_error("[Tileo::Mesh] error: atlas must not be nullptr");
   ALLEGRO_BITMAP *atlas_bitmap = atlas->get_bitmap();
   //ALLEGRO_TRANSFORM prev, transform;
   //al_copy_transform(&prev, al_get_current_transform());
   //al_identity_transform(&transform);
   ///al_translate_transform(&transform, -camera_x, -camera_y);
   //al_use_transform(&transform);

   //al_draw_prim(&vertexes[0], NULL, atlas->bitmap, 0, vertexes.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   al_draw_vertex_buffer(
      vertex_buffer,
      atlas_bitmap,
      0,
      al_get_vertex_buffer_size(vertex_buffer),
      ALLEGRO_PRIM_TRIANGLE_LIST);

   //al_use_transform(&prev);
}

} // Tileo


