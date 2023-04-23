PlayMenu* PlayMenu::getPlayMenu() {
  if (ppm == nullptr) {
    ppm = new PlayMenu();
  }
  return ppm;
}
void PlayMenu::Draw() {
  PlayMenuFon.Draw();
  BackButton.Draw();
  Game1Button.Draw();
  Game2Button.Draw();
  Game3Button.Draw();
  Game4Button.Draw();
}
PlayMenu::~PlayMenu() {
  ppm = nullptr;
#ifdef DEBAG
  std::cout << "~PlayMenu\n\n";
#endif
}
void PlayMenu::SetEnableMod(bool enable) {
  BackButton.SetEnableMod(enable);
  Game1Button.SetEnableMod(enable);
  Game2Button.SetEnableMod(enable);
  Game3Button.SetEnableMod(enable);
  Game4Button.SetEnableMod(enable);
  enable_ = enable;
  if (enable_ && !visible_) {
    SetVisibleMod(true);
  }
}
PlayMenu::PlayMenu()
    : Essence(),
      BackButton(PATH_TO_RESOURCES"/buttons/buttonN1.png",
                 PATH_TO_RESOURCES"/buttons/buttonN2.png",
                 PATH_TO_RESOURCES"/buttons/buttonN3.png",
                 parent_,
                 false),
      Game1Button(PATH_TO_RESOURCES"/buttons/UIpack/PNG/blue_button11.png",
                  PATH_TO_RESOURCES"/buttons/UIpack/PNG/green_button11.png",
                  PATH_TO_RESOURCES"/buttons/UIpack/PNG/yellow_button12.png",
                  parent_,
                  false),
      Game2Button(PATH_TO_RESOURCES"/buttons/UIpack/PNG/blue_button11.png",
                  PATH_TO_RESOURCES"/buttons/UIpack/PNG/green_button11.png",
                  PATH_TO_RESOURCES"/buttons/UIpack/PNG/yellow_button12.png",
                  parent_,
                  false),
      Game3Button(PATH_TO_RESOURCES"/buttons/UIpack/PNG/blue_button11.png",
                  PATH_TO_RESOURCES"/buttons/UIpack/PNG/green_button11.png",
                  PATH_TO_RESOURCES"/buttons/UIpack/PNG/yellow_button12.png",
                  parent_,
                  false),
      Game4Button(PATH_TO_RESOURCES"/buttons/UIpack/PNG/blue_button11.png",
                  PATH_TO_RESOURCES"/buttons/UIpack/PNG/green_button11.png",
                  PATH_TO_RESOURCES"/buttons/UIpack/PNG/yellow_button12.png",
                  parent_,
                  false),
      PlayMenuFon(PATH_TO_RESOURCES"/Fons/PlayMenu/(*).png", 99,
                  45,
                  parent_,
                  false) {
  float targetHeight = parent_->getSize().y / 6.0f;
  float targetWidth = targetHeight * BackButton.GetWidth() / BackButton.GetHeight();
  BackButton.SetSize(targetWidth, targetHeight);
  targetHeight = parent_->getSize().y / 9.0f;
  targetWidth = targetHeight * Game1Button.GetWidth() / Game1Button.GetHeight();
  Game1Button.SetSize(targetWidth, targetHeight);
  targetWidth = targetHeight * Game2Button.GetWidth() / Game2Button.GetHeight();
  Game2Button.SetSize(targetWidth, targetHeight);
  targetWidth = targetHeight * Game3Button.GetWidth() / Game3Button.GetHeight();
  Game3Button.SetSize(targetWidth, targetHeight);
  targetWidth = targetHeight * Game4Button.GetWidth() / Game4Button.GetHeight();
  Game4Button.SetSize(targetWidth, targetHeight);
  sf::Font font;
  font.loadFromFile(PATH_TO_RESOURCES"/Fonts/JosefinSans-VariableFont_wght.ttf");
  sf::Text text;
  text.setFont(font);
  text.setFillColor(sf::Color::Yellow);
  text.setStyle(sf::Text::Bold);
  std::string BackName = "Back", Game1Name = "1", Game2Name = "2", Game3Name = "3", Game4Name = "4";
  sf::FloatRect BackTextBounds = sf::Text(BackName, font).getLocalBounds();
  float BackScaleFactor = std::min(BackButton.GetLocalWidth() * 3 / 7 / BackTextBounds.width,
                                   BackButton.GetLocalHeight() * 5 / 14 / BackTextBounds.height);
  text.setScale(BackScaleFactor, BackScaleFactor);
  text.setString(BackName);
  BackButton.Print(text);
  sf::FloatRect Game1TextBounds = sf::Text(Game1Name, font).getLocalBounds();
  float Game1ScaleFactor = std::min(Game1Button.GetLocalWidth() * 3 / 7 / Game1TextBounds.width,
                                    Game1Button.GetLocalHeight() * 5 / 14 / Game1TextBounds.height);
  sf::FloatRect Game2TextBounds = sf::Text(Game2Name, font).getLocalBounds();
  float Game2ScaleFactor = std::min(Game2Button.GetLocalWidth() * 3 / 7 / Game2TextBounds.width,
                                    Game2Button.GetLocalHeight() * 5 / 14 / Game2TextBounds.height);
  sf::FloatRect Game3TextBounds = sf::Text(Game3Name, font).getLocalBounds();
  float Game3ScaleFactor = std::min(Game3Button.GetLocalWidth() * 3 / 7 / Game3TextBounds.width,
                                    Game3Button.GetLocalHeight() * 5 / 14 / Game3TextBounds.height);
  sf::FloatRect Game4TextBounds = sf::Text(Game4Name, font).getLocalBounds();
  float Game4ScaleFactor = std::min(Game4Button.GetLocalWidth() * 3 / 7 / Game4TextBounds.width,
                                    Game4Button.GetLocalHeight() * 5 / 14 / Game4TextBounds.height);
  float GamesScaleFactor =
      std::min(std::min(std::min(Game1ScaleFactor, Game2ScaleFactor), Game3ScaleFactor),
               Game4ScaleFactor);
  text.setScale(GamesScaleFactor, GamesScaleFactor);
  text.setString(Game1Name);
  Game1Button.Print(text);
  text.setString(Game2Name);
  Game2Button.Print(text);
  text.setString(Game3Name);
  Game3Button.Print(text);
  text.setString(Game4Name);
  Game4Button.Print(text);
  float free_horizontal_space_for_Games = (parent_->getSize().x
      - (Game1Button.GetWidth() + Game2Button.GetWidth())) / 3;
  float free_vertical_space_for_Games = (parent_->getSize().y * 65 / 100
      - (Game1Button.GetHeight() + Game2Button.GetHeight())) / 3;
  Game1Button.Move(free_horizontal_space_for_Games, free_vertical_space_for_Games);
  Game2Button.Move(Game1Button.GetRight() + free_horizontal_space_for_Games,
                   free_vertical_space_for_Games);
  Game3Button.Move(free_horizontal_space_for_Games,
                   Game1Button.GetBottom() + free_vertical_space_for_Games);
  Game4Button.Move(Game1Button.GetRight() + free_horizontal_space_for_Games,
                   Game1Button.GetBottom() + free_vertical_space_for_Games);
  BackButton.MoveByCenter(parent_->getSize().x / 2,
                          parent_->getSize().y * 65 / 100 + parent_->getSize().y * 35 / 200);
  BackButton.SetMouseButtonReleasedEvent(BackButtonEvent);
  Game2Button.SetMouseButtonReleasedEvent(Game2ButtonEvent);
}
void PlayMenu::BackButtonEvent(const sf::Event& event) {
  MainMenu::getMainMenu();
  ppm->Delete();
}
void PlayMenu::Game2ButtonEvent(const sf::Event& event) {
  game2::getGame2();
  ppm->Delete();
}