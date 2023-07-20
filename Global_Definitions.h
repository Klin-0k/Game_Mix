#pragma once

#include <ctime>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <classes/MainComp.h>
#include <classes/Menus.h>

Window* MainWindow = nullptr;
//sf::BlendMode blendMode;

void GettingStarted() {
  MainWindow = new Window(sf::VideoMode(sf::VideoMode::getDesktopMode().height * 3 / 4 * 16 / 9,
                                        sf::VideoMode::getDesktopMode().height * 3 / 4),
                          "Casino");
  MainWindow->setPosition({0, 0});
  Window::WindowsToDisplay.insert(MainWindow);
  //  MainWindow->Close = [] { ExitMenu::CloseWithExitMenu(MainWindow); };
  MainMenu::getMainMenu();
  sf::Image window_icon;
  window_icon.loadFromFile(PATH_TO_RESOURCES "/icons/main_icon.png");
  MainWindow->setIcon(1024, 1024, window_icon.getPixelsPtr());
  MainWindow->setVerticalSyncEnabled(true);
//  blendMode.colorSrcFactor = sf::BlendMode::SrcAlpha;
//  blendMode.colorDstFactor = sf::BlendMode::OneMinusSrcAlpha;
//  blendMode.colorEquation = sf::BlendMode::Add;
#ifdef DEBAG
  MainWindow->Name = "MainWindow";
#endif
}