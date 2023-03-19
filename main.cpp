#include <ctime>
#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Global_Classes.h"
#include "Global_Variables.h"

void GettingStarted() {
    sf::Image window_icon;
    window_icon.loadFromFile("../Resources/icon.png");
    window.setIcon(1024, 1024, window_icon.getPixelsPtr());
};
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
          (*i).KeyPressed();
        }
      case sf::Event::KeyPressed:
        for (auto i : ObjectsWithKeyPressedEvent) {
          (*i).KeyPressed();
        }
      case sf::Event::KeyReleased:
        for (auto i : ObjectsWithKeyReleasedEvent) {
          (*i).KeyPressed();
        }
      case sf::Event::MouseWheelScrolled:
        for (auto i : ObjectsWithMouseWheelScrolledEvent) {
          (*i).KeyPressed();
        }
      case sf::Event::MouseButtonPressed:
        for (auto i : ObjectsWithMouseButtonPressedEvent) {
          (*i).KeyPressed();
        }
      case sf::Event::MouseButtonReleased:
        for (auto i : ObjectsWithMouseButtonReleasedEvent) {
          (*i).KeyPressed();
        }
      case sf::Event::MouseMoved:
        for (auto i : ObjectsWithMouseMovedEvent) {
          (*i).KeyPressed();
        }
      case sf::Event::MouseEntered:
        for (auto i : ObjectsWithMouseEnteredEvent) {
          (*i).KeyPressed();
        }
      case sf::Event::MouseLeft:
        for (auto i : ObjectsWithMouseLeftEvent) {
          (*i).KeyPressed();
        }
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
  sf::Color color(255, 0, 0);
  while (true) {
    EventHandling();
    if (program_is_ending) {
      break;
    }
    color.r = (color.r + 1) % 256;
    color.g = (color.g + 2) % 256;
    color.b = (color.b + 3) % 256;
    window.clear(color);
    window.display();
  }
  return 0;
}
