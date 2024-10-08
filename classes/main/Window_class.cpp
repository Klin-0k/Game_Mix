#include <classes/main/Essence_class.h>
#include <classes/main/Object_class.h>
#include <classes/main/Window_class.h>

std::unordered_set<Window*> Window::WindowsToDisplay = std::unordered_set<Window*>();
bool Window::WaitingForProgramClosing = false;

void Window::Delete() {
  SetEnableMod(false);
  WaitingForDeleting = true;
}
void Window::CloseProgram() {
  WaitingForProgramClosing = true;
}
bool Window::IsWaitingForDeleting() const {
  return WaitingForDeleting;
}
bool Window::ProgramIsWaitingForClosing() {
  return WaitingForProgramClosing;
}
void Window::EventHandling(const sf::Event& event) {
  switch (event.type) {
    case sf::Event::Closed:
      Close();
      break;
    case sf::Event::Resized: break;
    case sf::Event::LostFocus: break;
    case sf::Event::GainedFocus: break;
    case sf::Event::TextEntered:
      for (auto i : EssencesWithTextEnteredEvent) {
        if (i->enable_) {
          i->TextEntered_(event);
          if (WaitingForDeleting || WaitingForProgramClosing) {
            break;
          }
          if (!enable_) {
            break;
          }
        }
      }
      break;
    case sf::Event::KeyPressed:
      for (auto i : EssencesWithKeyPressedEvent) {
        if (i->enable_) {
          i->KeyPressed_(event);
          if (WaitingForDeleting || WaitingForProgramClosing) {
            break;
          }
          if (!enable_) {
            break;
          }
        }
      }
      break;
    case sf::Event::KeyReleased:
      for (auto i : EssencesWithKeyReleasedEvent) {
        if (i->enable_) {
          i->KeyReleased_(event);
          if (WaitingForDeleting || WaitingForProgramClosing) {
            break;
          }
          if (!enable_) {
            break;
          }
        }
      }
      break;
    case sf::Event::MouseWheelScrolled:
      for (auto i : ObjectsWithMouseWheelScrolledEvent) {
        if (i->enable_) {
          i->MouseWheelScrolled_(event);
          if (WaitingForDeleting || WaitingForProgramClosing) {
            break;
          }
          if (!enable_) {
            break;
          }
        }
      }
      break;
    case sf::Event::MouseButtonPressed:
      for (auto i : ObjectsWithMouseButtonPressedEvent) {
        if (i->enable_) {
          if (i->Sprite_.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            i->pressed_ = true;
            i->MouseButtonPressed_(event);
          }
          if (WaitingForDeleting || WaitingForProgramClosing) {
            break;
          }
          if (!enable_) {
            break;
          }
        }
      }
      break;
    case sf::Event::MouseButtonReleased:
      for (auto i : ObjectsWithMouseButtonReleasedEvent) {
        if (i->enable_) {
          if (i->pressed_) {
            i->MouseButtonReleased_(event);
            i->pressed_ = false;
          }
          if (WaitingForDeleting || WaitingForProgramClosing) {
            break;
          }
          if (!enable_) {
            break;
          }
        }
      }
      break;
    case sf::Event::MouseMoved:
      for (auto i : ObjectsWithMouseMovedEvent) {
        if (i->enable_) {
          if (i->under_mouse_
              && i->Sprite_.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
            i->MouseMoved_(event);
          }
          if (WaitingForDeleting || WaitingForProgramClosing) {
            break;
          }
          if (!enable_) {
            break;
          }
        }
        if (i->enable_) {
          if (i->under_mouse_
              && !(i->Sprite_.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))) {
            i->MouseLeft_(event);
            i->under_mouse_ = false;
          }
          if (WaitingForDeleting || WaitingForProgramClosing) {
            break;
          }
          if (!enable_) {
            break;
          }
        }
        if (i->enable_) {
          if (!i->under_mouse_
              && i->Sprite_.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
            i->under_mouse_ = true;
            i->MouseEntered_(event);
          }
          if (WaitingForDeleting || WaitingForProgramClosing) {
            break;
          }
          if (!enable_) {
            break;
          }
        }
      }
      break;
    default: break;
  }
}
void Window::UpdatingEssences(double dt) {
  if (!WaitingForDeleting && !WaitingForProgramClosing) {
    for (auto i : EssencesWithUpdate) {
      if (i->enable_) {
        i->Update_(dt);
        if (WaitingForDeleting || WaitingForProgramClosing) {
          break;
        }
        if (!enable_) {
          break;
        }
      }
    }
  }
}
void Window::ChangingEssencesStates() {
  for (auto i : EssencesToDelete) {
    delete i;
  }
  EssencesToDelete.clear();
}
void Window::MakeFrame() {
  double dt = time_between_frames.restart().asMilliseconds();
  if (enable_) {
    sf::Event event = sf::Event();
    if (pollEvent(event)) {
      EventHandling(event);
    }
  }
  if (enable_) {
    UpdatingEssences(dt);
  }
  ChangingEssencesStates();
  if (WaitingForDeleting || WaitingForProgramClosing) {
    return;
  }
  clear(sf::Color::Transparent);
  for (auto i : EssencesToDraw) {
    if (i->visible_) {
      i->Draw();
    }
  }
  display();
  if (IsAlwaysOnFocus) {
    requestFocus();
  }
}
void Window::SetEnableMod(bool enable) {
  if (!enable_ && enable) {
    for (auto i : EssencesToDraw) {
      i->SetEnableMod(true);
    }
  }
  if (enable_ && !enable) {
    for (auto i : EssencesToDraw) {
      i->SetEnableMod(false);
    }
  }
  enable_ = enable;
  time_between_frames.restart();
}
void Window::SetVisibleMod(bool visible) {
  //todo or not todo, this is the question
}
bool Window::GetEnableMod() const {
  return enable_;
}
bool Window::GetVisibleMod() const {
  return visible_;
}
Window::~Window() {
  while (!AllEssences.empty()) {
    delete *AllEssences.begin();
  }
#ifdef DEBUG
  std::cout << '~' << Name << "\n\n";
#endif
}