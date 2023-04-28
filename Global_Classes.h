#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

extern sf::RenderWindow window;
//----------------------------------------------------------

class Object {
 public:
  Object(const sf::Texture& texture, const sf::Rect<int>& rect, int X, int Y, sf::RenderWindow* parent);
  Object(const sf::Texture& texture, const sf::Rect<int>& rect, sf::RenderWindow* parent);
  Object(const sf::Texture& texture, sf::RenderWindow* parent);
  Object(sf::RenderWindow* parent);
  Object();
  ~Object();
  void Move(int X, int Y);
  void MoveByCenter(int X, int Y);
  void SetEnableMod(bool enable);
  void SetVisibleMod(bool visible);
  bool GetEnableMod() const;
  bool GetVisibleMod() const;
  const sf::RenderWindow* parent();
  void SetTextEnteredEvent(void (* Func)(const sf::Event& event));
  void SetKeyPressedEvent(void (* Func)(const sf::Event& event));
  void SetKeyReleasedEvent(void (* Func)(const sf::Event& event));
  void SetMouseWheelScrolledEvent(void (* Func)(const sf::Event& event));
  void SetMouseButtonPressedEvent(void (* Func)(const sf::Event& event));
  void SetMouseButtonReleasedEvent(void (* Func)(const sf::Event& event));
  void SetMouseMovedEvent(void (* Func)(const sf::Event& event));
  void SetMouseEnteredEvent(void (* Func)(const sf::Event& event));
  void SetMouseLeftEvent(void (* Func)(const sf::Event& event));
  friend void EventHandling();
  void Draw();
 protected:
  int Ox, Oy;
  sf::Sprite Sprite_;
  bool enable_ = false;
  bool visible_ = false;
  bool under_mouse_ = false;
  bool pressed_ = false;
  sf::RenderWindow* parent_;
//  void (* TextEntered)(const sf::Event& event) = nullptr;
//  void (* KeyPressed)(const sf::Event& event) = nullptr;
//  void (* KeyReleased)(const sf::Event& event) = nullptr;
//  void (* MouseWheelScrolled)(const sf::Event& event) = nullptr;
//  void (* MouseButtonPressed)(const sf::Event& event) = nullptr;
//  void (* MouseButtonReleased)(const sf::Event& event) = nullptr;
//  void (* MouseMoved)(const sf::Event& event) = nullptr;
//  void (* MouseEntered)(const sf::Event& event) = nullptr;
//  void (* MouseLeft)(const sf::Event& event) = nullptr;
  std::function<void(const sf::Event&)> TextEntered = nullptr;
  std::function<void(const sf::Event&)> KeyPressed = nullptr;
  std::function<void(const sf::Event&)> KeyReleased = nullptr;
  std::function<void(const sf::Event&)> MouseWheelScrolled = nullptr;
  std::function<void(const sf::Event&)> MouseButtonPressed = nullptr;
  std::function<void(const sf::Event&)> MouseButtonReleased = nullptr;
  std::function<void(const sf::Event&)> MouseMoved = nullptr;
  std::function<void(const sf::Event&)> MouseEntered = nullptr;
  std::function<void(const sf::Event&)> MouseLeft = nullptr;

 private:

};

class Character : Object {
 public:
 private:
};

//----------------------------------------------------------

class Button : public Object {
 public:
  Button(const sf::Texture& s1, const sf::Texture& s2, const sf::Texture& s3, sf::RenderWindow* parent);
  Button(sf::Texture&& s1, sf::Texture&& s2, sf::Texture&& s3, sf::RenderWindow* parent);
  Button(sf::Texture& s1, sf::Texture& s2, sf::Texture& s3, const sf::Text& text, const sf::Color& color, sf::RenderWindow* parent);
  Button(sf::Texture&& s1, sf::Texture&& s2, sf::Texture&& s3, const sf::Text& text, const sf::Color& color, sf::RenderWindow* parent);
  void Print(const sf::Text& text, const sf::Color& color) {}
  void SetMouseButtonPressedEvent(void (* Func)(const sf::Event& event));
  void SetMouseButtonReleasedEvent(void (* Func)(const sf::Event& event));
  void SetMouseMovedEvent(void (* Func)(const sf::Event& event));
  void SetMouseEnteredEvent(void (* Func)(const sf::Event& event));
  void SetMouseLeftEvent(void (* Func)(const sf::Event& event));
 protected:
  void Assign(const sf::Texture& texture);
  void ButtonMouseEntered();
  void ButtonMouseLeft();
  void ButtonMouseButtonPressed();
  void ButtonMouseButtonReleased();
  void ButtonMouseMoved();
 private:
  sf::Texture p1, p2, p3;
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