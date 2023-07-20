#pragma once

#include <classes/main/Essence_class.h>

class Object : public Essence {
 public:
  Object(const sf::Texture& texture,
         int X,
         int Y,
         Window* parent,
         bool is_independent);
  Object(const sf::Texture& texture, Window* parent, bool is_independent);
  Object(Window* parent, bool is_independent);
  explicit Object(bool is_independent);
  Object();
  ~Object() override;
  float GetX();
  float GetY();
  float GetWidth();
  float GetHeight();
  float GetLocalWidth();
  float GetLocalHeight();
  float GetLeft();
  float GetTop();
  float GetRight();
  float GetBottom();
  void SetScale(float scaleX, float scaleY);
  void SetSize(float Width, float Height);
  void Move(float X, float Y);
  void MoveByCenter(float X, float Y);
  virtual void SetMouseWheelScrolledEvent(const std::function<void(const sf::Event&)>& Func);
  virtual void SetMouseButtonPressedEvent(const std::function<void(const sf::Event&)>& Func);
  virtual void SetMouseButtonReleasedEvent(const std::function<void(const sf::Event&)>& Func);
  virtual void SetMouseMovedEvent(const std::function<void(const sf::Event&)>& Func);
  virtual void SetMouseEnteredEvent(const std::function<void(const sf::Event&)>& Func);
  virtual void SetMouseLeftEvent(const std::function<void(const sf::Event&)>& Func);
  friend class Window;
  void Draw() override;
  void AssignMyTexture(const sf::Texture& texture);
  void Assign(const sf::Texture& texture);

 protected:
  sf::Sprite Sprite_;
  sf::Texture Texture_;
  bool under_mouse_ = false;
  bool pressed_ = false;
  std::function<void(const sf::Event&)> MouseWheelScrolled_ = nullptr;
  std::function<void(const sf::Event&)> MouseButtonPressed_ = nullptr;
  std::function<void(const sf::Event&)> MouseButtonReleased_ = nullptr;
  std::function<void(const sf::Event&)> MouseMoved_ = nullptr;
  std::function<void(const sf::Event&)> MouseEntered_ = nullptr;
  std::function<void(const sf::Event&)> MouseLeft_ = nullptr;

 private:
};