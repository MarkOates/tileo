

#include <Tileo/TMJDataLoader.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
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
   , collision_layer_num_columns(0)
   , collision_layer_num_rows(0)
   , collision_layer_tile_data({})
   , loaded(false)
{
}


TMJDataLoader::~TMJDataLoader()
{
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

int TMJDataLoader::get_layer_num_columns()
{
   if (!(loaded))
      {
         std::stringstream error_message;
         error_message << "TMJDataLoader" << "::" << "get_layer_num_columns" << ": error: " << "guard \"loaded\" not met";
         throw std::runtime_error(error_message.str());
      }
   return layer_num_columns;
}

int TMJDataLoader::get_layer_num_rows()
{
   if (!(loaded))
      {
         std::stringstream error_message;
         error_message << "TMJDataLoader" << "::" << "get_layer_num_rows" << ": error: " << "guard \"loaded\" not met";
         throw std::runtime_error(error_message.str());
      }
   return layer_num_rows;
}

std::vector<int> TMJDataLoader::get_layer_tile_data()
{
   if (!(loaded))
      {
         std::stringstream error_message;
         error_message << "TMJDataLoader" << "::" << "get_layer_tile_data" << ": error: " << "guard \"loaded\" not met";
         throw std::runtime_error(error_message.str());
      }
   return layer_tile_data;
}

int TMJDataLoader::get_collision_layer_num_columns()
{
   if (!(loaded))
      {
         std::stringstream error_message;
         error_message << "TMJDataLoader" << "::" << "get_collision_layer_num_columns" << ": error: " << "guard \"loaded\" not met";
         throw std::runtime_error(error_message.str());
      }
   return collision_layer_num_columns;
}

int TMJDataLoader::get_collision_layer_num_rows()
{
   if (!(loaded))
      {
         std::stringstream error_message;
         error_message << "TMJDataLoader" << "::" << "get_collision_layer_num_rows" << ": error: " << "guard \"loaded\" not met";
         throw std::runtime_error(error_message.str());
      }
   return collision_layer_num_rows;
}

std::vector<int> TMJDataLoader::get_collision_layer_tile_data()
{
   if (!(loaded))
      {
         std::stringstream error_message;
         error_message << "TMJDataLoader" << "::" << "get_collision_layer_tile_data" << ": error: " << "guard \"loaded\" not met";
         throw std::runtime_error(error_message.str());
      }
   return collision_layer_tile_data;
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
      if (layer.value()["type"] == "tilelayer" && layer.value()["name"] != "collision")
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



   // get first j["layers"] that is a ["type"] == "tilelayer"
   bool collision_tilelayer_type_found = false;
   nlohmann::json collision_tilelayer;
   for (auto &layer : j["layers"].items())
   {
      if (layer.value()["type"] == "tilelayer" && layer.value()["name"] == "collision")
      {
         collision_tilelayer = layer.value();
         collision_tilelayer_type_found = true;
         break;
      }
   }
   if (!collision_tilelayer_type_found)
   {
      std::stringstream error_message;
      error_message << "TMJMeshLoader: error: collision_tilelayer type not found. Expecting a layer of type "
                    << "\"tilelayer\" that also has a \"name\" property of \"collision\". Note that only "
                    << "the following layers present: \"" << std::endl;
      int layer_num = 0;
      for (auto &layer : j["layers"].items())
      {
         layer_num++;
         error_message << "  - layer " << layer_num << ":" << std::endl;
         error_message << "    - type: \"" << layer.value()["type"] << "\"" << std::endl;
         error_message << "    - name: \"" << layer.value()["name"] << "\"" << std::endl;
      }
      throw std::runtime_error(error_message.str());
   }

   collision_layer_num_columns = collision_tilelayer["width"];
   collision_layer_num_rows = collision_tilelayer["height"];
   collision_layer_tile_data = collision_tilelayer["data"].get<std::vector<int>>();


   loaded = true;

   i.close();

   return true;
}
} // namespace Tileo


