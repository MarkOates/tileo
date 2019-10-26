
#include <gtest/gtest.h>

#include <adventures_of_beary/TileMap.hpp>

TEST(adventures_of_beary__TileMapTest, can_be_created_without_blowing_up)
{
   TileMap tile_map;
}

TEST(adventures_of_beary__TileMapTest, initializes_with_the_expected_values)
{
   TileMap tile_map;
   ASSERT_EQ(0, tile_map.get_width());
   ASSERT_EQ(0, tile_map.get_height());
}

TEST(adventures_of_beary__TileMapTest, is_dimensionless__returns_true_if_the_width_or_height_is_less_than_zero)
{
   TileMap tile_map;
   ASSERT_EQ(true, tile_map.is_dimensionless());
}

