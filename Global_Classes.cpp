#include "Global_Variables.h"

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
bool Object::GetEnableMod() {
  return enable_;
}
bool Object::GetVisibleMod() {
  return visible_;
}
const sf::RenderWindow& Object::parent() {
  return parent_;
}
void Object::SetTextEnteredEvent(void (* Func)()) {
  ObjectsWithTextEnteredEvent.erase(this);
  TextEntered = Func;
  if (Func != nullptr) {
    ObjectsWithTextEnteredEvent.insert(this);
  }
}
void Object::SetKeyPressedEvent(void (* Func)()) {
  ObjectsWithKeyPressedEvent.erase(this);
  KeyPressed = Func;
  if (Func != nullptr) {
    ObjectsWithKeyPressedEvent.insert(this);
  }
}
void Object::SetKeyReleasedEvent(void (* Func)()) {
  ObjectsWithKeyReleasedEvent.erase(this);
  KeyReleased = Func;
  if (Func != nullptr) {
    ObjectsWithKeyReleasedEvent.insert(this);
  }
}
void Object::SetMouseWheelScrolledEvent(void (* Func)()) {
  ObjectsWithMouseWheelScrolledEvent.erase(this);
  MouseWheelScrolled = Func;
  if (Func != nullptr) {
    ObjectsWithMouseWheelScrolledEvent.insert(this);
  }
}
void Object::SetMouseButtonPressedEvent(void (* Func)()) {
  ObjectsWithMouseButtonPressedEvent.erase(this);
  MouseButtonPressed = Func;
  if (Func != nullptr) {
    ObjectsWithMouseButtonPressedEvent.insert(this);
  }
}
void Object::SetMouseButtonReleasedEvent(void (* Func)()) {
  ObjectsWithMouseButtonReleasedEvent.erase(this);
  MouseButtonReleased = Func;
  if (Func != nullptr) {
    ObjectsWithMouseButtonReleasedEvent.insert(this);
  }
}
void Object::SetMouseMovedEvent(void (* Func)()) {
  ObjectsWithMouseMovedEvent.erase(this);
  MouseMoved = Func;
  if (Func != nullptr) {
    ObjectsWithMouseMovedEvent.insert(this);
  }
}
void Object::SetMouseEnteredEvent(void (* Func)()) {
  ObjectsWithMouseEnteredEvent.erase(this);
  MouseEntered = Func;
  if (Func != nullptr) {
    ObjectsWithMouseEnteredEvent.insert(this);
  }
}
void Object::SetMouseLeftEvent(void (* Func)()) {
  ObjectsWithMouseLeftEvent.erase(this);
  MouseLeft = Func;
  if (Func != nullptr) {
    ObjectsWithMouseLeftEvent.insert(this);
  }
}

void Object::Draw() {
  parent_.draw(Sprite_);
}