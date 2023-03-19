#pragma once

#include <ctime>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>


#include "Global_Classes.h"

sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getFullscreenModes()[2]), "Casino");

bool program_is_ending = false;

std::unordered_set<Object*> ObjectsWithTextEnteredEvent = std::unordered_set<Object*>();
std::unordered_set<Object*> ObjectsWithKeyPressedEvent = std::unordered_set<Object*>();
std::unordered_set<Object*> ObjectsWithKeyReleasedEvent = std::unordered_set<Object*>();
std::unordered_set<Object*> ObjectsWithMouseWheelScrolledEvent = std::unordered_set<Object*>();
std::unordered_set<Object*> ObjectsWithMouseButtonPressedEvent = std::unordered_set<Object*>();
std::unordered_set<Object*> ObjectsWithMouseButtonReleasedEvent = std::unordered_set<Object*>();
std::unordered_set<Object*> ObjectsWithMouseMovedEvent = std::unordered_set<Object*>();
std::unordered_set<Object*> ObjectsWithMouseEnteredEvent = std::unordered_set<Object*>();
std::unordered_set<Object*> ObjectsWithMouseLeftEvent = std::unordered_set<Object*>();
std::unordered_set<Object*> ObjectsToDraw = std::unordered_set<Object*>();