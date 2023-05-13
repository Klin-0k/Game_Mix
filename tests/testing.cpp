#include "../Global_Classes.cpp"
#include "InterfaceTests.cpp"
#include <SFML/Window/Keyboard.hpp>
#include <gtest/gtest.h>

TEST(LootTest, Constructor) {
  sf::Texture texture;
  Window window(sf::VideoMode(400, 600), "My window", sf::Style::None);
  Loot loot(texture, &window, false, "test_name");
  EXPECT_EQ(loot.name, "test_name");
  window.close();
}

TEST(BucketTest, BucketTest1) {
  sf::Texture texture;
  sf::Window w;
  Window window(sf::VideoMode(1000, 800), "My window", sf::Style::None);
  Bucket bucket(texture, 60.0, 12, &window, false, "../Resources/game2/animation/*.png");
  EXPECT_EQ(bucket.animat.size(), 12);
  EXPECT_EQ(bucket.FPS, 60.0);
  window.close();
}

TEST(BucketTest, BucketTest2) {
  sf::Texture texture;
  sf::Window w;
  Window window(sf::VideoMode(1000, 800), "My window", sf::Style::None);
  Bucket bucket(texture, 60.0, 12, &window, false, "../Resources/game2/animation/*.png");
  EXPECT_EQ(bucket.orientation, 'L');
  bucket.Turn_Right(0.1, 1);
  bucket.Update(0.01);
  EXPECT_EQ(bucket.orientation, 'R');
  window.close();
}

TEST(BucketTest, BucketTest3) {
  sf::Texture texture;
  sf::Window w;
  Window window(sf::VideoMode(1000, 800), "My window", sf::Style::None);
  Bucket bucket(texture, 60.0, 12, &window, false, "../Resources/game2/animation/*.png");
  bucket.jump = true;
  bucket.Jumping(1);
  EXPECT_EQ(bucket.GetTop() > bucket.parent()->getSize().y / 2, true);
  window.close();
}

TEST(BucketTest, BucketTest4) {
  sf::Texture texture;
  sf::Window w;
  Window window(sf::VideoMode(1000, 800), "My window", sf::Style::None);
  Bucket bucket(texture, 60.0, 12, &window, false, "../Resources/game2/animation/*.png");
  bucket.hearts = 0;
  bucket.Update(0.01);
  EXPECT_EQ(bucket.dead, true);
  window.close();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}