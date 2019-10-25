

#include <adventures_of_beary/TileMapMeshRenderer.hpp>

#include <iostream> // for set_tile_uv


void TileMapMeshRenderer::set_tile_uv(int tile_x, int tile_y, int u1, int v1, int u2, int v2)
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


TileMapMeshRenderer::TileMapMeshRenderer(ALLEGRO_BITMAP *tile_atlas_bitmap)
   : vertex_buffer(nullptr)
   , vtx()
   , tile_atlas_bitmap(tile_atlas_bitmap)
   , width(0)
   , height(0)
   , use_vtx(false)
{
}


TileMapMeshRenderer::~TileMapMeshRenderer()
{
}


int TileMapMeshRenderer::get_width()
{
   return width;
}


int TileMapMeshRenderer::get_height()
{
   return height;
}


int TileMapMeshRenderer::infer_num_tiles()
{
   return width * height;
}


bool TileMapMeshRenderer::set_tile_to_mesh(TileAtlas &tile_atlas, int tile_x, int tile_y, int tile_index)
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


void TileMapMeshRenderer::render(int camera_x, int camera_y)
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


