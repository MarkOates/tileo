
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <Tileo/TMJDataLoader.hpp>

#define TMJ_FIXTURE_PATH "/Users/markoates/Repos/tileo/tests/fixtures/"
#define TMJ_FIXTURE_FILENAME "map1.tmj"
#define TMJ_MALFORMED_JSON_FIXTURE_FILENAME "file-with-malformed-json.tmj"
#define TMJ_FIXTURE_PATH_AND_FILENAME (TMJ_FIXTURE_PATH TMJ_FIXTURE_FILENAME)
#define TMJ_MALFORMED_JSON_FIXTURE_PATH_AND_FILENAME (TMJ_FIXTURE_PATH TMJ_MALFORMED_JSON_FIXTURE_FILENAME)


TEST(Tileo_TMJDataLoaderTest, can_be_created_without_blowing_up)
{
   Tileo::TMJDataLoader loader;
}


TEST(Tileo_TMJDataLoaderTest, get_loaded__before_calling_load__returns_false)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   Tileo::TMJDataLoader loader(filename);
   ASSERT_EQ(false, loader.get_loaded());
}


TEST(Tileo_TMJDataLoaderTest, get_loaded__after_calling_load__returns_true)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   Tileo::TMJDataLoader loader(filename);
   true, loader.load();
   ASSERT_EQ(true, loader.get_loaded());
}


TEST(Tileo_TMJDataLoaderTest, load__on_a_file_that_does_not_exist__throws_an_error)
{
   std::string filename = "some-file-that-does-not-exist.tmj";
   Tileo::TMJDataLoader loader(filename);

   std::string expected_error_message = "[Tileo/TMJDataLoader] load() error: the file \""
                                        + filename + "\" does not exist.";

   ASSERT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message);
}


TEST(Tileo_TMJDataLoaderTest, load__on_a_file_with_malformed_json__throws_an_error)
{
   std::string filename = TMJ_MALFORMED_JSON_FIXTURE_PATH_AND_FILENAME;
   Tileo::TMJDataLoader loader(filename);

   std::string expected_error_message = "[Tileo/TMJDataLoader] load() error: the file \""
      "/Users/markoates/Repos/tileo/tests/fixtures/file-with-malformed-json.tmj\" appears to have malformed JSON. "
      "The following error was thrown by nlohmann::json: \"[json.exception.parse_error.101] parse error at line 1, "
      "column 10: syntax error while parsing value - unexpected '}'; expected '[', '{', or a literal\"";

   ASSERT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message);
}


TEST(Tileo_TMJDataLoaderTest, load__returns_true)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   Tileo::TMJDataLoader loader(filename);

   ASSERT_EQ(true, loader.load());
}


TEST(Tileo_TMJDataLoaderTest, load__if_load_has_already_been_called__throws_an_error)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   Tileo::TMJDataLoader loader(filename);
   loader.load();

   std::string expected_error_message = "TMJDataLoader::load: error: guard \"(!loaded)\" not met";

   ASSERT_THROW_WITH_MESSAGE(loader.load(), std::runtime_error, expected_error_message);
}


TEST(Tileo_TMJDataLoaderTest, load__will_set_the_expected_values)
{
   std::string filename = TMJ_FIXTURE_PATH_AND_FILENAME;
   Tileo::TMJDataLoader loader(filename);

   loader.load();

   ASSERT_EQ(25, loader.get_num_columns());
   ASSERT_EQ(15, loader.get_num_rows());
   ASSERT_EQ(25, loader.get_layer_num_columns());
   ASSERT_EQ(15, loader.get_layer_num_rows());
}


TEST(Tileo_TMJDataLoaderTest, getters__before_load_has_been_called__will_throw_an_error)
{
   // TODO
}


