

#include <Tileo/TMJDataLoader.hpp>
#include <sstream>
#include <Blast/FileExistenceChecker.hpp>
#include <lib/nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>
#include <sstream>


namespace Tileo
{


TMJDataLoader::TMJDataLoader(std::string filename)
   : filename(filename)
   , num_columns(0)
   , num_rows(0)
   , tmx_tilewidth(0)
   , tmx_tileheight(0)
   , tilelayer_width(0)
   , tilelayer_height(0)
   , tiles({})
   , loaded(false)
{
}


TMJDataLoader::~TMJDataLoader()
{
}


int TMJDataLoader::get_num_columns()
{
   return num_columns;
}


int TMJDataLoader::get_num_rows()
{
   return num_rows;
}


int TMJDataLoader::get_tmx_tilewidth()
{
   return tmx_tilewidth;
}


int TMJDataLoader::get_tmx_tileheight()
{
   return tmx_tileheight;
}


int TMJDataLoader::get_tilelayer_width()
{
   return tilelayer_width;
}


int TMJDataLoader::get_tilelayer_height()
{
   return tilelayer_height;
}


std::vector<int> TMJDataLoader::get_tiles()
{
   return tiles;
}


bool TMJDataLoader::get_loaded()
{
   return loaded;
}


bool TMJDataLoader::load()
{
   if (!((!loaded)))
      {
         std::stringstream error_message;
         error_message << "TMJDataLoader" << "::" << "load" << ": error: " << "guard \"(!loaded)\" not met";
         throw std::runtime_error(error_message.str());
      }
   Blast::FileExistenceChecker file_existence_checker(filename);
   if (!file_existence_checker.exists())
   {
      std::stringstream error_message;
      error_message << "[Tileo/TMJDataLoader] load() error: the file \"" << filename << "\" does not exist.";
      throw std::runtime_error(error_message.str());
   }

   // load and validate the json data to variables
   std::ifstream i(filename);
   nlohmann::json j;
   try
   {
      i >> j;
   }
   catch (const std::exception& e)
   {
      i.close();
      std::stringstream error_message;
      error_message << "[Tileo/TMJDataLoader] load() error: the file \"" << filename << "\" appears to have"
                    << " malformed JSON. The following error was thrown by nlohmann::json: \""
                    << e.what() << "\"";
      throw std::runtime_error(error_message.str());
   }

   num_columns = j["width"]; // get width
   num_rows = j["height"]; // get height
   tmx_tilewidth = j["tilewidth"]; // get width
   tmx_tileheight = j["tileheight"]; // get height

   // get first j["layers"] that is a ["type"] == "tilelayer"
   bool tilelayer_type_found = false;
   nlohmann::json tilelayer;
   for (auto &layer : j["layers"].items())
   {
      if (layer.value()["type"] == "tilelayer")
      {
         tilelayer = layer.value();
         tilelayer_type_found = true;
         break;
      }
   }
   if (!tilelayer_type_found) throw std::runtime_error("TMJMeshLoader: error: tilelayer type not found.");

   tilelayer_width = tilelayer["width"];
   tilelayer_height = tilelayer["height"];
   tiles = tilelayer["data"].get<std::vector<int>>();

   loaded = true;

   i.close();

   return true;
}
} // namespace Tileo


