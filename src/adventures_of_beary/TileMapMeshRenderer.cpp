

#include <adventures_of_beary/TileMapMeshRenderer.hpp>


TileMapMeshRenderer::TileMapMeshRenderer(ALLEGRO_BITMAP *tile_atlas_bitmap, int camera_x, int camera_y)
   : vertex_buffer(nullptr)
   , tile_atlas_bitmap(tile_atlas_bitmap)
   , camera_x(camera_x)
   , camera_y(camera_y)
{
}


TileMapMeshRenderer::~TileMapMeshRenderer()
{
}


void TileMapMeshRenderer::render()
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


