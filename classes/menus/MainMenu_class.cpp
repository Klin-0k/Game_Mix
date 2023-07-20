#include <classes/menus/MainMenu_class.h>
#include <classes/menus/PlayMenu_class.h>

MainMenu* MainMenu::pmm = nullptr;

MainMenu* MainMenu::getMainMenu() {
  if (pmm == nullptr) {
    pmm = new MainMenu();
  }
  return pmm;
}
void MainMenu::Draw() {
  MainMenuFon.Draw();
  PlayButton.Draw();
  SettingsButton.Draw();
  ExitButton.Draw();
}
MainMenu::~MainMenu() {
  pmm = nullptr;
#ifdef DEBUG
  std::cout << "~MainMenu\n\n";
#endif
}
void MainMenu::SetEnableMod(bool enable) {
  PlayButton.SetEnableMod(enable);
  SettingsButton.SetEnableMod(enable);
  ExitButton.SetEnableMod(enable);
  enable_ = enable;
  if (enable_ && !visible_) {
    SetVisibleMod(true);
  }
}
MainMenu::MainMenu()
    : Essence(),
      PlayButton(PATH_TO_RESOURCES "/buttons/buttonN1.png",
                 PATH_TO_RESOURCES "/buttons/buttonN2.png",
                 PATH_TO_RESOURCES "/buttons/buttonN3.png",
                 parent_,
                 false),
      SettingsButton(PATH_TO_RESOURCES "/buttons/buttonN1.png",
                     PATH_TO_RESOURCES "/buttons/buttonN2.png",
                     PATH_TO_RESOURCES "/buttons/buttonN3.png",
                     parent_,
                     false),
      ExitButton(PATH_TO_RESOURCES "/buttons/buttonN1.png",
                 PATH_TO_RESOURCES "/buttons/buttonN2.png",
                 PATH_TO_RESOURCES "/buttons/buttonN3.png",
                 parent_,
                 false),
      MainMenuFon({PATH_TO_RESOURCES "/Fons/MainMenu/(0).png",
                   PATH_TO_RESOURCES "/Fons/MainMenu/(1).png",
                   PATH_TO_RESOURCES "/Fons/MainMenu/(2).png",
                   PATH_TO_RESOURCES "/Fons/MainMenu/(3).png",
                   PATH_TO_RESOURCES "/Fons/MainMenu/(4).png"},
                  30,
                  parent_,
                  false) {
  float targetHeight = parent_->getSize().y / 6.0f;
  float targetWidth = targetHeight * PlayButton.GetWidth() / PlayButton.GetHeight();
  PlayButton.SetSize(targetWidth, targetHeight);
  targetWidth = targetHeight * SettingsButton.GetWidth() / SettingsButton.GetHeight();
  SettingsButton.SetSize(targetWidth, targetHeight);
  targetWidth = targetHeight * ExitButton.GetWidth() / ExitButton.GetHeight();
  ExitButton.SetSize(targetWidth, targetHeight);
  sf::Font font;
  font.loadFromFile(PATH_TO_RESOURCES "/Fonts/JosefinSans-VariableFont_wght.ttf");
  sf::Text text;
  text.setFont(font);
  text.setFillColor(sf::Color::Yellow);
  text.setStyle(sf::Text::Bold);
  std::string PlayName = "Play", SettingsName = "Settings", ExitName = "Exit";
  sf::FloatRect textBounds1 = sf::Text(PlayName, font).getLocalBounds();
  float scaleFactor1 = std::min(PlayButton.GetLocalWidth() * 3 / 7 / textBounds1.width,
                                PlayButton.GetLocalHeight() * 5 / 14 / textBounds1.height);
  sf::FloatRect textBounds2 = sf::Text(SettingsName, font).getLocalBounds();
  float scaleFactor2 = std::min(SettingsButton.GetLocalWidth() * 3 / 7 / textBounds2.width,
                                SettingsButton.GetLocalHeight() * 5 / 14 / textBounds2.height);
  sf::FloatRect textBounds3 = sf::Text(ExitName, font).getLocalBounds();
  float scaleFactor3 = std::min(ExitButton.GetLocalWidth() * 3 / 7 / textBounds3.width,
                                ExitButton.GetLocalHeight() * 5 / 14 / textBounds3.height);
  float scaleFactor = std::min(std::min(scaleFactor1, scaleFactor2), scaleFactor3);
  text.setScale(scaleFactor, scaleFactor);
  text.setString(PlayName);
  PlayButton.Print(text);
  text.setString(SettingsName);
  SettingsButton.Print(text);
  text.setString(ExitName);
  ExitButton.Print(text);
  float free_space_ = (parent_->getSize().y
                       - (PlayButton.GetHeight() + SettingsButton.GetHeight() + ExitButton.GetHeight()))
      / 4;
  PlayButton.Move((parent_->getSize().x - PlayButton.GetWidth()) / 2, free_space_);
  SettingsButton.Move((parent_->getSize().x - SettingsButton.GetWidth()) / 2,
                      PlayButton.GetBottom() + free_space_);
  ExitButton.Move((parent_->getSize().x - ExitButton.GetWidth()) / 2,
                  SettingsButton.GetBottom() + free_space_);
  PlayButton.SetMouseButtonReleasedEvent(PlayButtonEvent);
  ExitButton.SetMouseButtonReleasedEvent([this](const sf::Event& event) { ExitButtonEvent(event); });
}

void MainMenu::PlayButtonEvent(const sf::Event& event) {
  PlayMenu::getPlayMenu();
  pmm->Delete();
}
void MainMenu::ExitButtonEvent(const sf::Event& event) {
  pmm->parent_->Close();
}