#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Global_Classes.cpp"

TEST(LootTest, Constructor) {
  sf::Texture texture;
  Window window(sf::VideoMode(400, 600), "My window", sf::Style::None);
  Loot loot(texture, &window, false, "test_name");
  EXPECT_EQ(loot.name, "test_name");
  window.close();
}

TEST(BucketTest, Constructor) {
  sf::Texture texture;
  Window window(sf::VideoMode(400, 600), "My window", sf::Style::None);
  Bucket bucket(texture, 60.0, 4, &window, false, "../Resources/game2/animation/*.png");
  EXPECT_EQ(bucket.animat.size(), 4);
  EXPECT_EQ(bucket.FPS, 60.0);
  window.close();
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}