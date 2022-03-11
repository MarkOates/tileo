

#include <Tileo/TMJMeshLoader.hpp>
#include <Tileo/TileAtlasBuilder.hpp>
#include <lib/nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>
#include <sstream>


namespace Tileo
{


TMJMeshLoader::TMJMeshLoader(AllegroFlare::BitmapBin* bitmap_bin, Tileo::Atlas* tile_atlas, std::string filename, std::string bitmap_atlas_filename)
   : bitmap_bin(bitmap_bin)
   , tile_atlas(tile_atlas)
   , filename(filename)
   , bitmap_atlas_filename(bitmap_atlas_filename)
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
   // 1
   // load and validate the json data to variables
   std::ifstream i(filename);
   nlohmann::json j;
   i >> j;

   int tmx_height = j["height"];// get height
   int tmx_width = j["width"];// get width
   int tmx_tileheight = j["tileheight"]; // get height
   int tmx_tilewidth = j["tilewidth"]; // get width

   // get first j["layers"] that is a ["type"] == "tilelayer"
   bool tilelayer_type_found = false;
   nlohmann::json tilelayer;
   for (auto &layer : j["layers"].items())
   {
      if (layer.value()["type"] == "tilelayer")
      {
         std::cout << "AAAAAAAAA" << std::endl;
         tilelayer = layer.value();
         tilelayer_type_found = true;
         break;
      }
   }
   if (!tilelayer_type_found) throw std::runtime_error("TMJMeshLoader: error: tilelayer type not found.");

   int tilelayer_width = tilelayer["width"];
   int tilelayer_height = tilelayer["height"];
   std::vector<int> tiles = tilelayer["data"].get<std::vector<int>>();

   // validate widths and heights match
   if (tilelayer_width != tmx_width)
   {
      throw std::runtime_error("TMJMeshLoader: error: tilelayer width does not match tmx_width.");
   }
   if (tilelayer_height != tmx_height)
   {
      throw std::runtime_error("TMJMeshLoader: error: tilelayer height does not match tmx_height.");
   }
   if (tmx_tileheight != 16 || tmx_tilewidth != 16)
   {
      throw std::runtime_error("TMJMeshLoader: error: tmx tileheight and tilewidth other than 16 not supported.");
   }
   if (tiles.size() != tmx_width * tmx_height)
   {
      throw std::runtime_error("TMJMeshLoader: error: num tiles (in \"data\" field) does not match width*height.");
   }

   // 2
   // create the atlas
   int tile_width = 16;
   int tile_height = 16;

   ALLEGRO_BITMAP *tile_map_bitmap = bitmap_bin->operator[](bitmap_atlas_filename);
   tile_atlas->set_bitmap_filename(bitmap_atlas_filename);

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

   // 3
   // create the mesh
   int width = tmx_width;
   int height = tmx_height;
   Tileo::Mesh* mesh = new Tileo::Mesh(tile_atlas, width, height, tile_width*4.8, tile_height*4.5);
   mesh->initialize();

   // 4
   // fill the data
   for (int y=0; y<height; y++)
   {
      for (int x=0; x<width; x++)
      {
         int tile_id = tiles[y * width + x];
         mesh->set_tile_id(x, y, tile_id-1);
      }
   }

   // 5
   // return the mesh
   return mesh;
}
} // namespace Tileo


