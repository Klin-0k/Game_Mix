#pragma once

#include <classes/main/Window_class.h>

class Essence {
 public:
  Essence(Window* parent, bool is_independent);
  explicit Essence(bool is_independent);
  Essence();
  Essence(const Essence& other);
  Essence& operator=(const Essence& other);
  virtual ~Essence();
  virtual void SetEnableMod(bool enable);
  virtual void SetVisibleMod(bool visible);
  [[nodiscard]] bool GetEnableMod() const;
  [[nodiscard]] bool GetVisibleMod() const;
  const Window* parent();
  virtual void SetTextEnteredEvent(const std::function<void(const sf::Event&)>& Func);
  virtual void SetKeyPressedEvent(const std::function<void(const sf::Event&)>& Func);
  virtual void SetKeyReleasedEvent(const std::function<void(const sf::Event&)>& Func);
  void SetUpdateEvent(const std::function<void(double dt)>& Func);
  friend class Window;
  virtual void Draw();
  virtual void Delete();

 protected:
  bool enable_ = true;
  bool visible_ = true;
  Window* parent_;
  std::function<void(const sf::Event&)> TextEntered_ = nullptr;
  std::function<void(const sf::Event&)> KeyPressed_ = nullptr;
  std::function<void(const sf::Event&)> KeyReleased_ = nullptr;
  std::function<void(const double)> Update_ = nullptr;
  bool is_independent_;

 private:
};