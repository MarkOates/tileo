
#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Tileo/MeshWithNormals.hpp>

#include <AllegroFlare/BitmapBin.hpp>

class Tileo_MeshWithNormalsRenderingFixtureTest : public ::testing::Test
{
private:
   ALLEGRO_DISPLAY *display;

public:
   Tileo_MeshWithNormalsRenderingFixtureTest()
     : display(nullptr)
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      al_init_primitives_addon();
      al_set_new_display_flags(ALLEGRO_PROGRAMMABLE_PIPELINE | ALLEGRO_OPENGL);
      ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   }

   virtual void TearDown() override
   {
      if (display) al_destroy_display(display);
      al_shutdown_primitives_addon();
      al_uninstall_system();
   }
};

class Tileo_MeshWithNormalsTestFixture : public ::testing::Test {};


TEST_F(Tileo_MeshWithNormalsTestFixture, can_be_created_without_blowing_up)
{
   Tileo::MeshWithNormals mesh_with_normals;
}


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest, initialize__works_without_blowing_up)
{
   Tileo::MeshWithNormals mesh_with_normals(6, 4, 16, 16);
   mesh_with_normals.initialize();
   mesh_with_normals.destroy();
}


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest, initialize__with_num_columns_less_than_zero__throws_an_error)
{
   Tileo::MeshWithNormals mesh_with_normals(-1, 4, 16, 16);
   std::string expected_error_message = "MeshWithNormals::initialize: error: guard \"(num_columns >= 0)\" not met";
   EXPECT_THROW_WITH_MESSAGE(mesh_with_normals.initialize(), std::runtime_error, expected_error_message);
}


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest, initialize__with_num_rows_less_than_zero__throws_an_error)
{
   Tileo::MeshWithNormals mesh_with_normals(6, -1, 16, 16);
   std::string expected_error_message = "MeshWithNormals::initialize: error: guard \"(num_rows >= 0)\" not met";
   EXPECT_THROW_WITH_MESSAGE(mesh_with_normals.initialize(), std::runtime_error, expected_error_message);
}


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest, initialize__if_called_more_than_once__throws_an_error)
{
   Tileo::MeshWithNormals mesh_with_normals(6, 4, 16, 16);
   mesh_with_normals.initialize();
   std::string expected_error_message = "MeshWithNormals::initialize: error: guard \"(!initialized)\" not met";
   EXPECT_THROW_WITH_MESSAGE(mesh_with_normals.initialize(), std::runtime_error, expected_error_message);
   mesh_with_normals.destroy();
}


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest, set_tile__if_called_before_initialization__throws_an_error)
{
   // TODO
}


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest, set_tile__without_an_atlas__throws_an_error)
{
   // TODO
}


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest, set_tile__with_a_tile_x_that_is_out_of_bounds__does_nothing)
{
   // TODO
}


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest, set_tile__with_a_tile_y_that_is_out_of_bounds__does_nothing)
{
   // TODO
}


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest, vertexes_will_render_as_expected)
{
   Tileo::MeshWithNormals mesh_with_normals(6, 4, 16, 16);
   mesh_with_normals.initialize();

   std::vector<TILEO_TILE_VERTEX> vertexes = mesh_with_normals.get_vertexes_ref();
   ALLEGRO_VERTEX_DECL* vertex_declaration = mesh_with_normals.obtain_vertex_declaration();
   ALLEGRO_BITMAP* texture = nullptr;

   al_draw_prim(&vertexes, vertex_declaration, texture, 0, vertexes.size(), ALLEGRO_PRIM_TRIANGLE_LIST);

   mesh_with_normals.destroy();
}


TEST_F(Tileo_MeshWithNormalsRenderingFixtureTest, INTERACTIVE__vertexes_will_render_as_expected)
{
   al_init_image_addon();
   Tileo::MeshWithNormals mesh_with_normals(6, 4, 16, 16);
   mesh_with_normals.initialize();
   AllegroFlare::BitmapBin bitmap_bin;
   bitmap_bin.set_full_path("/Users/markoates/Repos/tileo/bin/programs/data/bitmaps/");

   // HERE:
   //set_tile(...)

   std::vector<TILEO_TILE_VERTEX> vertexes = mesh_with_normals.get_vertexes_ref();
   ALLEGRO_VERTEX_DECL* vertex_declaration = mesh_with_normals.obtain_vertex_declaration();
   ALLEGRO_BITMAP* texture = bitmap_bin["tiles_dungeon_v1.1.png"];

   al_draw_prim(&vertexes, vertex_declaration, texture, 0, vertexes.size(), ALLEGRO_PRIM_TRIANGLE_LIST);

   sleep(2);

   mesh_with_normals.destroy();
   al_shutdown_image_addon();
}


