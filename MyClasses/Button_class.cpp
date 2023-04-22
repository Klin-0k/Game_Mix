Button::Button(const sf::Texture& s1,
               const sf::Texture& s2,
               const sf::Texture& s3,
               Window* parent = MainWindow,
               bool is_independent = true) : Object(parent, is_independent),
                                             p1(s1),
                                             p2(s2),
                                             p3(s3) {
  AssignMyTexture(p1);
  SetMouseButtonPressedEvent(nullptr);
  SetMouseButtonReleasedEvent(nullptr);
  SetMouseMovedEvent(nullptr);
  SetMouseEnteredEvent(nullptr);
  SetMouseLeftEvent(nullptr);
  sf::Vector2u parent_size = parent->getSize();
  sf::Vector2f sprite_size = static_cast<sf::Vector2f>(Sprite_.getTexture()->getSize());
  sf::Vector2f
      position(parent_size.x / 2 - sprite_size.x / 2, parent_size.y / 2 - sprite_size.y / 2);
  Sprite_.setPosition(position);
}
Button::Button(const std::string& s1,
               const std::string& s2,
               const std::string& s3,
               Window* parent = MainWindow,
               bool is_independent = true) : Object(parent, is_independent) {
  p1.loadFromFile(s1);
  p2.loadFromFile(s2);
  p3.loadFromFile(s3);
  AssignMyTexture(p1);
  SetMouseButtonPressedEvent(nullptr);
  SetMouseButtonReleasedEvent(nullptr);
  SetMouseMovedEvent(nullptr);
  SetMouseEnteredEvent(nullptr);
  SetMouseLeftEvent(nullptr);
  sf::Vector2u parent_size = parent->getSize();
  sf::Vector2f sprite_size = static_cast<sf::Vector2f>(Sprite_.getTexture()->getSize());
  sf::Vector2f
      position(parent_size.x / 2 - sprite_size.x / 2, parent_size.y / 2 - sprite_size.y / 2);
  Sprite_.setPosition(position);
}
Button::Button(sf::Texture&& s1,
               sf::Texture&& s2,
               sf::Texture&& s3,
               Window* parent = MainWindow,
               bool is_independent = true) : Object(parent, is_independent),
                                             p1(s1),
                                             p2(s2),
                                             p3(s3) {
  AssignMyTexture(p1);
  SetMouseButtonPressedEvent(nullptr);
  SetMouseButtonReleasedEvent(nullptr);
  SetMouseMovedEvent(nullptr);
  SetMouseEnteredEvent(nullptr);
  SetMouseLeftEvent(nullptr);
  sf::Vector2u parent_size = parent->getSize();
  sf::Vector2f sprite_size = static_cast<sf::Vector2f>(Sprite_.getTexture()->getSize());
  sf::Vector2f
      position(parent_size.x / 2 - sprite_size.x / 2, parent_size.y / 2 - sprite_size.y / 2);
  Sprite_.setPosition(position);
}
Button::Button(sf::Texture& s1,
               sf::Texture& s2,
               sf::Texture& s3,
               const sf::Text& text,
               Window* parent = MainWindow,
               bool is_independent = true) : Button(s1, s2, s3, parent, is_independent) {
  Print(text);
  AssignMyTexture(p1);
}
Button::Button(sf::Texture&& s1,
               sf::Texture&& s2,
               sf::Texture&& s3,
               const sf::Text& text,
               Window* parent = MainWindow,
               bool is_independent = true) : Button(std::move(s1),
                                                    std::move(s2),
                                                    std::move(s3),
                                                    parent, is_independent) {
  Print(text);
  AssignMyTexture(p1);
}
Button::~Button() {
#ifdef DEBAG
  std::cout << "~Button\n";
#endif
}
void Button::Print(sf::Text text, sf::Texture& texture) {
  sf::RenderTexture rt;
  rt.create(texture.getSize().x, texture.getSize().y);
  rt.clear(sf::Color::Transparent);
  rt.draw(sf::Sprite(texture));
  sf::FloatRect textRect = text.getLocalBounds();
  text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
  text.setPosition(sf::Vector2f(rt.getSize().x / 2.0f, rt.getSize().y / 2.0f));
  rt.draw(text);
  rt.display();
  texture.update(rt.getTexture());
//  static int counter;
//  sf::Image screenshot;
//  screenshot.create(rt.getSize().x, rt.getSize().y);
//  screenshot.copy(rt.getTexture().copyToImage(), 0, 0);
//  screenshot.saveToFile("button_"+std::to_string(counter)+".png");
//  ++counter;
}
void Button::Print(const sf::Text& text) {
  Print(text, p1);
  Print(text, p2);
  Print(text, p3);
}
void Button::SetEnableMod(bool enable) {
  enable_ = enable;
  if (enable_ && !visible_) {
    SetVisibleMod(true);
  }
  if (!enable_) {
    AssignMyTexture(p1);
    pressed_ = false;
    under_mouse_ = false;
  }
}
void Button::SetMouseButtonPressedEvent(const std::function<void(const sf::Event&)>& Func) {
  if (Func != nullptr) {
    MouseButtonPressed = [this, Func](const sf::Event& event) {
      ButtonMouseButtonPressed();
      Func(event);
    };
  } else {
    MouseButtonPressed = [this](const sf::Event& event) {
      ButtonMouseButtonPressed();
    };
  }
  parent_->ObjectsWithMouseButtonPressedEvent.insert(this);
}
void Button::SetMouseButtonReleasedEvent(const std::function<void(const sf::Event&)>& Func) {
  if (Func != nullptr) {
    MouseButtonReleased = [this, Func](const sf::Event& event) {
      ButtonMouseButtonReleased();
      if (under_mouse_) {
        Func(event);
      }
    };
  } else {
    MouseButtonReleased = [this](const sf::Event& event) {
      ButtonMouseButtonReleased();
    };
  }
  parent_->ObjectsWithMouseButtonReleasedEvent.insert(this);
}
void Button::SetMouseMovedEvent(const std::function<void(const sf::Event&)>& Func) {
  if (Func != nullptr) {
    MouseMoved = [this, Func](const sf::Event& event) {
      ButtonMouseMoved();
      Func(event);
    };
  } else {
    MouseMoved = [this](const sf::Event& event) {
      ButtonMouseMoved();
    };
  }
  parent_->ObjectsWithMouseMovedEvent.insert(this);
}
void Button::SetMouseEnteredEvent(const std::function<void(const sf::Event&)>& Func) {
  if (Func != nullptr) {
    MouseEntered = [this, Func](const sf::Event& event) {
      ButtonMouseEntered();
      Func(event);
    };
  } else {
    MouseEntered = [this](const sf::Event& event) {
      ButtonMouseEntered();
    };
  }
  parent_->ObjectsWithMouseMovedEvent.insert(this);
}
void Button::SetMouseLeftEvent(const std::function<void(const sf::Event&)>& Func) {
  if (Func != nullptr) {
    MouseLeft = [this, Func](const sf::Event& event) {
      ButtonMouseLeft();
      Func(event);
    };
  } else {
    MouseLeft = [this](const sf::Event& event) {
      ButtonMouseLeft();
    };
  }
  parent_->ObjectsWithMouseMovedEvent.insert(this);
}

void Button::ButtonMouseEntered() {
  AssignMyTexture(p2);
}
void Button::ButtonMouseLeft() {
  if (!pressed_) {
    AssignMyTexture(p1);
  }
}
void Button::ButtonMouseButtonPressed() {
  AssignMyTexture(p3);
}
void Button::ButtonMouseButtonReleased() {
  if (!under_mouse_) {
    AssignMyTexture(p1);
  } else {
    AssignMyTexture(p2);
  }
}
void Button::ButtonMouseMoved() {
  if (pressed_) {
    AssignMyTexture(p3);
  } else {
    AssignMyTexture(p2);
  }
}

