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
         void set_light_angle_of_incidence(float light_angle_of_incidence=0.0f);
         void set_primary_texture(ALLEGRO_BITMAP* primary_texture_bitmap=nullptr);
         void set_normal_texture(ALLEGRO_BITMAP* normal_texture_bitmap=nullptr);
         static std::string obtain_vertex_source();
         static std::string obtain_fragment_source();
      };
   }
}



