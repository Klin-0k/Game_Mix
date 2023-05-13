#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Test_Window : public Window {
  using Window::Window;
  friend class WindowEventsTest_TextEnteredEventTest_Test;
  friend class WindowEventsTest_KeyPressedEventTest_Test;
  friend class WindowEventsTest_KeyReleasedEventTest_Test;
  friend class WindowEventsTest_MouseWheelScrolledEventTest_Test;
  friend class WindowEventsTest_MouseButtonPressedEventTest_Test;
  friend class WindowEventsTest_MouseButtonReleasedEventTest_Test;
  friend class WindowEventsTest_MouseMovedEventTest_Test;
  friend class WindowEventsTest_MouseEnteredEventTest_Test;
  friend class WindowEventsTest_MouseLeftEventTest_Test;
  friend class WindowUpdateTest_UpdateTest_Test;
};
class Test_Object : public Object {
  using Object::Object;
  friend class WindowEventsTest_TextEnteredEventTest_Test;
  friend class WindowEventsTest_KeyPressedEventTest_Test;
  friend class WindowEventsTest_KeyReleasedEventTest_Test;
  friend class WindowEventsTest_MouseWheelScrolledEventTest_Test;
  friend class WindowEventsTest_MouseButtonPressedEventTest_Test;
  friend class WindowEventsTest_MouseButtonReleasedEventTest_Test;
  friend class WindowEventsTest_MouseMovedEventTest_Test;
  friend class WindowEventsTest_MouseEnteredEventTest_Test;
  friend class WindowEventsTest_MouseLeftEventTest_Test;
  friend class WindowUpdateTest_UpdateTest_Test;
};

TEST(WindowEventsTest, TextEnteredEventTest) {
Test_Window window(sf::VideoMode(1, 1), "test_window");
auto* obj = new Test_Object(&window, true);
std::string event_check;
auto TextEnteredEvent =
    [&event_check](const sf::Event& event) { event_check += "TextEnteredEvent\n"; };
obj->SetTextEnteredEvent(TextEnteredEvent);
sf::Event event;
event.type = sf::Event::TextEntered;
window.EventHandling(event);
obj->SetTextEnteredEvent(nullptr);
window.EventHandling(event);
EXPECT_EQ(event_check, "TextEnteredEvent\n");
delete obj;
}

TEST(WindowEventsTest, KeyPressedEventTest) {
Test_Window window(sf::VideoMode(1, 1), "test_window");
auto* obj = new Test_Object(&window, true);
std::string event_check;
auto KeyPressedEvent =
    [&event_check](const sf::Event& event) { event_check += "KeyPressedEvent\n"; };
obj->SetKeyPressedEvent(KeyPressedEvent);
sf::Event event;
event.type = sf::Event::KeyPressed;
window.EventHandling(event);
obj->SetKeyPressedEvent(nullptr);
window.EventHandling(event);
EXPECT_EQ(event_check, "KeyPressedEvent\n");
delete obj;
}

TEST(WindowEventsTest, KeyReleasedEventTest) {
Test_Window window(sf::VideoMode(1, 1), "test_window");
auto* obj = new Test_Object(&window, true);
std::string event_check;
auto KeyReleasedEvent =
    [&event_check](const sf::Event& event) { event_check += "KeyReleasedEvent\n"; };
obj->SetKeyReleasedEvent(KeyReleasedEvent);
sf::Event event;
event.type = sf::Event::KeyReleased;
window.EventHandling(event);
obj->SetKeyReleasedEvent(nullptr);
window.EventHandling(event);
EXPECT_EQ(event_check, "KeyReleasedEvent\n");
delete obj;
}

TEST(WindowEventsTest, MouseWheelScrolledEventTest) {
Test_Window window(sf::VideoMode(1, 1), "test_window");
auto* obj = new Test_Object(&window, true);
std::string event_check;
auto MouseWheelScrolledEvent =
    [&event_check](const sf::Event& event) { event_check += "MouseWheelScrolledEvent\n"; };
obj->SetMouseWheelScrolledEvent(MouseWheelScrolledEvent);
sf::Event event;
event.type = sf::Event::MouseWheelScrolled;
window.EventHandling(event);
obj->SetMouseWheelScrolledEvent(nullptr);
window.EventHandling(event);
EXPECT_EQ(event_check, "MouseWheelScrolledEvent\n");
delete obj;
}

TEST(WindowEventsTest, MouseButtonPressedEventTest) {
Test_Window window(sf::VideoMode(1, 1), "test_window");
auto* obj = new Test_Object(&window, true);
sf::Texture texture;
sf::Image image;
image.create(1, 1, sf::Color::Red);
texture.loadFromImage(image);
obj->AssignMyTexture(texture);
obj->MoveByCenter(0, 0);
std::string event_check;
auto MouseButtonPressedEvent =
    [&event_check](const sf::Event& event) { event_check += "MouseButtonPressedEvent\n"; };
obj->SetMouseButtonPressedEvent(MouseButtonPressedEvent);
sf::Event event;
event.type = sf::Event::MouseButtonPressed;
event.mouseButton.x = 0;
event.mouseButton.y = 0;
window.EventHandling(event);
obj->SetMouseButtonPressedEvent(nullptr);
window.EventHandling(event);
EXPECT_EQ(event_check, "MouseButtonPressedEvent\n");
delete obj;
}

TEST(WindowEventsTest, MouseButtonReleasedEventTest) {
Test_Window window(sf::VideoMode(1, 1), "test_window");
auto* obj = new Test_Object(&window, true);
sf::Texture texture;
sf::Image image;
image.create(1, 1, sf::Color::Red);
texture.loadFromImage(image);
obj->AssignMyTexture(texture);
obj->MoveByCenter(0, 0);
obj->pressed_ = true;
std::string event_check;
auto MouseButtonReleasedEvent =
    [&event_check](const sf::Event& event) { event_check += "MouseButtonReleasedEvent\n"; };
obj->SetMouseButtonReleasedEvent(MouseButtonReleasedEvent);
sf::Event event;
event.type = sf::Event::MouseButtonReleased;
event.mouseButton.x = 0;
event.mouseButton.y = 0;
window.EventHandling(event);
obj->SetMouseButtonReleasedEvent(nullptr);
window.EventHandling(event);
EXPECT_EQ(event_check, "MouseButtonReleasedEvent\n");
delete obj;
}

TEST(WindowEventsTest, MouseMovedEventTest) {
Test_Window window(sf::VideoMode(1, 1), "test_window");
auto* obj = new Test_Object(&window, true);
sf::Texture texture;
sf::Image image;
image.create(1, 1, sf::Color::Red);
texture.loadFromImage(image);
obj->AssignMyTexture(texture);
obj->MoveByCenter(0, 0);
obj->under_mouse_ = true;
std::string event_check;
auto MouseMovedEvent =
    [&event_check](const sf::Event& event) { event_check += "MouseMovedEvent\n"; };
obj->SetMouseMovedEvent(MouseMovedEvent);
sf::Event event;
event.type = sf::Event::MouseMoved;
event.mouseMove.x = 0;
event.mouseMove.y = 0;
window.EventHandling(event);
obj->SetMouseMovedEvent(nullptr);
window.EventHandling(event);
EXPECT_EQ(event_check, "MouseMovedEvent\n");
delete obj;
}

TEST(WindowEventsTest, MouseEnteredEventTest) {
Test_Window window(sf::VideoMode(1, 1), "test_window");
auto* obj = new Test_Object(&window, true);
sf::Texture texture;
sf::Image image;
image.create(1, 1, sf::Color::Red);
texture.loadFromImage(image);
obj->AssignMyTexture(texture);
obj->MoveByCenter(0, 0);
std::string event_check;
auto MouseEnteredEvent =
    [&event_check](const sf::Event& event) { event_check += "MouseEnteredEvent\n"; };
obj->SetMouseEnteredEvent(MouseEnteredEvent);
sf::Event event;
event.type = sf::Event::MouseMoved;
event.mouseMove.x = 0;
event.mouseMove.y = 0;
window.EventHandling(event);
obj->SetMouseEnteredEvent(nullptr);
window.EventHandling(event);
EXPECT_EQ(event_check, "MouseEnteredEvent\n");
delete obj;
}

TEST(WindowEventsTest, MouseLeftEventTest) {
Test_Window window(sf::VideoMode(1, 1), "test_window");
auto* obj = new Test_Object(&window, true);
sf::Texture texture;
sf::Image image;
image.create(1, 1, sf::Color::Red);
texture.loadFromImage(image);
obj->AssignMyTexture(texture);
obj->MoveByCenter(-5, -5);
obj->under_mouse_ = true;
std::string event_check;
auto MouseLeftEvent =
    [&event_check](const sf::Event& event) { event_check += "MouseLeftEvent\n"; };
obj->SetMouseLeftEvent(MouseLeftEvent);
sf::Event event;
event.type = sf::Event::MouseMoved;
event.mouseMove.x = 0;
event.mouseMove.y = 0;
window.EventHandling(event);
obj->SetMouseLeftEvent(nullptr);
window.EventHandling(event);
EXPECT_EQ(event_check, "MouseLeftEvent\n");
delete obj;
}

TEST(WindowUpdateTest, UpdateTest) {
Test_Window window(sf::VideoMode(1, 1), "test_window");
auto* obj = new Test_Object(&window, true);
std::string update_check;
auto Update = [&update_check](size_t dt) { update_check += "Update\n"; };
obj->SetUpdateEvent(Update);
window.UpdatingEssences(1);
obj->SetUpdateEvent(nullptr);
window.UpdatingEssences(1);
EXPECT_EQ(update_check, "Update\n");
delete obj;
}

class MainMenuTest : public MainMenu {
  using MainMenu::MainMenu;
  friend class GITest_GITest1_Test;
  friend class GITest_GITest2_Test;
  friend class GITest_GITest3_Test;
  friend class GITest_GITest4_Test;
  friend class GITest_GITest5_Test;
  friend class GITest_GITest6_Test;
};
class PlayMenuTest : public PlayMenu {
  using PlayMenu::PlayMenu;
  friend class GITest_GITest1_Test;
  friend class GITest_GITest2_Test;
  friend class GITest_GITest3_Test;
  friend class GITest_GITest4_Test;
  friend class GITest_GITest5_Test;
  friend class GITest_GITest6_Test;
};
class ExitMenuTest : public ExitMenu {
  using ExitMenu::ExitMenu;
  friend class GITest_GITest1_Test;
  friend class GITest_GITest2_Test;
  friend class GITest_GITest3_Test;
  friend class GITest_GITest4_Test;
  friend class GITest_GITest5_Test;
  friend class GITest_GITest6_Test;
};

TEST(GITest, GITest1) {
MainMenu*& pmm = MainMenuTest::pmm;
PlayMenu*& ppm = PlayMenuTest::ppm;
std::unordered_set<Window*>& WindowsWithOpenExit = ExitMenuTest::WindowsWithOpenExit;
GettingStarted();
EXPECT_NE(pmm, nullptr);
EXPECT_EQ(ppm, nullptr);
EXPECT_EQ(WindowsWithOpenExit.size(), 0);
sf::Event event;
MainMenuTest::PlayButtonEvent(event);
MainWindow->MakeFrame();
EXPECT_EQ(pmm, nullptr);
EXPECT_NE(ppm, nullptr);
EXPECT_EQ(WindowsWithOpenExit.size(), 0);
delete MainWindow;
EXPECT_EQ(pmm, nullptr);
EXPECT_EQ(ppm, nullptr);
EXPECT_EQ(WindowsWithOpenExit.size(), 0);
}

TEST(GITest, GITest2) {
MainMenu*& pmm = MainMenuTest::pmm;
PlayMenu*& ppm = PlayMenuTest::ppm;
std::unordered_set<Window*>& WindowsWithOpenExit = ExitMenuTest::WindowsWithOpenExit;
GettingStarted();
sf::Event event;
MainMenuTest::PlayButtonEvent(event);
MainWindow->MakeFrame();
EXPECT_EQ(pmm, nullptr);
EXPECT_NE(ppm, nullptr);
EXPECT_EQ(WindowsWithOpenExit.size(), 0);
delete MainWindow;
EXPECT_EQ(pmm, nullptr);
EXPECT_EQ(ppm, nullptr);
EXPECT_EQ(WindowsWithOpenExit.size(), 0);
}

TEST(GITest, GITest3) {
MainMenu*& pmm = MainMenuTest::pmm;
PlayMenu*& ppm = PlayMenuTest::ppm;
std::unordered_set<Window*>& WindowsWithOpenExit = ExitMenuTest::WindowsWithOpenExit;
GettingStarted();
sf::Event event;
MainMenuTest::PlayButtonEvent(event);
MainWindow->MakeFrame();
PlayMenuTest::BackButtonEvent(event);
MainWindow->MakeFrame();
EXPECT_NE(pmm, nullptr);
EXPECT_EQ(ppm, nullptr);
EXPECT_EQ(WindowsWithOpenExit.size(), 0);
delete MainWindow;
EXPECT_EQ(pmm, nullptr);
EXPECT_EQ(ppm, nullptr);
EXPECT_EQ(WindowsWithOpenExit.size(), 0);
}

TEST(GITest, GITest4) {
MainMenu*& pmm = MainMenuTest::pmm;
PlayMenu*& ppm = PlayMenuTest::ppm;
std::unordered_set<Window*>& WindowsWithOpenExit = ExitMenuTest::WindowsWithOpenExit;
GettingStarted();
sf::Event event;
MainMenuTest::ExitButtonEvent(event);
MainWindow->MakeFrame();
EXPECT_NE(pmm, nullptr);
EXPECT_EQ(ppm, nullptr);
EXPECT_EQ(WindowsWithOpenExit.size(), 1);
Window* ExitWindow;
if (*Window::WindowsToDisplay.begin() == MainWindow) {
ExitWindow = *Window::WindowsToDisplay.end();
} else {
ExitWindow = *Window::WindowsToDisplay.begin();
}
Essence* peme = *ExitWindow->AllEssences.begin();
ExitMenuTest* pem = static_cast<ExitMenuTest*>(peme);
pem->NOButtonEvent(event);
ExitWindow->MakeFrame();
EXPECT_TRUE(ExitWindow->IsWaitingForDeleting());
EXPECT_NE(pmm, nullptr);
EXPECT_EQ(ppm, nullptr);
EXPECT_EQ(WindowsWithOpenExit.size(), 0);
delete ExitWindow;
delete MainWindow;
EXPECT_EQ(pmm, nullptr);
EXPECT_EQ(ppm, nullptr);
EXPECT_EQ(WindowsWithOpenExit.size(), 0);
}

TEST(GITest, GITest5) {
MainMenu*& pmm = MainMenuTest::pmm;
PlayMenu*& ppm = PlayMenuTest::ppm;
std::unordered_set<Window*>& WindowsWithOpenExit = ExitMenuTest::WindowsWithOpenExit;
GettingStarted();
sf::Event event;
MainMenuTest::ExitButtonEvent(event);
MainWindow->MakeFrame();
EXPECT_NE(pmm, nullptr);
EXPECT_EQ(ppm, nullptr);
EXPECT_EQ(WindowsWithOpenExit.size(), 1);
Window* ExitWindow;
if (*Window::WindowsToDisplay.begin() == MainWindow) {
ExitWindow = *Window::WindowsToDisplay.end();
} else {
ExitWindow = *Window::WindowsToDisplay.begin();
}
Essence* peme = *ExitWindow->AllEssences.begin();
ExitMenuTest* pem = static_cast<ExitMenuTest*>(peme);
pem->YESButtonEvent(event);
ExitWindow->MakeFrame();
EXPECT_TRUE(MainWindow->IsWaitingForDeleting());
EXPECT_TRUE(ExitWindow->IsWaitingForDeleting());
delete ExitWindow;
delete MainWindow;
EXPECT_EQ(pmm, nullptr);
EXPECT_EQ(ppm, nullptr);
EXPECT_EQ(WindowsWithOpenExit.size(), 0);
}

TEST(GITest, GITest6) {
MainMenu*& pmm = MainMenuTest::pmm;
PlayMenu*& ppm = PlayMenuTest::ppm;
std::unordered_set<Window*>& WindowsWithOpenExit = ExitMenuTest::WindowsWithOpenExit;
GettingStarted();
EXPECT_NE(pmm, nullptr);
EXPECT_EQ(ppm, nullptr);
EXPECT_EQ(WindowsWithOpenExit.size(), 0);
sf::Event event;
MainMenuTest::PlayButtonEvent(event);
MainWindow->MakeFrame();
EXPECT_EQ(pmm, nullptr);
EXPECT_NE(ppm, nullptr);
EXPECT_EQ(WindowsWithOpenExit.size(), 0);
PlayMenuTest::BackButtonEvent(event);
MainWindow->MakeFrame();
EXPECT_NE(pmm, nullptr);
EXPECT_EQ(ppm, nullptr);
EXPECT_EQ(WindowsWithOpenExit.size(), 0);
MainMenuTest::ExitButtonEvent(event);
MainWindow->MakeFrame();
EXPECT_NE(pmm, nullptr);
EXPECT_EQ(ppm, nullptr);
EXPECT_EQ(WindowsWithOpenExit.size(), 1);
Window* ExitWindow;
if (*Window::WindowsToDisplay.begin() == MainWindow) {
ExitWindow = *Window::WindowsToDisplay.end();
} else {
ExitWindow = *Window::WindowsToDisplay.begin();
}
Essence* peme = *ExitWindow->AllEssences.begin();
ExitMenuTest* pem = static_cast<ExitMenuTest*>(peme);
pem->NOButtonEvent(event);
ExitWindow->MakeFrame();
EXPECT_TRUE(ExitWindow->IsWaitingForDeleting());
EXPECT_NE(pmm, nullptr);
EXPECT_EQ(ppm, nullptr);
EXPECT_EQ(WindowsWithOpenExit.size(), 0);
Window::WindowsToDisplay.erase(ExitWindow);
delete ExitWindow;
MainMenuTest::ExitButtonEvent(event);
MainWindow->MakeFrame();
EXPECT_NE(pmm, nullptr);
EXPECT_EQ(ppm, nullptr);
EXPECT_EQ(WindowsWithOpenExit.size(), 1);
if (*Window::WindowsToDisplay.begin() == MainWindow) {
ExitWindow = *Window::WindowsToDisplay.end();
} else {
ExitWindow = *Window::WindowsToDisplay.begin();
}
peme = *ExitWindow->AllEssences.begin();
pem = static_cast<ExitMenuTest*>(peme);
pem->YESButtonEvent(event);
ExitWindow->MakeFrame();
EXPECT_TRUE(MainWindow->IsWaitingForDeleting());
EXPECT_TRUE(ExitWindow->IsWaitingForDeleting());
delete ExitWindow;
delete MainWindow;
EXPECT_EQ(pmm, nullptr);
EXPECT_EQ(ppm, nullptr);
EXPECT_EQ(WindowsWithOpenExit.size(), 0);
}
