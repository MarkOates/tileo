

#include <Tileo/MeshWithNormals.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Tileo
{


MeshWithNormals::MeshWithNormals(int num_columns, int num_rows, float tile_width, float tile_height)
   : tileo_tile_vertex_allegro_vertex_declaration()
   , num_columns(num_columns)
   , num_rows(num_rows)
   , tile_width(tile_width)
   , tile_height(tile_height)
   , tile_ids()
   , normal_tile_ids()
   , vertexes()
   , initialized(false)
   , destroyed(false)
{
}


MeshWithNormals::~MeshWithNormals()
{
}


void MeshWithNormals::initialize()
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "MeshWithNormals" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!((num_columns >= 0)))
      {
         std::stringstream error_message;
         error_message << "MeshWithNormals" << "::" << "initialize" << ": error: " << "guard \"(num_columns >= 0)\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!((num_rows >= 0)))
      {
         std::stringstream error_message;
         error_message << "MeshWithNormals" << "::" << "initialize" << ": error: " << "guard \"(num_rows >= 0)\" not met";
         throw std::runtime_error(error_message.str());
      }
   tileo_tile_vertex_allegro_vertex_declaration.initialize();
   clear_and_reserve();
   initialized = true;
   return;
}

void MeshWithNormals::destroy()
{
   // TODO: guards
   tileo_tile_vertex_allegro_vertex_declaration.destroy();
   destroyed = true;
   return;
}

void MeshWithNormals::resize(int num_columns, int num_rows)
{
   if (!((num_columns >= 0)))
      {
         std::stringstream error_message;
         error_message << "MeshWithNormals" << "::" << "resize" << ": error: " << "guard \"(num_columns >= 0)\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!((num_rows >= 0)))
      {
         std::stringstream error_message;
         error_message << "MeshWithNormals" << "::" << "resize" << ": error: " << "guard \"(num_rows >= 0)\" not met";
         throw std::runtime_error(error_message.str());
      }
   this->num_columns = num_columns;
   this->num_rows = num_rows;

   clear_and_reserve();
   place_vertexes_into_tile_mesh_shape();

   return;
}

void MeshWithNormals::place_vertexes_into_tile_mesh_shape()
{
   // place the vertexes to create a mesh of boxes for tiles
   int num_vertexes = num_columns*num_rows*6;
   for (int v=0; v<num_vertexes; v+=6)
   {
      long tile_num = v / 6;

      int x1 = (tile_num % num_columns);
      int y1 = (tile_num / num_columns);
      int x2 = x1 + 1;
      int y2 = y1 + 1;

      vertexes[v+0].x = x1;
      vertexes[v+0].y = y1;

      vertexes[v+1].x = x1;
      vertexes[v+1].y = y2;

      vertexes[v+2].x = x2;
      vertexes[v+2].y = y2;

      vertexes[v+3].x = x2;
      vertexes[v+3].y = y2;

      vertexes[v+4].x = x2;
      vertexes[v+4].y = y1;

      vertexes[v+5].x = x1;
      vertexes[v+5].y = y1;
   }

   // "scale" the vertexes to tile_width and tile_height, and set other default values
   for (int v=0; v<num_vertexes; v++)
   {
      vertexes[v].x *= tile_width;
      vertexes[v].y *= tile_height;
      vertexes[v].z = 0;
      vertexes[v].color = al_map_rgba_f(1, 1, 1, 1);
   }

   return;
}

void MeshWithNormals::clear_and_reserve()
{
   int num_elements = num_rows * num_columns;
   TILEO_TILE_VERTEX empty_vertex = Tileo::TileoTileVertexAllegroVertexDeclaration::build_empty_vertex();

   tile_ids.clear();
   normal_tile_ids.clear();
   vertexes.clear();

   tile_ids.resize(num_elements, 0);
   normal_tile_ids.resize(num_elements, 0);
   vertexes.resize(num_elements*6, empty_vertex);

   return;
}
} // namespace Tileo


