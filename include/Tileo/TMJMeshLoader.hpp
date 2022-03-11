#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <Tileo/Atlas.hpp>
#include <Tileo/Mesh.hpp>
#include <string>


namespace Tileo
{
   class TMJMeshLoader
   {
   private:
      AllegroFlare::BitmapBin* bitmap_bin;
      Tileo::Atlas* tile_atlas;
      std::string filename;
      std::string bitmap_atlas_filename;

   public:
      TMJMeshLoader(AllegroFlare::BitmapBin* bitmap_bin=nullptr, Tileo::Atlas* tile_atlas=nullptr, std::string filename="filename-not-set.tmj", std::string bitmap_atlas_filename="tiles_dungeon_v1.1.png");
      ~TMJMeshLoader();

      Tileo::Mesh* create_mesh();
   };
}



