#pragma once

#include <classes/main/Fon_class.h>

struct Coords {
  int x;
  int y;
};

struct Figure {
  std::vector<sf::RectangleShape> tiles;
  size_t size;
  int type;
};

class Game1 : Essence {
 public:
  Game1();

  static Game1* game_1_pointer;

  Fon* background;

  Object* game_background;
  Object* game_over_background;
  sf::Texture game_background_image;
  sf::Texture game_over_background_image;

  Button* back_button;
  Button* restart_button;

  static const int width_of_net_in_tiles = 15;
  int height_of_net_in_tiles;
  float indent_x;
  float indent_y;
  int tile_size;
  sf::RectangleShape tile;

  sf::RectangleShape red_line;
  sf::RectangleShape white_line1;
  sf::RectangleShape white_line2;
  sf::RectangleShape white_line3;
  sf::RectangleShape white_line4;

  std::vector<std::vector<Coords>> figures_pos;
  std::vector<std::vector<sf::RectangleShape>> figures;
  int type_of_figure;
  Figure figure;
  Figure next_figure;

  int speed_of_falling;
  int moves_by_x;
  int moves_by_y;
  int rotation;
  int indent_by_x;

  std::vector<std::vector<bool>> is_tiled;
  std::vector<std::vector<bool>> is_destroyed;
  std::vector<std::vector<bool>> supposed_to_be_destroyed;
  std::vector<std::vector<sf::Color>> mem_color;

  int start_transparency = 255;
  int transparency = start_transparency;

  int speed_of_destruction = 5;
  bool in_process_of_destruction = false;
  int row_of_destruction = -1;
  int counter_of_destructed_rows = 0;
  int max_value_before_speed_up = 5;

  bool is_active_game_over = false;
  int score = 0;

  int one_tile_cost = 10;
  int coins;
  int record;

  sf::Font main_font;
  sf::Text record_text;
  sf::Text record_value;
  sf::Text score_text;
  sf::Text score_value;
  sf::Text coins_text;
  sf::Text coins_value;
  sf::Text new_text;
  sf::Text back_text;
  sf::Text restart_text;
  sf::Text game_over_text;

  sf::Color color;
  sf::Color next_color;
  sf::Color my_green = {41, 232, 35};
  sf::Color my_blue = {20, 54, 247};
  sf::Color my_orange = {252, 233, 56};
  sf::Color my_skyblue = {187, 237, 234};
  sf::Color my_white = {255, 255, 255};
  sf::Color my_transparent = {255, 255, 255, 0};

  static Game1* getGame1();
  Game1(const Game1&) = delete;
  Game1& operator=(const Game1&) = delete;

  void Update(double dt);
  void Draw() override;

  void CreateBackground();
  void CreateButtons();
  void SetTileProperties();
  void CreateDesignLines();
  void CreateFigures();
  void SetFigureMovement();
  void CreateDataArrays();
  void CreateTextObjects();
  void DrawNet();
  void DrawFigure();
  void DrawNextFigure();
  void MaintainCorrectBottom();
  void SetNetTile();
  void MoveByX(const Figure& prev_figure);
  void MoveByY(const Figure& prev_figure);
  void Rotate(const Figure& prev_figure);
  void UpdateCounters();
  void ReturnToBase();
  void FindDestroyedRows();
  void GetGameOver();

  sf::Color GetRandomColor();
  int GetRecord();
  void SetRecord(int my_record, int my_score);
  void SetText(sf::Text& target,
               const sf::Font& font,
               const std::string& text,
               int character_size,
               sf::Color my_color,
               sf::Vector2f pos);

  void CheckEvents(const sf::Event& event);
  void DestroyRow(int i, int j);
  void ReloadNet();

  void ButtonLink(const sf::Event& event);
  void ReloadGame(const sf::Event& event);

  ~Game1() override;
};