#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

//----------------------------------------------------------

class Window;
class Essence;
class Object;
class Button;
class Fon;
class MainMenu;
class PlayMenu;
class ExitMenu;
class Settings;
class Profile;
class User;
class BigBoy;
class Game;
class InGameMenu;

class Window final : public sf::RenderWindow {
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
  ~Window() final;
  std::function<void()> Close = [this]() { Delete(); };
  bool IsAlwaysOnFocus = false;
  static void CloseProgram();
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
#ifdef DEBAG
  std::string Name = "Window";
#endif

private:
  void EventHandling();
  void UpdatingEssences(double dt);
  void ChangingEssencesStates();
  bool enable_ = true;
  bool visible_ = true;
  bool WaitingForDeleting = false;
  static bool WaitingForProgramClosing;
  sf::Clock time_between_frames;
};

class Essence {
public:
  Essence(Window* parent, bool is_independent);
  explicit Essence(bool is_independent);
  Essence();
  Essence(const Essence& other);
  Essence& operator=(const Essence& other);
  virtual ~Essence();
  virtual void SetEnableMod(bool enable);
  virtual void SetVisibleMod(bool visible);
  [[nodiscard]] bool GetEnableMod() const;
  [[nodiscard]] bool GetVisibleMod() const;
  const Window* parent();
  virtual void SetTextEnteredEvent(const std::function<void(const sf::Event&)>& Func);
  virtual void SetKeyPressedEvent(const std::function<void(const sf::Event&)>& Func);
  virtual void SetKeyReleasedEvent(const std::function<void(const sf::Event&)>& Func);
  void SetUpdateEvent(const std::function<void(double dt)>& Func, double time);
  friend class Window;
  virtual void Draw();
  virtual void Delete();

protected:
  bool enable_ = true;
  bool visible_ = true;
  Window* parent_;
  std::function<void(const sf::Event&)> TextEntered_ = nullptr;
  std::function<void(const sf::Event&)> KeyPressed_ = nullptr;
  std::function<void(const sf::Event&)> KeyReleased_ = nullptr;
  std::function<void(const double)> Update_ = nullptr;
  bool is_independent_;
private:
};

class Object : public Essence {
public:
  Object(const sf::Texture& texture,
         int X,
         int Y,
         Window* parent,
         bool is_independent);
  Object(const sf::Texture& texture, Window* parent, bool is_independent);
  Object(Window* parent, bool is_independent);
  explicit Object(bool is_independent);
  Object();
  ~Object() override;
  float GetX();
  float GetY();
  float GetWidth();
  float GetHeight();
  float GetLocalWidth();
  float GetLocalHeight();
  float GetLeft();
  float GetTop();
  float GetRight();
  float GetBottom();
  void SetScale(float scaleX, float scaleY);
  void SetSize(float Width, float Height);
  void Move(float X, float Y);
  void MoveByCenter(float X, float Y);
  virtual void SetMouseWheelScrolledEvent(const std::function<void(const sf::Event&)>& Func);
  virtual void SetMouseButtonPressedEvent(const std::function<void(const sf::Event&)>& Func);
  virtual void SetMouseButtonReleasedEvent(const std::function<void(const sf::Event&)>& Func);
  virtual void SetMouseMovedEvent(const std::function<void(const sf::Event&)>& Func);
  virtual void SetMouseEnteredEvent(const std::function<void(const sf::Event&)>& Func);
  virtual void SetMouseLeftEvent(const std::function<void(const sf::Event&)>& Func);
  friend class Window;
  void Draw() override;
  void AssignMyTexture(const sf::Texture& texture);
  void Assign(const sf::Texture& texture);

protected:
  sf::Sprite Sprite_;
  sf::Texture Texture_;
  bool under_mouse_ = false;
  bool pressed_ = false;
  std::function<void(const sf::Event&)> MouseWheelScrolled_ = nullptr;
  std::function<void(const sf::Event&)> MouseButtonPressed_ = nullptr;
  std::function<void(const sf::Event&)> MouseButtonReleased_ = nullptr;
  std::function<void(const sf::Event&)> MouseMoved_ = nullptr;
  std::function<void(const sf::Event&)> MouseEntered_ = nullptr;
  std::function<void(const sf::Event&)> MouseLeft_ = nullptr;

private:

};

class Character : public Object {
public:
private:
};

//----------------------------------------------------------

class Button : public Object {
public:
  Button(const sf::Texture& s1,
         const sf::Texture& s2,
         const sf::Texture& s3,
         Window* parent,
         bool is_independent);
  Button(sf::Texture&& s1,
         sf::Texture&& s2,
         sf::Texture&& s3,
         Window* parent,
         bool is_independent);
  Button(const std::string& s1,
         const std::string& s2,
         const std::string& s3,
         Window* parent,
         bool is_independent);
  Button(sf::Texture& s1,
         sf::Texture& s2,
         sf::Texture& s3,
         const sf::Text& text,
         Window* parent,
         bool is_independent);
  Button(sf::Texture&& s1,
         sf::Texture&& s2,
         sf::Texture&& s3,
         const sf::Text& text,
         Window* parent,
         bool is_independent);
  static void Print(sf::Text text, sf::Texture& texture);
  void Print(const sf::Text& text);
  void SetMouseButtonPressedEvent(const std::function<void(const sf::Event&)>& Func) final;
  void SetMouseButtonReleasedEvent(const std::function<void(const sf::Event&)>& Func) final;
  void SetMouseMovedEvent(const std::function<void(const sf::Event&)>& Func) final;
  void SetMouseEnteredEvent(const std::function<void(const sf::Event&)>& Func) final;
  void SetMouseLeftEvent(const std::function<void(const sf::Event&)>& Func) final;
  void SetEnableMod(bool enable) final;

  ~Button() override;
protected:
  void ButtonMouseEntered();
  void ButtonMouseLeft();
  void ButtonMouseButtonPressed();
  void ButtonMouseButtonReleased();
  void ButtonMouseMoved();
  sf::Texture p1, p2, p3;
private:
};

class Game {
public:
private:
};

class Fon final : public Object {
public:
  Fon(std::vector<std::string> PathsToFrames, double FPS, Window* parent, bool is_independent);
  Fon(std::string PathToFrames, size_t NumberOfFrames, double FPS, Window* parent, bool is_independent);
  ~Fon() final;
  void Update(double dt);
private:
  std::vector<sf::Texture> FonImages;
  double FPS = 30;
  double CurrentFrame = 0;
};

class MainMenu final : public Essence {
public:
  static MainMenu* getMainMenu();
  void Draw() final;
  ~MainMenu() final;
  void SetEnableMod(bool enable) final;
  MainMenu(const MainMenu&) = delete;
  MainMenu& operator=(const MainMenu&) = delete;
private:
  static MainMenu* pmm;
  static void PlayButtonEvent(const sf::Event& event);
  void ExitButtonEvent(const sf::Event& event);
  MainMenu();
  Button PlayButton, SettingsButton, ExitButton;
  Fon MainMenuFon;
};

class PlayMenu final : public Essence {
public:
  static PlayMenu* getPlayMenu();
  void Draw() final;
  ~PlayMenu() final;
  void SetEnableMod(bool enable) final;
  PlayMenu(const PlayMenu&) = delete;
  PlayMenu& operator=(const PlayMenu&) = delete;
private:
  static PlayMenu* ppm;
  static void BackButtonEvent(const sf::Event& event);
  static void Game2ButtonEvent(const sf::Event& event);
  PlayMenu();
  Button BackButton;
  Button Game1Button, Game2Button, Game3Button, Game4Button;
  Fon PlayMenuFon;
};

class InGameMenu {
public:
private:
  Button ContinueButton, MainMenuButton, SettingsButton, ExitButton;
};

class ExitMenu final : public Essence {
public:
  explicit ExitMenu(Window* WindowThatShouldBeClosed);
  void Draw() final;
  static void CloseWithExitMenu(Window* window);
  void SetEnableMod(bool enable) final;
  ExitMenu(const ExitMenu&) = delete;
  ExitMenu& operator=(const ExitMenu&) = delete;
private:
  ~ExitMenu() final;
  Window* WindowThatShouldBeClosed;
  Button ButtonYES, ButtonNO;
  Fon ExitMenuFon;
  void YESButtonEvent(const sf::Event& event);
  void NOButtonEvent(const sf::Event& event);
  void ExitClosed();
  static std::unordered_set<Window*> WindowsWithOpenExit;
};

class Settings {
public:
private:
};

//----------------------------------------------------------

class Profile {
public:
private:
};

class User {
public:
private:
};

class BigBoy {
public:
private:
};

//class Bucket : public Object {
// public:
//   int lft = 0;
//   int rgh = 0;
//   int tp = 0;
//   int bt = 0;
//   Bucket(const sf::Texture& texture,
//          Window* parent,
//          bool is_independent = true) : Object(texture, parent, is_independent) {
//                                            lft = rect.left;
//                                            rgh = rect.width + lft;
//                                            tp = rect.top;
//                                            bt = tp - 20;
//                                        };
//};

class Bucket : public Object{
 public:
   std::vector<sf::Texture> animat;
   bool jump = 0;
   float max_height = 0;
   std::string inf = "up";
   char orientation = 'L';
   double speed = 1;
   sf::Clock tmr;
   double CurrentFrame = 0;
   double FPS = 0;
   bool down = false;
   Bucket(const sf::Texture& texture,
          double FPS,
          size_t NumberOfFrames,
          Window* parent,
          bool is_independent, std::string PathToFrames);
   void Reverse();
   void Update(double dt);
};

class Loot : public Object{
 public:
   std::string name;
   Loot(const sf::Texture& texture, Window* parent, bool is_independent, std::string name);
};

class game2: Essence {
 private:
   game2();
   static game2* game2pointer;
   int coin = 0;
   Fon* background;
   Bucket* bucket;
   std::vector<Loot*> loot;
   sf::Clock global_timer;
   sf::Clock loot_timer;
   sf::Texture tnt_text;
   sf::Texture coin_text;
   int level = 1;
   double loot_speed;
   double loot_creat_time;
   double min_loot_creat_time;
   double max_loot_speed;
 public:
   void Draw();
   static game2* getGame2();
   game2(const game2&) = delete;
   game2& operator=(const game2&) = delete;
   void stop();
   void cont();
   void exit();
   void start();
   int get_coin();
   void Update(double dt);
   ~game2();
};