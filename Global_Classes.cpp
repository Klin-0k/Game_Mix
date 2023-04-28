#include "Global_Variables.h"

Object::Object(const sf::Texture& texture, const sf::Rect<int>& rect, int X = window.getSize().x / 2, int Y = window.getSize().y / 2, sf::RenderWindow* parent = &window): parent_(parent), Ox(X), Oy(Y) {
  SetEnableMod(true);
  SetVisibleMod(true);
  AllObjects.push_back(this);
  sf::Vector2u parent_size = parent->getSize();
  sf::Vector2f sprite_size = static_cast<sf::Vector2f>(Sprite_.getTexture()->getSize());
  sf::Vector2f position(parent_size.x / 2 - sprite_size.x / 2, parent_size.y / 2 - sprite_size.y / 2);
  Sprite_.setPosition(position);
}
Object::Object(const sf::Texture& texture, const sf::Rect<int>& rect, sf::RenderWindow* parent = &window): Object(texture, rect, parent->getSize().x / 2, parent->getSize().y / 2, parent) {}
Object::Object(const sf::Texture& texture, sf::RenderWindow* parent = &window): Object(texture, sf::Rect{0, 0, 0, 0}, parent) {}
Object::Object(sf::RenderWindow* parent): parent_(parent) {
  SetEnableMod(true);
  SetVisibleMod(true);
  AllObjects.push_back(this);
  sf::Vector2u parent_size = parent->getSize();
  sf::Vector2f position(parent_size.x / 2, parent_size.y / 2);
  Sprite_.setPosition(position);
}
Object::Object(): Object(&window) {}
Object::~Object() {
  SetTextEnteredEvent(nullptr);
  SetKeyPressedEvent(nullptr);
  SetKeyReleasedEvent(nullptr);
  SetMouseWheelScrolledEvent(nullptr);
  SetMouseButtonPressedEvent(nullptr);
  SetMouseButtonReleasedEvent(nullptr);
  SetMouseMovedEvent(nullptr);
  SetMouseEnteredEvent(nullptr);
  SetMouseLeftEvent(nullptr);
  SetVisibleMod(false);
}

void Object::SetEnableMod(bool enable) {
  if (!enable_ && enable) {
    if (TextEntered != nullptr) {
      ObjectsWithTextEnteredEvent.insert(this);
    }
    if (KeyPressed != nullptr) {
      ObjectsWithKeyPressedEvent.insert(this);
    }
    if (KeyReleased != nullptr) {
      ObjectsWithKeyReleasedEvent.insert(this);
    }
    if (MouseWheelScrolled != nullptr) {
      ObjectsWithMouseWheelScrolledEvent.insert(this);
    }
    if (MouseButtonPressed != nullptr) {
      ObjectsWithMouseButtonPressedEvent.insert(this);
    }
    if (MouseButtonReleased != nullptr) {
      ObjectsWithMouseButtonReleasedEvent.insert(this);
    }
    if (MouseMoved != nullptr) {
      ObjectsWithMouseMovedEvent.insert(this);
    }
    if (MouseEntered != nullptr) {
      ObjectsWithMouseEnteredEvent.insert(this);
    }
    if (MouseLeft != nullptr) {
      ObjectsWithMouseLeftEvent.insert(this);
    }
  }
  if (enable_ && !enable) {
    ObjectsWithTextEnteredEvent.erase(this);
    ObjectsWithKeyPressedEvent.erase(this);
    ObjectsWithKeyReleasedEvent.erase(this);
    ObjectsWithMouseWheelScrolledEvent.erase(this);
    ObjectsWithMouseButtonPressedEvent.erase(this);
    ObjectsWithMouseButtonReleasedEvent.erase(this);
    ObjectsWithMouseMovedEvent.erase(this);
    ObjectsWithMouseEnteredEvent.erase(this);
    ObjectsWithMouseLeftEvent.erase(this);
  }
  enable_ = enable;
  if (enable_ && !visible_) {
    SetVisibleMod(true);
  }
}
void Object::SetVisibleMod(bool visible) {
  if (!visible_ && visible) {
    ObjectsToDraw.insert(this);
  }
  if (visible_ && !visible) {
    ObjectsToDraw.erase(this);
  }
  visible_ = visible;
  if (!visible_ && enable_) {
    SetEnableMod(false);
  }
}
bool Object::GetEnableMod() const {
  return enable_;
}
bool Object::GetVisibleMod() const {
  return visible_;
}
const sf::RenderWindow* Object::parent() {
  return parent_;
}
void Object::SetTextEnteredEvent(void (* Func)(const sf::Event& event)) {
  ObjectsWithTextEnteredEvent.erase(this);
  TextEntered = Func;
  if (Func != nullptr) {
    ObjectsWithTextEnteredEvent.insert(this);
  }
}
void Object::SetKeyPressedEvent(void (* Func)(const sf::Event& event)) {
  ObjectsWithKeyPressedEvent.erase(this);
  KeyPressed = Func;
  if (Func != nullptr) {
    ObjectsWithKeyPressedEvent.insert(this);
  }
}
void Object::SetKeyReleasedEvent(void (* Func)(const sf::Event& event)) {
  ObjectsWithKeyReleasedEvent.erase(this);
  KeyReleased = Func;
  if (Func != nullptr) {
    ObjectsWithKeyReleasedEvent.insert(this);
  }
}
void Object::SetMouseWheelScrolledEvent(void (* Func)(const sf::Event& event)) {
  ObjectsWithMouseWheelScrolledEvent.erase(this);
  MouseWheelScrolled = Func;
  if (Func != nullptr) {
    ObjectsWithMouseWheelScrolledEvent.insert(this);
  }
}
void Object::SetMouseButtonPressedEvent(void (* Func)(const sf::Event& event)) {
  ObjectsWithMouseButtonPressedEvent.erase(this);
  MouseButtonPressed = Func;
  if (Func != nullptr) {
    ObjectsWithMouseButtonPressedEvent.insert(this);
  }
}
void Object::SetMouseButtonReleasedEvent(void (* Func)(const sf::Event& event)) {
  ObjectsWithMouseButtonReleasedEvent.erase(this);
  MouseButtonReleased = Func;
  if (Func != nullptr) {
    ObjectsWithMouseButtonReleasedEvent.insert(this);
  }
}
void Object::SetMouseMovedEvent(void (* Func)(const sf::Event& event)) {
  ObjectsWithMouseMovedEvent.erase(this);
  MouseMoved = Func;
  if (Func != nullptr) {
    ObjectsWithMouseMovedEvent.insert(this);
  }
}
void Object::SetMouseEnteredEvent(void (* Func)(const sf::Event& event)) {
  ObjectsWithMouseEnteredEvent.erase(this);
  MouseEntered = Func;
  if (Func != nullptr) {
    ObjectsWithMouseEnteredEvent.insert(this);
  }
}
void Object::SetMouseLeftEvent(void (* Func)(const sf::Event& event)) {
  ObjectsWithMouseLeftEvent.erase(this);
  MouseLeft = Func;
  if (Func != nullptr) {
    ObjectsWithMouseLeftEvent.insert(this);
  }
}

void Object::Draw() {
  parent_->draw(Sprite_);
}


Button::Button(const sf::Texture& s1, const sf::Texture& s2, const sf::Texture& s3, sf::RenderWindow* parent = &window) : Object(parent), p1(s1), p2(s2), p3(s3) {
  Assign(p1);
  SetMouseButtonPressedEvent(nullptr);
  SetMouseButtonReleasedEvent(nullptr);
  SetMouseMovedEvent(nullptr);
  SetMouseEnteredEvent(nullptr);
  SetMouseLeftEvent(nullptr);
  sf::Vector2u parent_size = parent->getSize();
  sf::Vector2f sprite_size = static_cast<sf::Vector2f>(Sprite_.getTexture()->getSize());
  sf::Vector2f position(parent_size.x / 2 - sprite_size.x / 2, parent_size.y / 2 - sprite_size.y / 2);
  Sprite_.setPosition(position);
}
Button::Button(sf::Texture&& s1, sf::Texture&& s2, sf::Texture&& s3, sf::RenderWindow* parent = &window) : Object(parent), p1(s1), p2(s2), p3(s3) {
  Assign(p1);
  SetMouseButtonPressedEvent(nullptr);
  SetMouseButtonReleasedEvent(nullptr);
  SetMouseMovedEvent(nullptr);
  SetMouseEnteredEvent(nullptr);
  SetMouseLeftEvent(nullptr);
  sf::Vector2u parent_size = parent->getSize();
  sf::Vector2f sprite_size = static_cast<sf::Vector2f>(Sprite_.getTexture()->getSize());
  sf::Vector2f position(parent_size.x / 2 - sprite_size.x / 2, parent_size.y / 2 - sprite_size.y / 2);
  Sprite_.setPosition(position);
}
Button::Button(sf::Texture& s1, sf::Texture& s2, sf::Texture& s3, const sf::Text& text, const sf::Color& color, sf::RenderWindow* parent = &window) : Button(s1, s2, s3, parent) {
Print(text, color);
Assign(p1);
}
Button::Button(sf::Texture&& s1, sf::Texture&& s2, sf::Texture&& s3, const sf::Text& text, const sf::Color& color, sf::RenderWindow* parent = &window) : Button(std::move(s1), std::move(s2), std::move(s3), parent) {
Print(text, color);
Assign(p1);
}
void Button::Assign(const sf::Texture& texture) { Sprite_.setTexture(texture); }
void Button::SetMouseButtonPressedEvent(void (* Func)(const sf::Event& event)) {
  ObjectsWithMouseButtonPressedEvent.erase(this);
  if (Func != nullptr) {
    MouseButtonPressed = [this, Func](const sf::Event& event) {
      ButtonMouseButtonPressed();
      Func(event);
    };
  } else {
    MouseButtonPressed = [this, Func](const sf::Event& event) {
      ButtonMouseButtonPressed();
    };
  }
  ObjectsWithMouseButtonPressedEvent.insert(this);
}
void Button::SetMouseButtonReleasedEvent(void (* Func)(const sf::Event& event)) {
  ObjectsWithMouseButtonReleasedEvent.erase(this);
  if (Func != nullptr) {
    MouseButtonReleased = [this, Func](const sf::Event& event) {
      ButtonMouseButtonReleased();
      Func(event);
    };
  } else {
    MouseButtonReleased = [this, Func](const sf::Event& event) {
      ButtonMouseButtonReleased();
    };
  }
  ObjectsWithMouseButtonReleasedEvent.insert(this);
}
void Button::SetMouseMovedEvent(void (* Func)(const sf::Event& event)) {
  ObjectsWithMouseMovedEvent.erase(this);
  if (Func != nullptr) {
    MouseMoved = [this, Func](const sf::Event& event) {
      ButtonMouseMoved();
      Func(event);
    };
  } else {
    MouseMoved = [this, Func](const sf::Event& event) {
      ButtonMouseMoved();
    };
  }
  ObjectsWithMouseMovedEvent.insert(this);
}
void Button::SetMouseEnteredEvent(void (* Func)(const sf::Event& event)) {
  ObjectsWithMouseEnteredEvent.erase(this);
  if (Func != nullptr) {
    MouseEntered = [this, Func](const sf::Event& event) {
      ButtonMouseEntered();
      Func(event);
    };
  } else {
    MouseEntered = [this, Func](const sf::Event& event) {
      ButtonMouseEntered();
    };
  }
  ObjectsWithMouseEnteredEvent.insert(this);
}
void Button::SetMouseLeftEvent(void (* Func)(const sf::Event& event)) {
  ObjectsWithMouseLeftEvent.erase(this);
  if (Func != nullptr) {
    MouseLeft = [this, Func](const sf::Event& event) {
      ButtonMouseLeft();
      Func(event);
    };
  } else {
    MouseLeft = [this, Func](const sf::Event& event) {
      ButtonMouseLeft();
    };
  }
  ObjectsWithMouseLeftEvent.insert(this);
}

void Button::ButtonMouseEntered() {
  Assign(p2);
}
void Button::ButtonMouseLeft() {
  Assign(p1);
}
void Button::ButtonMouseButtonPressed() {
  Assign(p3);
}
void Button::ButtonMouseButtonReleased() {
  Assign(p1);
}
void Button::ButtonMouseMoved() {
  if(pressed_) {
    Assign(p3);
  } else {
    Assign(p2);
  }
}