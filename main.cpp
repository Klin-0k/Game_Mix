#include "Global_Classes.cpp"

int main() {
  GettingStarted();
  while (true) {
    for (auto window : Window::WindowsToDisplay) {
      window->MakeFrame();
      if (window->IsWaitingForDeleting()) {
        Window::WindowsToDisplay.erase(window);
        delete window;
        break;
      }
      if (Window::ProgramIsWaitingForClosing()) {
        while (!Window::WindowsToDisplay.empty()) {
          Window* i = *Window::WindowsToDisplay.begin();
          Window::WindowsToDisplay.erase(i);
          delete i;
        }
        break;
      }
    }
    if (Window::WindowsToDisplay.empty()) {
      break;
    }
  }
  return 0;
}
