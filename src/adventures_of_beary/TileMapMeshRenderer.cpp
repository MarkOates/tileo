

#include <adventures_of_beary/TileMapMeshRenderer.hpp>


TileMapMeshRenderer::TileMapMeshRenderer(ALLEGRO_BITMAP *tile_atlas_bitmap)
   : vertex_buffer(nullptr)
   , vtx()
   , tile_atlas_bitmap(tile_atlas_bitmap)
   , width(0)
   , height(0)
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


TileMapMeshRenderer::~TileMapMeshRenderer()
{
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


