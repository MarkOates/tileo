#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <Tileo/Atlas.hpp>
#include <Tileo/Mesh.hpp>
#include <Tileo/TileMap.hpp>
#include <string>


namespace Tileo
{
   class TMJMeshLoader
   {
   private:
      static std::string BITMAP_ATLAS_FILENAME;
      AllegroFlare::BitmapBin* bitmap_bin;
      std::string tmj_filename;
      Tileo::Atlas* tile_atlas;
      Tileo::Mesh* mesh;
      Tileo::TileMap* collision_tile_map;
      bool loaded;

   public:
      TMJMeshLoader(AllegroFlare::BitmapBin* bitmap_bin=nullptr, std::string tmj_filename="filename-not-set.tmj");
      ~TMJMeshLoader();

      Tileo::Atlas* get_tile_atlas();
      Tileo::Mesh* get_mesh();
      Tileo::TileMap* get_collision_tile_map();
      bool load();
   };
}



