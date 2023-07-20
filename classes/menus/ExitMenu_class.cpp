#include <classes/menus/ExitMenu_class.h>

std::unordered_set<Window*> ExitMenu::WindowsWithOpenExit = std::unordered_set<Window*>();

void ExitMenu::Draw() {
  ExitMenuFon.Draw();
  ButtonYES.Draw();
  ButtonNO.Draw();
}
ExitMenu::~ExitMenu() {
  WindowsWithOpenExit.erase(WindowThatShouldBeClosed);
  parent_->Delete();
#ifdef DEBUG
  std::cout << "~ExitMenu\n\n";
#endif
}
void ExitMenu::SetEnableMod(bool enable) {
  ButtonYES.SetEnableMod(enable);
  ButtonNO.SetEnableMod(enable);
  enable_ = enable;
  if (enable_ && !visible_) {
    SetVisibleMod(true);
  }
}
ExitMenu::ExitMenu(Window* WindowThatShouldBeClosed)
    : Essence(new Window(sf::VideoMode(sf::VideoMode::getDesktopMode().height * 3 / 8 * 16 / 9,
                                       sf::VideoMode::getDesktopMode().height * 3 / 8),
                         "Exit")),
      WindowThatShouldBeClosed(WindowThatShouldBeClosed),
      ButtonYES(PATH_TO_RESOURCES "/buttons/buttonN1.png",
                PATH_TO_RESOURCES "/buttons/buttonN2.png",
                PATH_TO_RESOURCES "/buttons/buttonN3.png",
                parent_,
                false),
      ButtonNO(PATH_TO_RESOURCES "/buttons/buttonN1.png",
               PATH_TO_RESOURCES "/buttons/buttonN2.png",
               PATH_TO_RESOURCES "/buttons/buttonN3.png",
               parent_,
               false),
      ExitMenuFon(PATH_TO_RESOURCES "/Fons/ExitMenu/(*).png", 23,
                  30,
                  parent_,
                  false) {
  parent_->setPosition({static_cast<int>(WindowThatShouldBeClosed->getPosition().x
                                         + (WindowThatShouldBeClosed->getSize().x - parent_->getSize().x) / 2),
                        static_cast<int>(WindowThatShouldBeClosed->getPosition().y
                                         + (WindowThatShouldBeClosed->getSize().y - parent_->getSize().y) / 2)});
  sf::Image window_icon;
  window_icon.loadFromFile(PATH_TO_RESOURCES "/icons/exit_icon.jpg");
  parent_->setIcon(1024, 1024, window_icon.getPixelsPtr());
  Window::WindowsToDisplay.insert(parent_);
  parent_->IsAlwaysOnFocus = true;
  parent_->requestFocus();
  parent_->Close = [this] { ExitClosed(); };
  WindowThatShouldBeClosed->SetEnableMod(false);
  //  ExitWindow->setMouseCursorGrabbed(true);
  float targetHeight = parent_->getSize().y / 6.0f;
  float targetWidth = targetHeight * ButtonYES.GetWidth() / ButtonYES.GetHeight();
  ButtonYES.SetSize(targetWidth, targetHeight);
  targetWidth = targetHeight * ButtonNO.GetWidth() / ButtonNO.GetHeight();
  ButtonNO.SetSize(targetWidth, targetHeight);
  sf::Font font;
  font.loadFromFile(PATH_TO_RESOURCES "/Fonts/JosefinSans-VariableFont_wght.ttf");
  sf::Text text;
  text.setFont(font);
  text.setFillColor(sf::Color::Yellow);
  text.setStyle(sf::Text::Bold);
  std::string YESName = "Yes", NOName = "No";
  sf::FloatRect textBounds1 = sf::Text(YESName, font).getLocalBounds();
  float scaleFactor1 = std::min(ButtonYES.GetLocalWidth() * 3 / 7 / textBounds1.width,
                                ButtonYES.GetLocalHeight() * 5 / 14 / textBounds1.height);
  sf::FloatRect textBounds2 = sf::Text(NOName, font).getLocalBounds();
  float scaleFactor2 = std::min(ButtonNO.GetLocalWidth() * 3 / 7 / textBounds2.width,
                                ButtonNO.GetLocalHeight() * 5 / 14 / textBounds2.height);
  float scaleFactor = std::min(scaleFactor1, scaleFactor2);
  text.setScale(scaleFactor, scaleFactor);
  text.setString(YESName);
  ButtonYES.Print(text);
  text.setString(NOName);
  ButtonNO.Print(text);
  float free_vertical_space_ = (parent_->getSize().y
                                - (ButtonYES.GetHeight() + ButtonNO.GetHeight()) / 2)
      / 2;
  float free_horizontal_space_ =
      (parent_->getSize().x - (ButtonYES.GetWidth() + ButtonNO.GetWidth())) / 3;
  ButtonYES.Move(free_horizontal_space_, free_vertical_space_);
  ButtonNO.Move(ButtonYES.GetRight() + free_horizontal_space_,
                free_vertical_space_);
  ButtonYES.SetMouseButtonReleasedEvent((std::function<void(const sf::Event&)>) [this](const sf::Event& event) {
    YESButtonEvent(event);
  });
  ButtonNO.SetMouseButtonReleasedEvent((std::function<void(const sf::Event&)>) [this](const sf::Event& event) {
    NOButtonEvent(event);
  });
#ifdef DEBUG
  parent_->Name = "ExitWindow";
#endif
}

void ExitMenu::YESButtonEvent(const sf::Event& event) {
  parent_->Close();
  WindowThatShouldBeClosed->Delete();
}
void ExitMenu::NOButtonEvent(const sf::Event& event) {
  parent_->Close();
}
void ExitMenu::ExitClosed() {
  Delete();
  WindowThatShouldBeClosed->SetEnableMod(true);
}
void ExitMenu::CloseWithExitMenu(Window* window) {
  if (WindowsWithOpenExit.find(window) == WindowsWithOpenExit.end()) {
    WindowsWithOpenExit.insert(window);
    new ExitMenu(window);
  }
}
