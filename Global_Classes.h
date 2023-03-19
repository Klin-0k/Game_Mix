#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Global_Variables.h"

//----------------------------------------------------------

class Object {
 public:
  void Move(int X, int Y);
  void MoveByCenter(int X, int Y);
  bool& enable();
  bool& visible();
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
 protected:
  int Ox, Oy;
  sf::Sprite Sprite_;
  sf::Texture Texture_;
  sf::RectangleShape Shape_;
  bool enable_ = true;
  bool visible_ = true;
  sf::RenderWindow& parent_;
  void draw(sf::RenderTarget& target, sf::RenderStates states);
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

std::unordered_set<Object*> ObjectsWithTextEnteredEvent = std::unordered_set<Object*>();
std::unordered_set<Object*> ObjectsWithKeyPressedEvent = std::unordered_set<Object*>();
std::unordered_set<Object*> ObjectsWithKeyReleasedEvent = std::unordered_set<Object*>();
std::unordered_set<Object*> ObjectsWithMouseWheelScrolledEvent = std::unordered_set<Object*>();
std::unordered_set<Object*> ObjectsWithMouseButtonPressedEvent = std::unordered_set<Object*>();
std::unordered_set<Object*> ObjectsWithMouseButtonReleasedEvent = std::unordered_set<Object*>();
std::unordered_set<Object*> ObjectsWithMouseMovedEvent = std::unordered_set<Object*>();
std::unordered_set<Object*> ObjectsWithMouseEnteredEvent = std::unordered_set<Object*>();
std::unordered_set<Object*> ObjectsWithMouseLeftEvent = std::unordered_set<Object*>();

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