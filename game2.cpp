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
  SetUpdateEvent([this](double dt) { Update(dt); }, 1000 / FPS);
}

void game2::Update(double dt){
  if (global_timer.getElapsedTime().asMilliseconds() >= level*7000){
    global_timer.restart();
    level+=1;
  }
  if (loot_timer.getElapsedTime().asMilliseconds() >= std::max(loot_creat_time/(level*level), min_loot_creat_time)){
    loot_timer.restart();
    int r = std::rand()%3 + 1;
    if (r == 1){
      Loot* l = new Loot(tnt_text, parent_, false, "TNT");
      loot.push_back(l);
      l->SetSize(parent_->getSize().y/25, parent_->getSize().y/25);
      int rr = std::rand()%19 + 1;
      l->MoveByCenter(rr * parent_->getSize().x/20, -(l->GetHeight()/2));
    } else {
      Loot* l = new Loot(coin_text, parent_, false, "coin");
      loot.push_back(l);
      l->SetSize(parent_->getSize().y/25, parent_->getSize().y/25);
      int rr = std::rand()%19 + 1;
      l->MoveByCenter(rr * parent_->getSize().x/20, -(l->GetHeight()/2));
    }
  }
  float h = this->bucket->GetHeight();
  float w = this->bucket->GetWidth();
  float l = this->bucket->GetLeft();
  float r = this->bucket->GetRight();
  float t = this->bucket->GetTop();
  float start = parent_->getSize().y*8/10+h/2;
  auto dist = dt * std::min(loot_speed*std::sqrt(level), max_loot_speed);
  auto it = loot.begin();
  for (auto& lt : loot){
    float center_y = lt->GetTop()+lt->GetHeight()/2;
    float loot_left = lt->GetLeft();
    float loot_right = lt->GetRight();
    if (center_y <= t+h*9/40 && center_y>=t+h/10 && loot_left>=l+w/20 && loot_right<=r-w/20) {
      if (lt->name=="TNT"){
        coin = 0;
      } else {
        coin += 1;
      }
      lt->Delete();
      it = loot.erase(it);
      continue;
    }
    if(lt->GetBottom()<start){
      lt->Move(lt->GetLeft(), lt->GetTop()+dist);
      ++it;
    } else{
      lt->Delete();
      it = loot.erase(it);
      continue;
    }
  }
}

void Bucket::Update(double dt) {
  auto dist = dt * speed/1.1;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->GetLeft()>=dist){
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
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->GetRight()<=parent_->getSize().x-dist){
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
  if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && jump==false) {
    jump = true;
    tmr.restart();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && jump==true) {
    inf = "down";
    down = true;
  }
  float h = this->GetHeight();
  float start = parent_->getSize().y*8/10+h/2;
  double g = speed/410.0;
  double sp = speed*1.3;
  if (jump && inf == "up"){
    double tm = tmr.getElapsedTime().asMilliseconds();
    float heigh = sp*tm - g*(0.5)*tm*tm;
    if (heigh >= 0){
      this->Move(this->GetLeft(), start-heigh-h);
    }
    max_height = heigh;
    if (g>=sp/tm && tm!=0){
      max_height = heigh;
      inf = "down";
      tmr.restart();
    }
  } else {
    if (jump && inf == "down") {
      if (down){
        this->Move(this->GetLeft(), this->GetTop()+dt*speed*2.5);
      } else {
        double tm = tmr.getElapsedTime().asMilliseconds();
        double s = g * (0.5) * tm * tm;
        this->Move(this->GetLeft(), start - max_height + s - h);
      }
      if (this->GetBottom() >= start) {
        this->Move(this->GetLeft(), start - h);
        jump = false;
        inf = "up";
        down = false;
      }
    }
  }
//  if (jump && inf == "up"){
//    this->Move(this->GetLeft(), this->GetTop()-dist/2);
//    if (this->GetBottom()<=max_height){
//      inf = "down";
//    }
//  } else {
//    if (jump && inf == "down"){
//      this->Move(this->GetLeft(), this->GetTop()+dist/2);
//      float h = this->GetHeight();
//      if (this->GetBottom()>=(parent_->getSize().y*8/10+h/2)) {
//        this->Move(this->GetLeft(), (parent_->getSize().y*8/10-h/2));
//        jump = false;
//        inf = "up";
//      }
//    }
//  }
}

void Bucket::Reverse() {
  sf::IntRect textureRect = Sprite_.getTextureRect();
  textureRect.left += textureRect.width; // смещение прямоугольника на ширину текстуры
  textureRect.width = -textureRect.width; // отзеркаливание по оси X
  Sprite_.setTextureRect(textureRect);
}

int game2::get_coin() {
  return coin;
}

game2::game2() {
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
  bucket->speed=parent_->getSize().x/1060.0;
  bucket->SetUpdateEvent([this] (double dt) { bucket->Update(dt); });
  global_timer.restart();
  loot_timer.restart();
  min_loot_creat_time = 300.0;
  loot_creat_time = 3000.0;
  max_loot_speed = bucket->speed*4;
  loot_speed = bucket->speed/8;
  SetUpdateEvent([this] (double dt) {Update(dt); });
}

void game2::cont() {
  SetEnableMod(false);
}

void game2::stop(){
    SetEnableMod(true);
}


game2* game2::game2pointer = nullptr;

game2* game2::getGame2() {
  if (game2pointer == nullptr) {
    game2pointer = new game2();
  }
  return game2pointer;
}

void game2::Draw() {
  background->Draw();
  bucket->Draw();
  for (auto& lt : loot){
    lt->Draw();
  }
  sf::Font font;
  font.loadFromFile(PATH_TO_RESOURCES"/Fonts/JosefinSans-VariableFont_wght.ttf");
  sf::Text text;
  text.setPosition ( parent_->getSize().x*24/30 , parent_->getSize().y/30) ;
  text.setString ( "Coins: "+std::to_string(coin) ) ;
  text.setCharacterSize(60);
  text.setFont(font);
  text.setFillColor(sf::Color::Green);
  text.setStyle(sf::Text::Bold);
  parent_->draw(text);
  text.setString ( "Level: "+std::to_string(level) ) ;
  text.setPosition ( parent_->getSize().x/30 , parent_->getSize().y/30) ;
  parent_->draw(text);
}

game2::~game2() {
  delete background;
  delete bucket;
  for (auto& lt: loot){
    lt->Delete();
  }
}