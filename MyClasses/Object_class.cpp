Object::Object(const sf::Texture& texture,
               const sf::Rect<int>& rect,
               int X = MainWindow->getSize().x / 2,
               int Y = MainWindow->getSize().y / 2,
               Window* parent = MainWindow,
               bool is_independent = true) : Essence(parent, is_independent) {
  sf::Vector2u parent_size = parent->getSize();
  sf::Vector2f sprite_size = static_cast<sf::Vector2f>(Sprite_.getTexture()->getSize());
  sf::Vector2f
      position(parent_size.x / 2 - sprite_size.x / 2, parent_size.y / 2 - sprite_size.y / 2);
  Sprite_.setPosition(position);
}
Object::Object(const sf::Texture& texture,
               const sf::Rect<int>& rect,
               Window* parent = MainWindow,
               bool is_independent = true) : Object(texture,
                                                    rect,
                                                    parent->getSize().x / 2,
                                                    parent->getSize().y / 2,
                                                    parent,
                                                    is_independent) {}
Object::Object(const sf::Texture& texture,
               Window* parent = MainWindow,
               bool is_independent = true) : Object(texture,
                                                    sf::Rect{0, 0, 0, 0},
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
#ifdef DEBAG
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
void Object::Assign(const sf::Texture& texture) { Sprite_.setTexture(texture); }
void Object::SetMouseWheelScrolledEvent(const std::function<void(const sf::Event&)>& Func) {
  parent_->ObjectsWithMouseWheelScrolledEvent.erase(this);
  MouseWheelScrolled = Func;
  if (Func != nullptr) {
    parent_->ObjectsWithMouseWheelScrolledEvent.insert(this);
  }
}
void Object::SetMouseButtonPressedEvent(const std::function<void(const sf::Event&)>& Func) {
  parent_->ObjectsWithMouseButtonPressedEvent.erase(this);
  MouseButtonPressed = Func;
  if (Func != nullptr) {
    parent_->ObjectsWithMouseButtonPressedEvent.insert(this);
  }
}
void Object::SetMouseButtonReleasedEvent(const std::function<void(const sf::Event&)>& Func) {
  parent_->ObjectsWithMouseButtonReleasedEvent.erase(this);
  MouseButtonReleased = Func;
  if (Func != nullptr) {
    parent_->ObjectsWithMouseButtonReleasedEvent.insert(this);
  }
}
void Object::SetMouseMovedEvent(const std::function<void(const sf::Event&)>& Func) {
  parent_->ObjectsWithMouseMovedEvent.erase(this);
  MouseMoved = Func;
  if (MouseMoved != nullptr || MouseEntered != nullptr || MouseLeft != nullptr) {
    parent_->ObjectsWithMouseMovedEvent.insert(this);
  }
}
void Object::SetMouseEnteredEvent(const std::function<void(const sf::Event&)>& Func) {
  parent_->ObjectsWithMouseMovedEvent.erase(this);
  MouseEntered = Func;
  if (MouseMoved != nullptr || MouseEntered != nullptr || MouseLeft != nullptr) {
    parent_->ObjectsWithMouseMovedEvent.insert(this);
  }
}
void Object::SetMouseLeftEvent(const std::function<void(const sf::Event&)>& Func) {
  parent_->ObjectsWithMouseMovedEvent.erase(this);
  MouseLeft = Func;
  if (MouseMoved != nullptr || MouseEntered != nullptr || MouseLeft != nullptr) {
    parent_->ObjectsWithMouseMovedEvent.insert(this);
  }
}
void Object::Draw() {
  parent_->draw(Sprite_);
}