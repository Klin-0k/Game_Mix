#include <ctime>
#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Global_Classes.cpp"

void testf() {
  sf::Color color(rand() % 256, rand() % 256, rand() % 256);
  window.clear(color);
}

void GettingStarted() {
    sf::Image window_icon;
    window_icon.loadFromFile("../Resources/icon.png");
    window.setIcon(1024, 1024, window_icon.getPixelsPtr());
    //window.setFramerateLimit(120);
    //test.SetMouseButtonPressedEvent(testf);
}
void EventHandling() {
  sf::Event event;
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
          i->TextEntered();
        }
        break;
      case sf::Event::KeyPressed:
        for (auto i : ObjectsWithKeyPressedEvent) {
          i->KeyPressed();
        }
        break;
      case sf::Event::KeyReleased:
        for (auto i : ObjectsWithKeyReleasedEvent) {
          i->KeyReleased();
        }
        break;
      case sf::Event::MouseWheelScrolled:
        for (auto i : ObjectsWithMouseWheelScrolledEvent) {
          i->MouseWheelScrolled();
        }
        break;
      case sf::Event::MouseButtonPressed:
        for (auto i : ObjectsWithMouseButtonPressedEvent) {
          i->MouseButtonPressed();
          //std::cout << "I was here\n";
        }
        break;
      case sf::Event::MouseButtonReleased:
        for (auto i : ObjectsWithMouseButtonReleasedEvent) {
          i->MouseButtonReleased();
        }
        break;
      case sf::Event::MouseMoved:
        for (auto i : ObjectsWithMouseMovedEvent) {
          i->MouseMoved();
        }
        break;
      case sf::Event::MouseEntered:
        for (auto i : ObjectsWithMouseEnteredEvent) {
          i->MouseEntered();
        }
        break;
      case sf::Event::MouseLeft:
        for (auto i : ObjectsWithMouseLeftEvent) {
          i->MouseLeft();
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
    if (program_is_ending) {
      break;
    }
    for (auto i : ObjectsToDraw) {
      i->Draw();
    }
    window.display();
  }
  return 0;
}
