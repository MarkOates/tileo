
#include <gtest/gtest.h>

#include <Tileo/MeshWithNormals.hpp>


TEST(Tileo_MeshWithNormalsTest, can_be_created_without_blowing_up)
{
   Tileo::MeshWithNormals mesh_with_normals;
}


TEST(Tileo_MeshWithNormalsTest, run__returns_the_expected_response)
{
   Tileo::MeshWithNormals mesh_with_normals;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, mesh_with_normals.run());
}

