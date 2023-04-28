#include <ctime>
#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Global_Classes.cpp"

sf::Color color = sf::Color();
void testf(const sf::Event& event) {
  color = sf::Color (rand() % 256, rand() % 256, rand() % 256);
}
Button* test;
void GettingStarted() {
  sf::Texture i1;
  sf::Texture i2;
  sf::Texture i3;
  i1.loadFromFile(PATH_TO_PROJECT_FILES"/Resources/buttons/buttonP1.png");
  i2.loadFromFile(PATH_TO_PROJECT_FILES"/Resources/buttons/buttonP2.png");
  i3.loadFromFile(PATH_TO_PROJECT_FILES"/Resources/buttons/buttonP3.png");
  test = new Button(i1, i2, i3);
  test->SetMouseEnteredEvent(testf);
  sf::Image window_icon;
  window_icon.loadFromFile(PATH_TO_PROJECT_FILES"/Resources/icon.png");
  window.setIcon(1024, 1024, window_icon.getPixelsPtr());
  window.setVerticalSyncEnabled(true);
  //window.setFramerateLimit(120);
  test->SetMouseButtonPressedEvent(testf);
}
void EventHandling() {
  sf::Event event = sf::Event();
  while (window.pollEvent(event))
  {
    switch (event.type)
    {
      case sf::Event::Closed:
        window.close();
        program_is_ending = true;
        break;
      case sf::Event::Resized:
      case sf::Event::LostFocus:
      case sf::Event::GainedFocus:
      case sf::Event::TextEntered:
        for (auto i : ObjectsWithTextEnteredEvent) {
          i->TextEntered(event);
        }
        break;
      case sf::Event::KeyPressed:
        for (auto i : ObjectsWithKeyPressedEvent) {
          i->KeyPressed(event);
        }
        break;
      case sf::Event::KeyReleased:
        for (auto i : ObjectsWithKeyReleasedEvent) {
          i->KeyReleased(event);
        }
        break;
      case sf::Event::MouseWheelScrolled:
        for (auto i : ObjectsWithMouseWheelScrolledEvent) {
          i->MouseWheelScrolled(event);
        }
        break;
      case sf::Event::MouseButtonPressed:
        for (auto i : ObjectsWithMouseButtonPressedEvent) {
          if(i->Sprite_.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            i->pressed_ = true;
            i->MouseButtonPressed(event);
            //std::cout << "I was here\n";
          }
        }
        break;
      case sf::Event::MouseButtonReleased:
        for (auto i : ObjectsWithMouseButtonReleasedEvent) {
          if(i->pressed_) {
            i->MouseButtonReleased(event);
            i->pressed_ = false;
          }
        }
        break;
      case sf::Event::MouseMoved:
        for (auto i : ObjectsWithMouseMovedEvent) {
          if(i->under_mouse_ && i->Sprite_.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            i->MouseMoved(event);
          }
          if(i->under_mouse_ && !(i->Sprite_.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))) {
            i->MouseLeft(event);
            i->under_mouse_ = false;
          }
          if(!i->under_mouse_ && i->Sprite_.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            i->under_mouse_ = true;
            i->MouseEntered(event);
          }
        }
        break;
      case sf::Event::MouseEntered:
        for (auto i : ObjectsWithMouseEnteredEvent) {

        }
        break;
      case sf::Event::MouseLeft:
        for (auto i : ObjectsWithMouseLeftEvent) {

        }
        break;
      case sf::Event::JoystickButtonPressed:
      case sf::Event::JoystickButtonReleased:
      case sf::Event::JoystickMoved:
      case sf::Event::JoystickConnected:
      case sf::Event::JoystickDisconnected:
      case sf::Event::TouchBegan:
      case sf::Event::TouchMoved:
      case sf::Event::TouchEnded:
      case sf::Event::SensorChanged:
      case sf::Event::Count:
      default: break;
    }
  }
}

int main() {
  GettingStarted();
  while (true) {
    EventHandling();
    window.clear(color);
    if (program_is_ending) {
      for (auto i : AllObjects) {
        delete i;
      }
      break;
    }
    for (auto i : ObjectsToDraw) {
      i->Draw();
    }
    window.display();
//    window.setActive(false);
//    window.setActive(true);
  }
  return 0;
}
