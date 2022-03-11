
#include <gtest/gtest.h>

#include <Tileo/TMJDataLoader.hpp>

TEST(Tileo_TMJDataLoaderTest, can_be_created_without_blowing_up)
{
   Tileo::TMJDataLoader tmjdata_loader;
}

TEST(Tileo_TMJDataLoaderTest, run__returns_the_expected_response)
{
   Tileo::TMJDataLoader tmjdata_loader;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, tmjdata_loader.run());
}
