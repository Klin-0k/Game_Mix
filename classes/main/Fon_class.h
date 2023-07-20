#pragma once

#include <classes/main/Object_class.h>

class Fon : public Object {
 public:
  Fon(std::vector<std::string> PathsToFrames, double FPS, Window* parent, bool is_independent);
  Fon(std::string PathToFrames,
      size_t NumberOfFrames,
      double FPS,
      Window* parent,
      bool is_independent);
  ~Fon() override;
  void Update(double dt);

 private:
  std::vector<sf::Texture> FonImages;
  double FPS = 30;
  double CurrentFrame = 0;
};