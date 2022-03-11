

#include <Tileo/TMJDataLoader.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
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
   , tile_width(0)
   , tile_height(0)
   , layer_num_columns(0)
   , layer_num_rows(0)
   , layer_tile_data({})
   , loaded(false)
{
}


TMJDataLoader::~TMJDataLoader()
{
}


int TMJDataLoader::get_layer_num_columns()
{
   return layer_num_columns;
}


int TMJDataLoader::get_layer_num_rows()
{
   return layer_num_rows;
}


std::vector<int> TMJDataLoader::get_layer_tile_data()
{
   return layer_tile_data;
}


bool TMJDataLoader::get_loaded()
{
   return loaded;
}


int TMJDataLoader::get_num_columns()
{
   if (!(loaded))
      {
         std::stringstream error_message;
         error_message << "TMJDataLoader" << "::" << "get_num_columns" << ": error: " << "guard \"loaded\" not met";
         throw std::runtime_error(error_message.str());
      }
   return num_columns;
}

int TMJDataLoader::get_num_rows()
{
   if (!(loaded))
      {
         std::stringstream error_message;
         error_message << "TMJDataLoader" << "::" << "get_num_rows" << ": error: " << "guard \"loaded\" not met";
         throw std::runtime_error(error_message.str());
      }
   return num_rows;
}

int TMJDataLoader::get_tile_width()
{
   if (!(loaded))
      {
         std::stringstream error_message;
         error_message << "TMJDataLoader" << "::" << "get_tile_width" << ": error: " << "guard \"loaded\" not met";
         throw std::runtime_error(error_message.str());
      }
   return tile_width;
}

int TMJDataLoader::get_tile_height()
{
   if (!(loaded))
      {
         std::stringstream error_message;
         error_message << "TMJDataLoader" << "::" << "get_tile_height" << ": error: " << "guard \"loaded\" not met";
         throw std::runtime_error(error_message.str());
      }
   return tile_height;
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
   tile_width = j["tilewidth"]; // get width
   tile_height = j["tileheight"]; // get height

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

   layer_num_columns = tilelayer["width"];
   layer_num_rows = tilelayer["height"];
   layer_tile_data = tilelayer["data"].get<std::vector<int>>();

   loaded = true;

   i.close();

   return true;
}
} // namespace Tileo


