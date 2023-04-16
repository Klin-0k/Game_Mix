Essence::Essence(Window* parent, bool is_independent = true) : parent_(parent), is_independent_(is_independent) {
  if (is_independent) {
    parent_->EssencesToDraw.insert(this);
    parent_->AllEssences.insert(this);
  }
}
Essence::Essence(bool is_independent) : Essence(MainWindow, is_independent) {}
Essence::Essence() : Essence(true) {}
Essence::Essence(const Essence& other) = default;
Essence& Essence::operator=(const Essence& other) = default;
Essence::~Essence() {
  parent_->EssencesWithTextEnteredEvent.erase(this);
  parent_->EssencesWithKeyPressedEvent.erase(this);
  parent_->EssencesWithKeyReleasedEvent.erase(this);
  parent_->EssencesToDraw.erase(this);
  parent_->AllEssences.erase(this);
#ifdef DEBAG
  std::cout << "~Essence\n\n";
#endif
}
void  Essence::SetEnableMod(bool enable) {
  enable_ = enable;
  if (enable_ && !visible_) {
    visible_ = true;
  }
}
void  Essence::SetVisibleMod(bool visible) {
  visible_ = visible;
  if (enable_ && !visible_) {
    enable_ = false;
  }
}
bool Essence::GetEnableMod() const {
  return enable_;
}
bool Essence::GetVisibleMod() const {
  return visible_;
}
const Window* Essence::parent() {
  return parent_;
}
void Essence::SetTextEnteredEvent(const std::function<void(const sf::Event&)>& Func) {
  parent_->EssencesWithTextEnteredEvent.erase(this);
  TextEntered = Func;
  if (Func != nullptr) {
    parent_->EssencesWithTextEnteredEvent.insert(this);
  }
}
void Essence::SetKeyPressedEvent(const std::function<void(const sf::Event&)>& Func) {
  parent_->EssencesWithKeyPressedEvent.erase(this);
  KeyPressed = Func;
  if (Func != nullptr) {
    parent_->EssencesWithKeyPressedEvent.insert(this);
  }
}
void Essence::SetKeyReleasedEvent(const std::function<void(const sf::Event&)>& Func) {
  parent_->EssencesWithKeyReleasedEvent.erase(this);
  KeyReleased = Func;
  if (Func != nullptr) {
    parent_->EssencesWithKeyReleasedEvent.insert(this);
  }
}
void Essence::Draw() {}

void Essence::Delete() {
  SetEnableMod(false);
  SetVisibleMod(false);
  parent_->EssencesToDelete.insert(this);
}