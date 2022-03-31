#pragma once


#include <Tileo/Shaders/Base.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace Tileo
{
   namespace Shaders
   {
      class MeshWithNormals : private Tileo::Shaders::Base
      {
      private:
         bool initialized;

      public:
         MeshWithNormals();
         ~MeshWithNormals();

         void initialize();
         void activate();
         void set_flat_color(ALLEGRO_COLOR flat_color={}, float intensity=1.0f);
         static std::string obtain_vertex_source();
         static std::string obtain_fragment_source();
      };
   }
}



