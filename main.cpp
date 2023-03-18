#include <ctime>
#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

//#include "Global_Classes.h"
#include "Global_Variables.h"

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
      case sf::Event::KeyPressed:
      case sf::Event::KeyReleased:
      case sf::Event::MouseWheelScrolled:
      case sf::Event::MouseButtonPressed:
      case sf::Event::MouseButtonReleased:
      case sf::Event::MouseMoved:
      case sf::Event::MouseEntered:
      case sf::Event::MouseLeft:
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
