
#include <gtest/gtest.h>

#include <Tileo/MeshWithNormals.hpp>


TEST(Tileo_MeshWithNormalsTest, can_be_created_without_blowing_up)
{
   Tileo::MeshWithNormals mesh_with_normals;
}


TEST(Tileo_MeshWithNormalsTest, initialize__works_without_blowing_up)
{
   al_init();
   al_init_primitives_addon();
   al_set_new_display_flags(ALLEGRO_PROGRAMMABLE_PIPELINE);
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);
   
   Tileo::MeshWithNormals mesh_with_normals(6, 4, 16, 16);
   mesh_with_normals.initialize();

   al_destroy_display(display);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


