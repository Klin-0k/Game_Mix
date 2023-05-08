#pragma once

#include <iostream>
#include <unordered_set>
#include <fstream>
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
  int coins = 0;
  static PlayMenu* getPlayMenu();
  void Draw() final;
  ~PlayMenu() final;
  void SetEnableMod(bool enable) final;
  PlayMenu(const PlayMenu&) = delete;
  PlayMenu& operator=(const PlayMenu&) = delete;
 private:
  static PlayMenu* ppm;
  static void BackButtonEvent(const sf::Event& event);
  static void Game2ButtonEvent(const sf::Event &event);
  static void Game1ButtonEvent(const sf::Event& event);
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

class Bucket : public Object {
 public:
  std::vector<sf::Texture> animat;
  int hearts = 3;
  bool dead  = false;
  sf::Texture heart_texture;
  std::vector<Object*> heart;
  bool jump = 0;
  float max_height = 0;
  std::string inf = "up";
  char orientation = 'L';
  double horizontal_speed;
  double vertical_speed;
  sf::Clock tmr;
  double CurrentFrame = 0;
  double FPS = 0;
  bool down = false;
  Bucket(const sf::Texture &texture, double FPS, size_t NumberOfFrames,
         Window *parent, bool is_independent, std::string PathToFrames);
  void Reverse();
  void Update(double dt);
  ~Bucket();
};

class Loot : public Object {
 public:
  std::string name;
  Loot(const sf::Texture &texture, Window *parent, bool is_independent,
       std::string name);
};

class Game2 : Essence {
 private:
  Game2();
  static Game2 *game2pointer;
  int coin = 0;
  Fon *background;
  Bucket *bucket;
  std::vector<Loot *> loot;
  sf::Clock global_timer;
  sf::Clock loot_timer;
  sf::Texture tnt_text;
  sf::Texture coin_text;
  Button* exit_button;
  int level = 1;
  double loot_speed;
  double loot_creat_time;
  double min_loot_creat_time;
  double max_loot_speed;

 public:
  void Draw();
  void button_link(const sf::Event& event);
  static Game2 *getGame2();
  Game2(const Game2 &) = delete;
  Game2 &operator=(const Game2 &) = delete;
  int get_coin();
  void Update(double dt);
  ~Game2();
};

struct Coords {
  int x;
  int y;
};

struct Figure {
  std::vector<sf::RectangleShape> tiles;
  size_t size;
  int type;
};

class Game1 : Essence {
 private:
  Game1();
  void CheckEvents(const sf::Event& event);
  void DestroyRow(int i, int j);
  sf::Color GetRandomColor();
  Object* game_background;
  static Game1 *game_1_pointer;
  Fon *background;
  sf::Texture game_background_image;
  static const int width_of_net_in_tiles = 15;
  int height_of_net_in_tiles;
  float indent_x;
  float indent_y;
  int tile_size;
  sf::RectangleShape tile;

  sf::RectangleShape red_line;
  sf::RectangleShape white_line;

  std::vector<std::vector<Coords>> figures_pos;
  std::vector<std::vector<sf::RectangleShape>> figures;
  int type_of_figure;
  Figure figure;
  Figure next_figure;
  sf::Color color;
  sf::Color next_color;
  int speed_of_falling;
  int moves_by_x;
  int moves_by_y;
  int rotation;
  int indent_by_x;

  std::vector<std::vector<bool>> is_tiled;
  std::vector<std::vector<bool>> is_destroyed;
  std::vector<std::vector<bool>> supposed_to_be_destroyed;
  std::vector<std::vector<sf::Color>> mem_color;

  int start_transparency = 255;
  int transparency = start_transparency;
  int speed_of_destruction = 5;
  bool in_process_of_destruction = false;
  int row_of_destruction = -1;
  int counter_of_destructed_rows = 0;
  int max_value_before_speed_up = 5;

  int score = 0;
  //record = get_record();
  int rows = 0;
  int one_tile_cost = 10;

 public:
  static Game1* GetGame1();
  Game1(const Game1&) = delete;
  Game1& operator=(const Game1&) = delete;
  void stop();
  void cont();
  void Update(double dt);
  void Draw();
  ~Game1();
};