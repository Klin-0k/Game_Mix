#include <classes/main/Object_class.h>

Object::Object(const sf::Texture& texture,
               int X = MainWindow->getSize().x / 2,
               int Y = MainWindow->getSize().y / 2,
               Window* parent = MainWindow,
               bool is_independent = true) : Essence(parent, is_independent) {
  Assign(texture);
  sf::Vector2u parent_size = parent->getSize();
  sf::Vector2f sprite_size = static_cast<sf::Vector2f>(Sprite_.getTexture()->getSize());
  sf::Vector2f
      position(parent_size.x / 2 - sprite_size.x / 2, parent_size.y / 2 - sprite_size.y / 2);
  Sprite_.setPosition(position);
}
Object::Object(const sf::Texture& texture,
               Window* parent = MainWindow,
               bool is_independent = true) : Object(texture,
                                                    parent->getSize().x / 2,
                                                    parent->getSize().y / 2,
                                                    parent,
                                                    is_independent) {}
Object::Object(Window* parent, bool is_independent) : Essence(parent, is_independent) {
  sf::Vector2u parent_size = parent->getSize();
  sf::Vector2f position(parent_size.x / 2, parent_size.y / 2);
  Sprite_.setPosition(position);
}
Object::Object(bool is_independent) : Object(MainWindow, is_independent) {}
Object::Object() : Object(true) {}
Object::~Object() {
  parent_->ObjectsWithMouseWheelScrolledEvent.erase(this);
  parent_->ObjectsWithMouseButtonPressedEvent.erase(this);
  parent_->ObjectsWithMouseButtonReleasedEvent.erase(this);
  parent_->ObjectsWithMouseMovedEvent.erase(this);
#ifdef DEBUG
  std::cout << "~Object\n";
#endif
}
float Object::GetX() {
  return Sprite_.getPosition().x;
}
float Object::GetY() {
  return Sprite_.getPosition().y;
}
float Object::GetWidth() {
  return Sprite_.getGlobalBounds().width;
}
float Object::GetHeight() {
  return Sprite_.getGlobalBounds().height;
}
float Object::GetLocalWidth() {
  return Sprite_.getLocalBounds().width;
}
float Object::GetLocalHeight() {
  return Sprite_.getLocalBounds().height;
}
float Object::GetLeft() {
  return GetX();
}
float Object::GetTop() {
  return GetY();
}
float Object::GetRight() {
  return GetX() + GetWidth();
}
float Object::GetBottom() {
  return GetY() + GetHeight();
}
void Object::SetScale(float scaleX, float scaleY) {
  Sprite_.setScale(scaleX, scaleY);
}
void Object::SetSize(float Width, float Height) {
  float scaleX = Width / GetWidth();
  float scaleY = Height / GetHeight();
  SetScale(scaleX, scaleY);
}
void Object::Move(float X, float Y) {
  Sprite_.setPosition(X, Y);
}
void Object::MoveByCenter(float X, float Y) {
  Sprite_.setPosition(X - GetWidth() / 2, Y - GetHeight() / 2);
}
void Object::AssignMyTexture(const sf::Texture& texture) {
  Sprite_.setTexture(texture);
}
void Object::Assign(const sf::Texture& texture) {
  Texture_ = texture;
  Sprite_.setTexture(Texture_);
}
void Object::SetMouseWheelScrolledEvent(const std::function<void(const sf::Event&)>& Func) {
  parent_->ObjectsWithMouseWheelScrolledEvent.erase(this);
  MouseWheelScrolled_ = Func;
  if (Func != nullptr) {
    parent_->ObjectsWithMouseWheelScrolledEvent.insert(this);
  }
}
void Object::SetMouseButtonPressedEvent(const std::function<void(const sf::Event&)>& Func) {
  parent_->ObjectsWithMouseButtonPressedEvent.erase(this);
  MouseButtonPressed_ = Func;
  if (Func != nullptr) {
    parent_->ObjectsWithMouseButtonPressedEvent.insert(this);
  }
}
void Object::SetMouseButtonReleasedEvent(const std::function<void(const sf::Event&)>& Func) {
  parent_->ObjectsWithMouseButtonReleasedEvent.erase(this);
  MouseButtonReleased_ = Func;
  if (Func != nullptr) {
    parent_->ObjectsWithMouseButtonReleasedEvent.insert(this);
  }
}
void Object::SetMouseMovedEvent(const std::function<void(const sf::Event&)>& Func) {
  parent_->ObjectsWithMouseMovedEvent.erase(this);
  MouseMoved_ = Func;
  if (MouseMoved_ != nullptr || MouseEntered_ != nullptr || MouseLeft_ != nullptr) {
    parent_->ObjectsWithMouseMovedEvent.insert(this);
  }
}
void Object::SetMouseEnteredEvent(const std::function<void(const sf::Event&)>& Func) {
  parent_->ObjectsWithMouseMovedEvent.erase(this);
  MouseEntered_ = Func;
  if (MouseMoved_ != nullptr || MouseEntered_ != nullptr || MouseLeft_ != nullptr) {
    parent_->ObjectsWithMouseMovedEvent.insert(this);
  }
}
void Object::SetMouseLeftEvent(const std::function<void(const sf::Event&)>& Func) {
  parent_->ObjectsWithMouseMovedEvent.erase(this);
  MouseLeft_ = Func;
  if (MouseMoved_ != nullptr || MouseEntered_ != nullptr || MouseLeft_ != nullptr) {
    parent_->ObjectsWithMouseMovedEvent.insert(this);
  }
}
void Object::Draw() {
  parent_->draw(Sprite_);
}
