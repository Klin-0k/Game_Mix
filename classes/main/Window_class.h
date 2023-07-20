#pragma once

#include <functional>
#include <unordered_set>

#include <SFML/Graphics.hpp>

#include <classes/main/fwd.h>

class Window : public sf::RenderWindow {
 public:
  void Delete();
  bool IsWaitingForDeleting() const;
  static bool ProgramIsWaitingForClosing();
  void SetEnableMod(bool enable);
  void SetVisibleMod(bool visible);
  [[nodiscard]] bool GetEnableMod() const;
  [[nodiscard]] bool GetVisibleMod() const;
  void MakeFrame();
  using SFML_window = sf::RenderWindow;
  using SFML_window::SFML_window;
  ~Window() override;
  std::function<void()> Close = [this]() { Delete(); };
  bool IsAlwaysOnFocus = false;
  static void CloseProgram();
  //  template<sf::Event::EventType Type>
  //  using SetOfHandleable = std::unordered_set<Handleable<Type> >;
  std::unordered_set<Essence*> EssencesWithTextEnteredEvent = std::unordered_set<Essence*>();
  std::unordered_set<Essence*> EssencesWithKeyPressedEvent = std::unordered_set<Essence*>();
  std::unordered_set<Essence*> EssencesWithKeyReleasedEvent = std::unordered_set<Essence*>();
  std::unordered_set<Object*> ObjectsWithMouseWheelScrolledEvent = std::unordered_set<Object*>();
  std::unordered_set<Object*> ObjectsWithMouseButtonPressedEvent = std::unordered_set<Object*>();
  std::unordered_set<Object*> ObjectsWithMouseButtonReleasedEvent = std::unordered_set<Object*>();
  std::unordered_set<Object*> ObjectsWithMouseMovedEvent = std::unordered_set<Object*>();
  std::unordered_set<Essence*> EssencesToDraw = std::unordered_set<Essence*>();
  std::unordered_set<Essence*> EssencesWithUpdate = std::unordered_set<Essence*>();
  std::unordered_set<Essence*> EssencesToDelete = std::unordered_set<Essence*>();
  std::unordered_set<Essence*> AllEssences = std::unordered_set<Essence*>();
  static std::unordered_set<Window*> WindowsToDisplay;
#ifdef DEBUG
  std::string Name = "Window";
#endif

 protected:
  void EventHandling(const sf::Event& event);
  void UpdatingEssences(double dt);
  void ChangingEssencesStates();
  bool enable_ = true;
  bool visible_ = true;
  bool WaitingForDeleting = false;
  static bool WaitingForProgramClosing;
  sf::Clock time_between_frames;
};

extern Window* MainWindow;