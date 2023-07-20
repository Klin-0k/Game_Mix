#pragma once

#include <classes/main/Button_class.h>
#include <classes/main/Fon_class.h>

class MainMenu : public Essence {
 public:
  static MainMenu* getMainMenu();
  void Draw() override;
  ~MainMenu() override;
  void SetEnableMod(bool enable) override;
  MainMenu(const MainMenu&) = delete;
  MainMenu& operator=(const MainMenu&) = delete;

 protected:
  static MainMenu* pmm;
  static void PlayButtonEvent(const sf::Event& event);
  static void ExitButtonEvent(const sf::Event& event);
  MainMenu();
  Button PlayButton, SettingsButton, ExitButton;
  Fon MainMenuFon;
};