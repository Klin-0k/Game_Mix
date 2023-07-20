#include <Global_Definitions.h>

int main() {
  GettingStarted();
  while (!Window::WindowsToDisplay.empty()) {
    for (auto window_it = Window::WindowsToDisplay.begin(); window_it != Window::WindowsToDisplay.end();) {
      auto window = *(window_it++);
      window->MakeFrame();
      if (window->IsWaitingForDeleting()) {
        Window::WindowsToDisplay.erase(window);
        delete window;
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
  }
  return 0;
}
