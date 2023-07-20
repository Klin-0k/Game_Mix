#pragma once

#include <classes/main/Button_class.h>
#include <classes/main/Fon_class.h>

class PlayMenu : public Essence {
 public:
  int coins = 0;
  static PlayMenu* getPlayMenu();
  void Draw() override;
  ~PlayMenu() override;
  void SetEnableMod(bool enable) override;
  PlayMenu(const PlayMenu&) = delete;
  PlayMenu& operator=(const PlayMenu&) = delete;

 protected:
  static PlayMenu* ppm;
  static void BackButtonEvent(const sf::Event& event);
  static void Game2ButtonEvent(const sf::Event& event);
  static void Game1ButtonEvent(const sf::Event& event);
  PlayMenu();
  Button BackButton;
  Button Game1Button, Game2Button, Game3Button, Game4Button;
  Fon PlayMenuFon;
};