#pragma once

#include <classes/main/Fon_class.h>

class Bucket : public Object {
 public:
  std::vector<sf::Texture> animat;
  int hearts = 3;
  bool dead = false;
  sf::Texture heart_texture;
  std::vector<Object*> heart;
  bool jump = 0;
  float max_height = 0;
  std::string inf = "up";
  char orientation = 'L';
  double horizontal_speed;
  double vertical_speed;
  sf::Clock tmr;
  double CurrentFrame = 0;
  double FPS = 0;
  bool down = false;
  Bucket(const sf::Texture& texture, double FPS, size_t NumberOfFrames,
         Window* parent, bool is_independent, std::string PathToFrames);
  void Reverse();
  void Update(double dt);
  void Turn_Left(double dt, double dist);
  void Turn_Right(double dt, double dist);
  void Jumping(double dt);
  ~Bucket() override;
};

class Loot : public Object {
 public:
  std::string name;
  Loot(const sf::Texture& texture, Window* parent, bool is_independent,
       std::string name);
};

class Game2 : Essence {
 private:
  Game2();
  static Game2* game2pointer;
  int coin = 0;
  Fon* background;
  Bucket* bucket;
  std::vector<Loot*> loot;
  sf::Clock global_timer;
  sf::Clock loot_timer;
  sf::Texture tnt_text;
  sf::Texture coin_text;
  Button* exit_button;
  int level = 1;
  double loot_speed;
  double loot_creat_time;
  double min_loot_creat_time;
  double max_loot_speed;
  void Loot_Generating();
  void Loot_Moving(double dt);

 public:
  void Draw() override;
  void button_link(const sf::Event& event);
  static Game2* getGame2();
  Game2(const Game2&) = delete;
  Game2& operator=(const Game2&) = delete;
  int get_coin();
  void Update(double dt);
  ~Game2() override;
};