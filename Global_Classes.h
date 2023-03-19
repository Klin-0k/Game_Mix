#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

extern sf::RenderWindow window;

//----------------------------------------------------------

class Object {
 public:
  Object(const sf::Image& image, sf::Rect<int> rect, sf::RenderWindow& parent = window, int X = window.getSize().x / 2, int Y = window.getSize().y / 2): parent_(parent), Ox(X), Oy(Y) {
    SetEnableMod(true);
    SetVisibleMod(true);
  }
  Object(const sf::Image& image, sf::Rect<int> rect, sf::RenderWindow& parent): Object(image, rect, parent, parent.getSize().x / 2, parent.getSize().y / 2) {}
  void Move(int X, int Y);
  void MoveByCenter(int X, int Y);
  void SetEnableMod(bool enable);
  void SetVisibleMod(bool visible);
  bool GetEnableMod();
  bool GetVisibleMod();
  const sf::RenderWindow& parent();
  void SetTextEnteredEvent(void (* Func)());
  void SetKeyPressedEvent(void (* Func)());
  void SetKeyReleasedEvent(void (* Func)());
  void SetMouseWheelScrolledEvent(void (* Func)());
  void SetMouseButtonPressedEvent(void (* Func)());
  void SetMouseButtonReleasedEvent(void (* Func)());
  void SetMouseMovedEvent(void (* Func)());
  void SetMouseEnteredEvent(void (* Func)());
  void SetMouseLeftEvent(void (* Func)());
  friend void EventHandling();
  void Draw();
 protected:
  int Ox, Oy;
  sf::Sprite Sprite_;
  bool enable_ = true;
  bool visible_ = true;
  sf::RenderWindow& parent_;
 private:
  void (* TextEntered)() = nullptr;
  void (* KeyPressed)() = nullptr;
  void (* KeyReleased)() = nullptr;
  void (* MouseWheelScrolled)() = nullptr;
  void (* MouseButtonPressed)() = nullptr;
  void (* MouseButtonReleased)() = nullptr;
  void (* MouseMoved)() = nullptr;
  void (* MouseEntered)() = nullptr;
  void (* MouseLeft)() = nullptr;
};

class Character : Object {
 public:
 private:
};

//----------------------------------------------------------

class Button : public Object {
 public:
 private:
  bool pressed;
};

class Game {
 public:
 private:
};

class MainMenu {
 public:
 private:
  Button MenuButton, SettingsButton, ExitButton;
  Button Game1Button, Game2Button, Game3Button, Game4Button;

};

class InGameMenu {
 public:
 private:
  Button ContinueButton, MainMenuButton, SettingsButton, ExitButton;
};

class Exit {
 public:
 private:
  Button ButtonYES, ButtonNO;
};

class Settings {
 public:
 private:
};

//----------------------------------------------------------

class Profile {
 public:
 private:
};

class User {
 public:
 private:
};

class BigBoy {
 public:
 private:
};