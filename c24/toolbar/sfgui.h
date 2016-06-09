#ifndef C24_TOOLBAR_SFGUI_H_
#define C24_TOOLBAR_SFGUI_H_
#include <chrono>

#include <SFML/Graphics.hpp>

#include "SFGUI/SFGUI.hpp"
#include "SFGUI/Widgets.hpp"

namespace c24 {
namespace toolbar {

// Window that contains the SFGUI widgets.
class SfguiWindow {
 public:
  SfguiWindow(sfg::SFGUI* sfgui, int screen_width, int screen_height);
  void AddWindow(sfg::Window::Ptr window);
  bool isOpen() const { return render_window_.isOpen(); }
  void close() { render_window_.close(); }
  void ProcessEvents();
  void Render();

 private:
  sfg::SFGUI* sfgui_;
  sfg::Desktop desktop_;
  sf::RenderWindow render_window_;
  std::chrono::system_clock::time_point last_update_;
};

}  // toolbar
}  // sfgui

#endif  // C24_TOOLBAR_SFGUI_H_
