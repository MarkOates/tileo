

#include <Tileo/Shaders/MeshWithNormals.hpp>
#include <stdexcept>
#include <sstream>


namespace Tileo
{
namespace Shaders
{


MeshWithNormals::MeshWithNormals()
   : Tileo::Shaders::Base(obtain_vertex_source(), obtain_fragment_source())
   , initialized(false)
{
}


MeshWithNormals::~MeshWithNormals()
{
}


void MeshWithNormals::initialize()
{
   if (!initialized) Tileo::Shaders::Base::initialize();
   initialized = true;
}

void MeshWithNormals::activate()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "MeshWithNormals" << "::" << "activate" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   Tileo::Shaders::Base::activate();
}

void MeshWithNormals::set_flat_color(ALLEGRO_COLOR flat_color, float intensity)
{
   Shader::set_vec3("tint", flat_color.r, flat_color.g, flat_color.b);
   Shader::set_float("tint_intensity", intensity);
   return;
}

void MeshWithNormals::set_light_angle_of_incidence(float light_angle_of_incidence)
{
   Shader::set_float("light_angle_of_incidence", light_angle_of_incidence);
   return;
}

void MeshWithNormals::set_light_spread(int light_spread)
{
   Shader::set_int("light_spread", light_spread);
   return;
}

void MeshWithNormals::set_primary_texture(ALLEGRO_BITMAP* primary_texture_bitmap)
{
   Shader::set_sampler("primary_texture", primary_texture_bitmap, 1);
   return;
}

void MeshWithNormals::set_normal_texture(ALLEGRO_BITMAP* normal_texture_bitmap)
{
   Shader::set_sampler("normal_texture", normal_texture_bitmap, 2);
   return;
}

std::string MeshWithNormals::obtain_vertex_source()
{
   static const std::string source = R"DELIM(
     attribute vec4 al_pos;
     attribute vec4 al_color;
     attribute vec2 al_texcoord;
     uniform mat4 al_projview_matrix;
     uniform bool al_use_tex_matrix;
     uniform mat4 al_tex_matrix;
     varying vec4 varying_color;
     varying vec2 varying_texcoord;

     // normals logic:
     attribute vec2 al_user_attr_0; // this is the normal_u/normal_v
     varying vec2 varying_normal_texcoord; // analagous to varying_texcoord

     void main()
     {
       varying_color = al_color;
       if (al_use_tex_matrix)
       {
         vec4 uv = al_tex_matrix * vec4(al_texcoord, 0, 1);
         varying_texcoord = vec2(uv.x, uv.y);

         // normals logic:
         vec4 normal_uv = al_tex_matrix * vec4(al_user_attr_0, 0, 1);
         varying_normal_texcoord = vec2(normal_uv.x, normal_uv.y);
       }
       else
       {
         varying_texcoord = al_texcoord;
       }
       gl_Position = al_projview_matrix * al_pos;
     }
   )DELIM";
   return source;
}

std::string MeshWithNormals::obtain_fragment_source()
{
   static const std::string source = R"DELIM(
     #ifdef GL_ES
     precision lowp float;
     #endif
     uniform sampler2D al_tex;
     uniform bool al_use_tex;
     uniform bool al_alpha_test;
     uniform int al_alpha_func;
     uniform float al_alpha_test_val;
     varying vec4 varying_color;
     varying vec2 varying_texcoord;
     uniform float tint_intensity;
     uniform vec3 tint;

     // lights logic:
     uniform float light_angle_of_incidence;
     uniform int light_spread;

     // normals logic:
     uniform sampler2D primary_texture; // analagous to al_tex
     uniform sampler2D normal_texture; // analagous to al_tex
     varying vec2 varying_normal_texcoord; // analagous to varying_texcoord

     bool alpha_test_func(float x, int op, float compare);
     void alter_by_tint(inout vec4 color);
     void alter_by_normal_texture_color(inout vec4 color, in vec4 normal_color);

     void main()
     {
       vec4 c, normal_c;
       if (al_use_tex)
       {
         c = varying_color * texture2D(primary_texture, varying_texcoord);
         normal_c = varying_color * texture2D(normal_texture, varying_normal_texcoord);
       }
       else
       {
         c = varying_color;
       }

       if (!al_alpha_test || alpha_test_func(c.a, al_alpha_func, al_alpha_test_val))
       {
         vec4 normal_altered_c = alter_by_normal_texture_color(c, normal_c);

         gl_FragColor = alter_by_tint(normal_altered_c);
       }
       else
       {
         discard;
       }
     }

     bool alpha_test_func(float x, int op, float compare)
     {
       if (op == 0) return false;
       else if (op == 1) return true;
       else if (op == 2) return x < compare;
       else if (op == 3) return x == compare;
       else if (op == 4) return x <= compare;
       else if (op == 5) return x > compare;
       else if (op == 6) return x != compare;
       else if (op == 7) return x >= compare;
       return false;
     }

     void alter_by_tint(inout vec4 color)
     {
        return;

        float inverse_tint_intensity = 1.0 - tint_intensity;
        color.r = (color.r * inverse_tint_intensity + tint.r * tint_intensity) * color.a;
        color.g = (color.g * inverse_tint_intensity + tint.g * tint_intensity) * color.a;
        color.b = (color.b * inverse_tint_intensity + tint.b * tint_intensity) * color.a;
        color.a = color.a;
     }

     void alter_by_normal_texture_color(inout vec4 color, in vec4 normal_color)
     {
        //int spread = 1;
        int light_direction_y = int(floor(light_angle_of_incidence * 8.0 + 0.5));
        int angle_to_light_y = int(floor(normal_color.g * 8.0 + 0.5));
        bool in_shadow =
          (abs(float(light_direction_y) - float(angle_to_light_y)) > float(4));
        bool in_light =
          (abs(float(light_direction_y) - float(angle_to_light_y)) < max(1.0, float(light_spread * 2)));

        if (in_shadow)
        {
           // darken
           color.r = color.r *= 0.8; //normal_color.r; //inverse_tint_intensity + tint.r * tint_intensity) * color.a;
           color.g = color.g *= 0.8; //normal_color.g; //inverse_tint_intensity + tint.g * tint_intensity) * color.a;
           color.b = color.b *= 0.8; //normal_color.b; //inverse_tint_intensity + tint.b * tint_intensity) * color.a;
           color.a = color.a *= 0.8;
        }

        if (in_light)
        {
           //return;

           // brighten
           color.r = color.r += 0.2; //normal_color.r; //inverse_tint_intensity + tint.r * tint_intensity) * color.a;
           color.g = color.g += 0.2; //normal_color.g; //inverse_tint_intensity + tint.g * tint_intensity) * color.a;
           color.b = color.b += 0.2; //normal_color.b; //inverse_tint_intensity + tint.b * tint_intensity) * color.a;
           color.a = color.a += 0.2;
        }
     }

   )DELIM";
   return source;
}
} // namespace Shaders
} // namespace Tileo


