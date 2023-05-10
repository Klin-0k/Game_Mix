#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>

Loot::Loot(const sf::Texture& texture, Window* parent, bool is_independent, std::string name) : Object(texture, parent, is_independent), name(name){}

Bucket::Bucket(const sf::Texture& texture,
               double FPS,
               size_t NumberOfFrames,
       Window* parent,
       bool is_independent, std::string PathToFrames) : Object(texture, parent, is_independent){
  size_t pos = PathToFrames.rend() - std::find(PathToFrames.rbegin(), PathToFrames.rend(), '*') - 1;
  for (size_t i = 0; i < NumberOfFrames; ++i) {
    std::string Path = PathToFrames;
    Path.erase(pos, 1);
    Path.insert(pos, std::to_string(i));
    sf::Texture Frame;
    Frame.loadFromFile(Path);
    animat.emplace_back(std::move(Frame));
  }
  this->FPS = FPS;
  SetUpdateEvent([this](double dt) { Update(dt); });
}

void Game2::Loot_Generating(){
  if (loot_timer.getElapsedTime().asMilliseconds() >=
      std::max(loot_creat_time / (level * level), min_loot_creat_time)) {
    loot_timer.restart();
    int r = std::rand() % 3 + 1;
    if (r == 1) {
      Loot *l = new Loot(tnt_text, parent_, false, "TNT");
      loot.push_back(l);
      l->SetSize(parent_->getSize().y / 25, parent_->getSize().y / 25);
      int rr = std::rand() % 19 + 1;
      l->MoveByCenter(rr * parent_->getSize().x / 20, -(l->GetHeight() / 2));
    } else {
      Loot *l = new Loot(coin_text, parent_, false, "coin");
      loot.push_back(l);
      l->SetSize(parent_->getSize().y / 25, parent_->getSize().y / 25);
      int rr = std::rand() % 19 + 1;
      l->MoveByCenter(rr * parent_->getSize().x / 20, -(l->GetHeight() / 2));
    }
  }
}

void Game2::Loot_Moving(double dt){
  float h = this->bucket->GetHeight();
  float w = this->bucket->GetWidth();
  float l = this->bucket->GetLeft();
  float r = this->bucket->GetRight();
  float t = this->bucket->GetTop();
  float start = parent_->getSize().y * 8 / 10 + h / 2;
  auto dist = dt * std::min(loot_speed * std::sqrt(level), max_loot_speed);
  auto it = loot.begin();
  while (it != loot.end()) {
    Loot *lt = *it;
    float center_y = lt->GetTop() + lt->GetHeight() / 2;
    float loot_left = lt->GetLeft();
    float loot_right = lt->GetRight();
    if (center_y <= t + h * 9 / 40 && center_y >= t + h / 10 &&
        loot_left >= l + w / 20 && loot_right <= r - w / 20 &&
        std::min(loot_speed * std::sqrt(level), max_loot_speed) >=
            bucket->vertical_speed) {
      if (lt->name == "TNT") {
        coin = 0;
        bucket->hearts -= 1;
      } else {
        coin += 1;
      }
      lt->Delete();
      it = loot.erase(it);
      continue;
    }
    if (lt->GetBottom() < start) {
      lt->Move(lt->GetLeft(), lt->GetTop() + dist);
      ++it;
    } else {
      lt->Delete();
      it = loot.erase(it);
      continue;
    }
  }
}

void Game2::Update(double dt) {
  if (bucket->dead) {
    return ;
  }
  bucket->horizontal_speed = parent_->getSize().x/1060.0;
  if (global_timer.getElapsedTime().asMilliseconds() >= level * 7000) {
    global_timer.restart();
    level += 1;
  }
  Loot_Generating();
  Loot_Moving(dt);
  if (bucket->hearts <= 0){
    bucket->dead = true;
  }
}

void Bucket::Turn_Left(double dt, double dist){
  if (orientation == 'R'){
    this->Reverse();
    orientation = 'L';
  }
  this->Move(this->GetLeft() - dist, this->GetTop());
  CurrentFrame += dt * FPS / 1000.0;
  CurrentFrame -=
      static_cast<double>(static_cast<size_t>(CurrentFrame) / animat.size() * animat.size());
  AssignMyTexture(animat[static_cast<size_t>(CurrentFrame)]);
}

void Bucket::Turn_Right(double dt, double dist){
  if (orientation == 'L'){
    this->Reverse();
    orientation = 'R';
  }
  this->Move(this->GetLeft() + dist, this->GetTop());
  CurrentFrame += dt * FPS / 1000.0;
  CurrentFrame -=
      static_cast<double>(static_cast<size_t>(CurrentFrame) / animat.size() * animat.size());
  AssignMyTexture(animat[static_cast<size_t>(CurrentFrame)]);
}

void Bucket::Jumping(double dt){
  float h = this->GetHeight();
  float start = parent_->getSize().y*8/10+h/2;
  double g = horizontal_speed /410.0;
  double sp = horizontal_speed *1.3;
  if (jump && inf == "up"){
    double tm = tmr.getElapsedTime().asMilliseconds();
    float heigh = sp*tm - g*(0.5)*tm*tm;
    if (heigh >= 0){
      this->Move(this->GetLeft(), start-heigh-h);
    }
    max_height = heigh;
    vertical_speed = -1;
    if (g>=sp/tm && tm!=0){
      max_height = heigh;
      inf = "down";
      tmr.restart();
    }
  } else {
    if (jump && inf == "down") {
      if (down){
        this->Move(this->GetLeft(), this->GetTop()+dt* vertical_speed);
      } else {
        double tm = tmr.getElapsedTime().asMilliseconds();
        double s = g * (0.5) * tm * tm;
        vertical_speed = g*tm;
        this->Move(this->GetLeft(), start - max_height + s - h);
      }
      if (this->GetBottom() >= start) {
        this->Move(this->GetLeft(), start - h);
        jump = false;
        inf = "up";
        down = false;
        vertical_speed = 0;
      }
    } else {
      max_height = (parent_->getSize().y/3);
    }
  }
}

    void Bucket::Update(double dt) {
      if (dead){
        return ;
      }
      auto dist = dt * horizontal_speed /1.1;
      if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && this->GetLeft()>=dist){
        Turn_Left(dt, dist);
      }
      if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && this->GetRight()<=parent_->getSize().x-dist){
        Turn_Right(dt, dist);
      }
      if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && jump==false) {
        jump = true;
        tmr.restart();
      }
      if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) && jump==true) {
        inf = "down";
        down = true;
        vertical_speed = horizontal_speed *2.5;
      }
      Jumping(dt);
      if (hearts <= 0){
        dead = true;
      }
    }

void Bucket::Reverse() {
  sf::IntRect textureRect = Sprite_.getTextureRect();
  textureRect.left += textureRect.width; // смещение прямоугольника на ширину текстуры
  textureRect.width = -textureRect.width; // отзеркаливание по оси X
  Sprite_.setTextureRect(textureRect);
}

Bucket::~Bucket(){
  size_t s = heart.size();
  for (size_t i = 0; i < s; ++i){
    heart[i]->Delete();
  }
  (*this).Delete();
}

int Game2::get_coin() {
  return coin;
}

Game2::Game2() {
  std::srand(time(NULL));
  tnt_text.loadFromFile(PATH_TO_RESOURCES"/game2/TNT.png");
  coin_text.loadFromFile(PATH_TO_RESOURCES"/game2/coin.png");
  std::string path = PATH_TO_RESOURCES"/game2/background*.png";
  background = new Fon(path, 1, 0, parent_, false);
  sf::Texture texture;
  texture.loadFromFile(PATH_TO_RESOURCES"/game2/animation/0.png");
  path = PATH_TO_RESOURCES"/game2/animation/*.png";
  bucket = new Bucket(texture, 60, 11, parent_, false, path);
  bucket->max_height = (parent_->getSize().y/3);
  bucket->SetSize(parent_->getSize().x/8, parent_->getSize().y/4);
  bucket->MoveByCenter(parent_->getSize().x/2, parent_->getSize().y*8/10);
  bucket->horizontal_speed =parent_->getSize().x/1060.0;
  bucket->SetUpdateEvent([this] (double dt) { bucket->Update(dt); });
  global_timer.restart();
  loot_timer.restart();
  min_loot_creat_time = 300.0;
  loot_creat_time = 3000.0;
  max_loot_speed = bucket->horizontal_speed *4;
  loot_speed = bucket->horizontal_speed /8;
  bucket->heart_texture.loadFromFile(PATH_TO_RESOURCES"/game2/heart.png");
  for (int i = 0; i < bucket->hearts; ++i){
    Object* l = new Object(bucket->heart_texture, parent_, false);
    l->SetSize(parent_->getSize().x/28, parent_->getSize().y/22);
    l->MoveByCenter(parent_->getSize().x*(i+1)/18, parent_->getSize().y*58/60);
    bucket->heart.push_back(l);
  }
  SetUpdateEvent([this] (double dt) {Update(dt); });
  exit_button = new Button(PATH_TO_RESOURCES"/buttons/buttonN1.png",
              PATH_TO_RESOURCES"/buttons/buttonN2.png",
              PATH_TO_RESOURCES"/buttons/buttonN3.png",
              parent_,
              false);
  exit_button->SetMouseButtonReleasedEvent([this](const sf::Event& event) { button_link(event); });
  sf::Font font;
  font.loadFromFile(PATH_TO_RESOURCES
                    "/Fonts/JosefinSans-VariableFont_wght.ttf");
  sf::Text text;
  text.setString("Exit");
  text.setCharacterSize(parent_->getSize().y / 15);
  text.setFont(font);
  text.setStyle(sf::Text::Bold);
  exit_button->Print(text);
  exit_button->SetSize(parent_->getSize().x / 10, parent_->getSize().y / 15);
  exit_button->MoveByCenter(parent_->getSize().x / 2, parent_->getSize().y*58 / 60);
}

void Game2::button_link(const sf::Event& event) {
  PlayMenu::getPlayMenu()->coins+=get_coin();
  game2pointer->Delete();
}

Game2 *Game2::game2pointer = nullptr;

Game2 *Game2::getGame2() {
  if (game2pointer == nullptr) {
    game2pointer = new Game2();
  }
  return game2pointer;
}

void Game2::Draw() {
  if (!bucket->dead) {
    background->Draw();
    bucket->Draw();
    for (auto &lt : loot) {
      lt->Draw();
    }
    sf::Font font;
    font.loadFromFile(PATH_TO_RESOURCES
                      "/Fonts/JosefinSans-VariableFont_wght.ttf");
    sf::Text text;
    text.setPosition(parent_->getSize().x * 24 / 30, parent_->getSize().y / 30);
    text.setString("Coins: " + std::to_string(coin));
    text.setCharacterSize(parent_->getSize().y / 15);
    text.setFont(font);
    text.setFillColor(sf::Color::Green);
    text.setStyle(sf::Text::Bold);
    parent_->draw(text);
    text.setString("Level: " + std::to_string(level));
    text.setPosition(parent_->getSize().x / 30, parent_->getSize().y / 30);
    parent_->draw(text);
    for (int i = 0; i < bucket->hearts; ++i) {
      bucket->heart[i]->Draw();
    }
  } else {
    parent_->clear(sf::Color::Black);
    sf::Font font;
    font.loadFromFile(PATH_TO_RESOURCES
                      "/Fonts/JosefinSans-VariableFont_wght.ttf");
    sf::Text text;
    text.setString("GAME OVER");
    text.setCharacterSize(parent_->getSize().y / 8);
    text.setFont(font);
    text.setFillColor(sf::Color::Yellow);
    text.setStyle(sf::Text::Bold);
    text.setPosition(parent_->getSize().x / 2 - text.getLocalBounds().width / 2, parent_->getSize().y / 2 - text.getLocalBounds().height / 2);
    parent_->draw(text);
  }
  exit_button->Draw();
}

Game2::~Game2() {
  delete background;
  bucket->Delete();
  delete bucket;
  for (auto &lt : loot) {
    lt->Delete();
  }
  exit_button->Delete();
  game2pointer = nullptr;
}