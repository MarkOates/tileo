
#include <gtest/gtest.h>

#include <Tileo/TileoTileVertexAllegroVertexDeclaration.hpp>
#define SUBJECT_UNDER_TEST TileoTileVertexAllegroVertexDeclaration

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#define BUILD_GUARD_ERROR_MESSAGE(class_name, method_name, guard_statement) \
   (#class_name "::" #method_name ": error: guard \"" #guard_statement "\" not met")


TEST(Tileo_TileoTileVertexAllegroVertexDeclarationTest, can_be_created_without_blowing_up)
{
   Tileo::TileoTileVertexAllegroVertexDeclaration declaration;
}


TEST(Tileo_TileoTileVertexAllegroVertexDeclarationTest,
   get_vertex_declaration__without_initialization__will_throw_an_error)
{
   Tileo::TileoTileVertexAllegroVertexDeclaration declaration;
   std::string expected_error_message =
      "TileoTileVertexAllegroVertexDeclaration::get_vertex_declaration: error: guard \"initialized\" not met";

   EXPECT_THROW_WITH_MESSAGE(declaration.get_vertex_declaration(), std::runtime_error, expected_error_message);
}


TEST(Tileo_TileoTileVertexAllegroVertexDeclarationTest, initialize__without_allegro_initialized__will_throw_an_error)
{
   Tileo::TileoTileVertexAllegroVertexDeclaration declaration;
   std::string expected_error_message =
      "TileoTileVertexAllegroVertexDeclaration::initialize: error: guard \"al_is_system_installed()\" not met";

   EXPECT_THROW_WITH_MESSAGE(declaration.initialize(), std::runtime_error, expected_error_message);
}


TEST(Tileo_TileoTileVertexAllegroVertexDeclarationTest,
   initialize__without_primitives_addon_initialized__will_throw_an_error)
{
   al_init();
   Tileo::TileoTileVertexAllegroVertexDeclaration declaration;

   EXPECT_THROW_WITH_MESSAGE(declaration.initialize(), std::runtime_error, BUILD_GUARD_ERROR_MESSAGE(
         TileoTileVertexAllegroVertexDeclaration,
         initialize,
         al_is_primitives_addon_initialized()
      )
   );

   al_uninstall_system();
}


