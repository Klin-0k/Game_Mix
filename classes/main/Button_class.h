#pragma once

#include <classes/main/Object_class.h>

class Button : public Object {
 public:
  Button(const sf::Texture& s1,
         const sf::Texture& s2,
         const sf::Texture& s3,
         Window* parent,
         bool is_independent);
  Button(sf::Texture&& s1,
         sf::Texture&& s2,
         sf::Texture&& s3,
         Window* parent,
         bool is_independent);
  Button(const std::string& s1,
         const std::string& s2,
         const std::string& s3,
         Window* parent,
         bool is_independent);
  Button(sf::Texture& s1,
         sf::Texture& s2,
         sf::Texture& s3,
         const sf::Text& text,
         Window* parent,
         bool is_independent);
  Button(sf::Texture&& s1,
         sf::Texture&& s2,
         sf::Texture&& s3,
         const sf::Text& text,
         Window* parent,
         bool is_independent);
  static void Print(sf::Text text, sf::Texture& texture);
  void Print(const sf::Text& text);
  void SetMouseButtonPressedEvent(const std::function<void(const sf::Event&)>& Func) override;
  void SetMouseButtonReleasedEvent(const std::function<void(const sf::Event&)>& Func) override;
  void SetMouseMovedEvent(const std::function<void(const sf::Event&)>& Func) override;
  void SetMouseEnteredEvent(const std::function<void(const sf::Event&)>& Func) override;
  void SetMouseLeftEvent(const std::function<void(const sf::Event&)>& Func) override;
  void SetEnableMod(bool enable) override;

  ~Button() override;

 protected:
  void ButtonMouseEntered();
  void ButtonMouseLeft();
  void ButtonMouseButtonPressed();
  void ButtonMouseButtonReleased();
  void ButtonMouseMoved();
  sf::Texture p1, p2, p3;

 private:
};
