

#include <Tileo/TMJMeshLoader.hpp>
#include <Tileo/TileAtlasBuilder.hpp>
#include <stdexcept>
#include <sstream>


namespace Tileo
{


TMJMeshLoader::TMJMeshLoader(AllegroFlare::BitmapBin* bitmap_bin, Tileo::Atlas* tile_atlas, std::string filename)
   : bitmap_bin(bitmap_bin)
   , tile_atlas(tile_atlas)
   , filename(filename)
{
}


TMJMeshLoader::~TMJMeshLoader()
{
}


Tileo::Mesh* TMJMeshLoader::create_mesh()
{
   if (!(bitmap_bin))
      {
         std::stringstream error_message;
         error_message << "TMJMeshLoader" << "::" << "create_mesh" << ": error: " << "guard \"bitmap_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(tile_atlas))
      {
         std::stringstream error_message;
         error_message << "TMJMeshLoader" << "::" << "create_mesh" << ": error: " << "guard \"tile_atlas\" not met";
         throw std::runtime_error(error_message.str());
      }
   // get height
   // get width
   // get first j["layers"] that is a ["type"] == "tilelayer"
   //   - get ["width"]
   //   - get ["height"]
   //   - get ["data"]
   // validate widths and heights match

   // get tilewidth
   // get tileheight
   // validate tileheight and tilewidth == 16

   // create the atlas
   int tile_width = 16;
   int tile_height = 16;

   std::string bitmap_filename = "tiles_dungeon_v1.1.png";
   ALLEGRO_BITMAP *tile_map_bitmap = bitmap_bin->operator[](bitmap_filename);
   tile_atlas->set_bitmap_filename(bitmap_filename);

   bool scaled_and_extruded = true;
   if (scaled_and_extruded)
   {
      int scale = 3;
      ALLEGRO_BITMAP *scaled_extruded_tile_map_bitmap =
         TileAtlasBuilder::build_scaled_and_extruded(tile_map_bitmap, scale);
      al_save_bitmap("/Users/markoates/Desktop/whatever.png", scaled_extruded_tile_map_bitmap);
      tile_atlas->duplicate_bitmap_and_load(scaled_extruded_tile_map_bitmap, tile_width*scale, tile_height*scale, 1);
   }
   else
   {
      tile_atlas->duplicate_bitmap_and_load(tile_map_bitmap, tile_width, tile_height);
   }

   // create the mesh
   int width = 0;
   int height = 0;
   Tileo::Mesh* mesh = new Tileo::Mesh(tile_atlas, width, height, tile_width, tile_height);
   mesh->initialize();

   // return the mesh
   return mesh;
}
} // namespace Tileo


