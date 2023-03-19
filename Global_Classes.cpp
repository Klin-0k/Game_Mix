#include "Global_Classes.h"

bool& Object::enable() {
  return enable_;
}
bool& Object::visible() {
  return visible_;
}
const sf::RenderWindow& Object::parent() {
  return parent_;
}
void Object::SetTextEnteredEvent(void (*Func)()) {
  ObjectsWithTextEnteredEvent.erase(this);
  TextEntered = Func;
  if (Func != nullptr) {
    ObjectsWithTextEnteredEvent.insert(this);
  }
}
void Object::SetKeyPressedEvent(void (*Func)()) {
  ObjectsWithKeyPressedEvent.erase(this);
  KeyPressed = Func;
  if (Func != nullptr) {
    ObjectsWithKeyPressedEvent.insert(this);
  }
}
void Object::SetKeyReleasedEvent(void (*Func)()) {
  ObjectsWithKeyReleasedEvent.erase(this);
  KeyReleased = Func;
  if (Func != nullptr) {
    ObjectsWithKeyReleasedEvent.insert(this);
  }
}
void Object::SetMouseWheelScrolledEvent(void (*Func)()) {
  ObjectsWithMouseWheelScrolledEvent.erase(this);
  MouseWheelScrolled = Func;
  if (Func != nullptr) {
    ObjectsWithMouseWheelScrolledEvent.insert(this);
  }
}
void Object::SetMouseButtonPressedEvent(void (*Func)()) {
  ObjectsWithMouseButtonPressedEvent.erase(this);
  MouseButtonPressed = Func;
  if (Func != nullptr) {
    ObjectsWithMouseButtonPressedEvent.insert(this);
  }
}
void Object::SetMouseButtonReleasedEvent(void (*Func)()) {
  ObjectsWithMouseButtonReleasedEvent.erase(this);
  MouseButtonReleased = Func;
  if (Func != nullptr) {
    ObjectsWithMouseButtonReleasedEvent.insert(this);
  }
}
void Object::SetMouseMovedEvent(void (*Func)()) {
  ObjectsWithMouseMovedEvent.erase(this);
  MouseMoved = Func;
  if (Func != nullptr) {
    ObjectsWithMouseMovedEvent.insert(this);
  }
}
void Object::SetMouseEnteredEvent(void (*Func)()) {
  ObjectsWithMouseEnteredEvent.erase(this);
  MouseEntered = Func;
  if (Func != nullptr) {
    ObjectsWithMouseEnteredEvent.insert(this);
  }
}
void Object::SetMouseLeftEvent(void (*Func)()) {
  ObjectsWithMouseLeftEvent.erase(this);
  MouseLeft = Func;
  if (Func != nullptr) {
    ObjectsWithMouseLeftEvent.insert(this);
  }
}
