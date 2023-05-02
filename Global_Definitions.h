#pragma once

#include <ctime>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>


#include "Global_Classes.h"

std::unordered_set<Window*> Window::WindowsToDisplay = std::unordered_set<Window*>();
bool Window::WaitingForProgramClosing = false;
std::unordered_set<Window*> ExitMenu::WindowsWithOpenExit = std::unordered_set<Window*>();
MainMenu* MainMenu::pmm = nullptr;
PlayMenu* PlayMenu::ppm = nullptr;
Window* MainWindow = nullptr;
//sf::BlendMode blendMode;

void GettingStarted() {
  MainWindow = new Window(sf::VideoMode(sf::VideoMode::getDesktopMode().height * 3 / 4 * 16 / 9,
                                        sf::VideoMode::getDesktopMode().height * 3 / 4), "Casino");
  MainWindow->setPosition({static_cast<int>(
                               (sf::VideoMode::getDesktopMode().width - MainWindow->getSize().x)
                                   / 2), static_cast<int>(
                               (sf::VideoMode::getDesktopMode().height - MainWindow->getSize().y)
                                   / 2)});
  Window::WindowsToDisplay.insert(MainWindow);
  MainWindow->Close = [] { ExitMenu::CloseWithExitMenu(MainWindow); };
  MainMenu::getMainMenu();
  sf::Image window_icon;
  window_icon.loadFromFile(PATH_TO_PROJECT_FILES"/Resources/icons/main_icon.png");
  MainWindow->setIcon(1024, 1024, window_icon.getPixelsPtr());
  MainWindow->setVerticalSyncEnabled(true);
//  blendMode.colorSrcFactor = sf::BlendMode::SrcAlpha;
//  blendMode.colorDstFactor = sf::BlendMode::OneMinusSrcAlpha;
//  blendMode.colorEquation = sf::BlendMode::Add;
#ifdef DEBAG
  MainWindow->Name = "MainWindow";
#endif
}