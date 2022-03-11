
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

class Tileo_TMJMeshLoaderTest : public ::testing::Test
{};

class Tileo_TMJMeshLoaderTestWithAllegroRenderingFixture : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <Tileo/TMJMeshLoader.hpp>

#define TMJ_FIXTURE_PATH "/Users/markoates/Repos/tileo/tests/fixtures/"
#define TMJ_FIXTURE_FILENAME "map1.tmj"
#define TILE_ATLAS_FILENAME "tiles_dungeon_v1.1.png"



TEST_F(Tileo_TMJMeshLoaderTest, can_be_created_without_blowing_up)
{
   Tileo::TMJMeshLoader tmjmesh_loader;
}

TEST_F(Tileo_TMJMeshLoaderTestWithAllegroRenderingFixture, create_mesh__returns_a_mesh_filled_with_the_expected_data)
{
   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   bitmap_bin.set_full_path(TMJ_FIXTURE_PATH);
   Tileo::Atlas atlas;
   Tileo::TMJMeshLoader tmjmesh_loader(&bitmap_bin, &atlas, std::string(TMJ_FIXTURE_PATH) + TMJ_FIXTURE_FILENAME);
   Tileo::Mesh *mesh = tmjmesh_loader.create_mesh();

   mesh->render();
   al_flip_display();
   sleep(0.4);

   delete mesh;
}


