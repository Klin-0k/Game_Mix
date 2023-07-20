#pragma once

#include <classes/main/Button_class.h>
#include <classes/main/Fon_class.h>

class ExitMenu : public Essence {
 public:
  explicit ExitMenu(Window* WindowThatShouldBeClosed);
  void Draw() override;
  static void CloseWithExitMenu(Window* window);
  void SetEnableMod(bool enable) override;
  ExitMenu(const ExitMenu&) = delete;
  ExitMenu& operator=(const ExitMenu&) = delete;
  ~ExitMenu() override;

 protected:
  Window* WindowThatShouldBeClosed;
  Button ButtonYES, ButtonNO;
  Fon ExitMenuFon;
  void YESButtonEvent(const sf::Event& event);
  void NOButtonEvent(const sf::Event& event);
  void ExitClosed();
  static std::unordered_set<Window*> WindowsWithOpenExit;
};

class Settings {
 public:
 private:
};