Fon::Fon(std::vector<std::string> PathsToFrames, double FPS, Window* parent, bool is_independent)
    : Object(parent, is_independent) {
  for (auto& PathToFrame : PathsToFrames) {
    sf::Texture Frame;
    Frame.loadFromFile(PathToFrame);
    FonImages.emplace_back(std::move(Frame));
  }
  AssignMyTexture(FonImages[0]);
  SetSize(parent_->getSize().x, parent_->getSize().y);
  Move(0, 0);
  this->FPS = FPS;
  SetUpdateEvent([this](double dt) { Update(dt); });
}
Fon::Fon(std::string PathToFrames,
         size_t NumberOfFrames,
         double FPS,
         Window* parent,
         bool is_independent) : Object(parent, is_independent) {
  size_t pos = PathToFrames.rend() - std::find(PathToFrames.rbegin(), PathToFrames.rend(), '*') - 1;
  for (size_t i = 0; i < NumberOfFrames; ++i) {
    std::string Path = PathToFrames;
    Path.erase(pos, 1);
    Path.insert(pos, std::to_string(i));
    sf::Texture Frame;
    Frame.loadFromFile(Path);
    FonImages.emplace_back(std::move(Frame));
  }
  AssignMyTexture(FonImages[0]);
  SetSize(parent_->getSize().x, parent_->getSize().y);
  Move(0, 0);
  this->FPS = FPS;
  SetUpdateEvent([this](double dt) { Update(dt); });
}
Fon::~Fon() {
#ifdef DEBAG
  std::cout << "~Fon\n";
#endif
}

void Fon::Update(double dt) {
  CurrentFrame += dt * FPS / 1000.0;
  CurrentFrame -=
      static_cast<double>(static_cast<size_t>(CurrentFrame) / FonImages.size() * FonImages.size());
  AssignMyTexture(FonImages[static_cast<size_t>(CurrentFrame)]);
}