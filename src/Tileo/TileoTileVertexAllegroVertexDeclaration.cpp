

#include <Tileo/TileoTileVertexAllegroVertexDeclaration.hpp>
#include <stdexcept>
#include <sstream>
#include <Tileo/TileoTileVertex.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Tileo
{


TileoTileVertexAllegroVertexDeclaration::TileoTileVertexAllegroVertexDeclaration()
   : vertex_declaration(nullptr)
   , initialized(false)
   , destructed(false)
{
}


TileoTileVertexAllegroVertexDeclaration::~TileoTileVertexAllegroVertexDeclaration()
{
}


bool TileoTileVertexAllegroVertexDeclaration::get_initialized()
{
   return initialized;
}


bool TileoTileVertexAllegroVertexDeclaration::get_destructed()
{
   return destructed;
}


ALLEGRO_VERTEX_DECL* TileoTileVertexAllegroVertexDeclaration::get_vertex_declaration()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "TileoTileVertexAllegroVertexDeclaration" << "::" << "get_vertex_declaration" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!((!destructed)))
      {
         std::stringstream error_message;
         error_message << "TileoTileVertexAllegroVertexDeclaration" << "::" << "get_vertex_declaration" << ": error: " << "guard \"(!destructed)\" not met";
         throw std::runtime_error(error_message.str());
      }
   return vertex_declaration;
}

void TileoTileVertexAllegroVertexDeclaration::initialize()
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "TileoTileVertexAllegroVertexDeclaration" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "TileoTileVertexAllegroVertexDeclaration" << "::" << "initialize" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_primitives_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "TileoTileVertexAllegroVertexDeclaration" << "::" << "initialize" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_VERTEX_ELEMENT elems[] = {
      {ALLEGRO_PRIM_POSITION, ALLEGRO_PRIM_FLOAT_3, offsetof(TILEO_TILE_VERTEX, x)},
      {ALLEGRO_PRIM_TEX_COORD, ALLEGRO_PRIM_FLOAT_2, offsetof(TILEO_TILE_VERTEX, texture_u)},
      {ALLEGRO_PRIM_USER_ATTR, ALLEGRO_PRIM_FLOAT_2, offsetof(TILEO_TILE_VERTEX, normal_u)},
      {ALLEGRO_PRIM_USER_ATTR, ALLEGRO_PRIM_FLOAT_2, offsetof(TILEO_TILE_VERTEX, height_u)},
      {ALLEGRO_PRIM_USER_ATTR, ALLEGRO_PRIM_FLOAT_1, offsetof(TILEO_TILE_VERTEX, height)},
      {ALLEGRO_PRIM_COLOR_ATTR, 0, offsetof(TILEO_TILE_VERTEX, color)},
   };

   vertex_declaration = al_create_vertex_decl(elems, sizeof(TILEO_TILE_VERTEX));

   return;
}

void TileoTileVertexAllegroVertexDeclaration::destroy()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "TileoTileVertexAllegroVertexDeclaration" << "::" << "destroy" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!((!destructed)))
      {
         std::stringstream error_message;
         error_message << "TileoTileVertexAllegroVertexDeclaration" << "::" << "destroy" << ": error: " << "guard \"(!destructed)\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!vertex_declaration)
   {
      throw std::runtime_error("there was an error destroying the TileoTileVertexWithNormal declaration.");
   }
   al_destroy_vertex_decl(vertex_declaration);
   destructed = true;
   return;
}
} // namespace Tileo


