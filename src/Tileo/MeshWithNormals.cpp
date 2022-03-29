

#include <Tileo/MeshWithNormals.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Tileo
{


MeshWithNormals::MeshWithNormals(int num_columns, int num_rows, float tile_width, float tile_height)
   : num_columns(num_columns)
   , num_rows(num_rows)
   , tile_width(tile_width)
   , tile_height(tile_height)
   , tile_ids()
   , normal_tile_ids()
   , initialized(false)
{
}


MeshWithNormals::~MeshWithNormals()
{
}


void MeshWithNormals::initialize()
{
   if (!((num_columns > 0)))
      {
         std::stringstream error_message;
         error_message << "MeshWithNormals" << "::" << "initialize" << ": error: " << "guard \"(num_columns > 0)\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!((num_rows > 0)))
      {
         std::stringstream error_message;
         error_message << "MeshWithNormals" << "::" << "initialize" << ": error: " << "guard \"(num_rows > 0)\" not met";
         throw std::runtime_error(error_message.str());
      }
   // TODO
   initialized = true;
   return;
}

void MeshWithNormals::resize(int num_columns, int num_rows)
{
   if (!((num_columns > 0)))
      {
         std::stringstream error_message;
         error_message << "MeshWithNormals" << "::" << "resize" << ": error: " << "guard \"(num_columns > 0)\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!((num_rows > 0)))
      {
         std::stringstream error_message;
         error_message << "MeshWithNormals" << "::" << "resize" << ": error: " << "guard \"(num_rows > 0)\" not met";
         throw std::runtime_error(error_message.str());
      }
   // TODO
   return;
}
} // namespace Tileo


