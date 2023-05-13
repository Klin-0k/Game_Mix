#include "../Global_Classes.cpp"
#include <SFML/Window/Keyboard.hpp>
#include <gtest/gtest.h>

TEST(FirstFrameTest, StableGlobals) {
  Game1* game1 = Game1::GetGame1();
  EXPECT_FALSE(game1->is_active_game_over);
  EXPECT_GT(game1->tile_size, 0);
  EXPECT_LE(game1->tile_size, game1->game_background->GetWidth());
  EXPECT_EQ(game1->moves_by_x, 0);
  EXPECT_EQ(game1->moves_by_y, 0);
  EXPECT_EQ(game1->rotation, 0);
}

TEST(UpdateTest, CorrectMovements) {
  Game1* game1 = Game1::GetGame1();
  Figure figure_before_move_by_x = game1->figure;
  Figure figure_before_move_by_y = game1->figure;
  int tile_size = game1->tile_size;
  EXPECT_EQ(game1->speed_of_falling, 1);
  game1->speed_of_falling = 0;
  game1->moves_by_x = 1;
  game1->Update(0.01);
  EXPECT_EQ(tile_size, game1->tile_size);
  EXPECT_NE(figure_before_move_by_x, game1->figure);
  game1->moves_by_x = -1;
  game1->Update(0.01);
  EXPECT_EQ(figure_before_move_by_x, game1->figure);
  game1->moves_by_x = 0;
  game1->moves_by_y = 1;
  game1->Update(0.01);
  EXPECT_NE(figure_before_move_by_y, game1->figure);
  Figure figure_before_rotation = game1->figure;
  game1->moves_by_y = 0;
  game1->rotation = 1;
  game1->Update(0.01);
  EXPECT_NE(figure_before_rotation, game1->figure);
}

TEST(UpdateTest, CorrectCounters) {
  Game1* game1 = Game1::GetGame1();
  game1->coins = 3228;
  game1->record = 9999;
  game1->score = 2023;
  game1->Update(0.01);
  EXPECT_EQ(game1->coins_value.getString(), "3228");
  EXPECT_EQ(game1->record_value.getString(), "9999");
  EXPECT_EQ(game1->score_value.getString(), "2023");
}

TEST(UpdateTest, CorrectGameOver) {
  Game1* game1 = Game1::GetGame1();
  game1->is_active_game_over = true;
  game1->speed_of_falling = 5;
  game1->Update(0.01);
  game1->Update(0.01);
  EXPECT_GE(game1->record, game1->score);
  EXPECT_EQ(game1->speed_of_falling, 1);
}