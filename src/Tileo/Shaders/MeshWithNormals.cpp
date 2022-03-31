

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
         //vec4 uv = al_tex_matrix * vec4(al_texcoord, 0, 1);
         //varying_texcoord = vec2(uv.x, uv.y);

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

     // normals logic:
     uniform sampler2D primary_texture; // analagous to al_tex
     uniform sampler2D normal_texture; // analagous to al_tex
     varying vec2 varying_normal_texcoord; // analagous to varying_texcoord

     bool alpha_test_func(float x, int op, float compare);
     void alter_by_tint(inout vec4 color);

     void main()
     {
       vec4 c;
       if (al_use_tex)
         //c = varying_color * texture2D(al_tex, varying_texcoord);
         //c = varying_color * texture2D(primary_texture, varying_texcoord);
         c = varying_color * texture2D(normal_texture, varying_normal_texcoord);
       else
         c = varying_color;
       if (!al_alpha_test || alpha_test_func(c.a, al_alpha_func, al_alpha_test_val))
         gl_FragColor = alter_by_tint(c);
       else
         discard;
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
        float inverse_tint_intensity = 1.0 - tint_intensity;
        color.r = (color.r * inverse_tint_intensity + tint.r * tint_intensity) * color.a;
        color.g = (color.g * inverse_tint_intensity + tint.g * tint_intensity) * color.a;
        color.b = (color.b * inverse_tint_intensity + tint.b * tint_intensity) * color.a;
        color.a = color.a;
     }

   )DELIM";
   return source;
}
} // namespace Shaders
} // namespace Tileo


