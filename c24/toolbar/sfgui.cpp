#include "sfgui.h"

SfguiWindow::SfguiWindow(sfg::SFGUI* sfgui, int screen_width, int screen_height)
    : sfgui_(sfgui),
      render_window_(
          sf::VideoMode(screen_width, screen_height), "Contest24 toolbar",
          sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize),
      last_update_(std::chrono::system_clock::now()) {
  // We're not using SFML to render anything in this program, so reset OpenGL
  // states. Otherwise we wouldn't see anything.
  render_window_.resetGLStates();
}

void SfguiWindow::ProcessEvents() {
  sf::Event event;
  while (render_window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      close();
    } else {
      desktop_.HandleEvent(event);
    }
  }
}

void SfguiWindow::Render() {
  auto now = std::chrono::system_clock::now();
  // Update the desktop with information how many seconds ago was the last
  // update.
  desktop_.Update((float)(std::chrono::duration_cast<std::chrono::microseconds>(
                              now - last_update_).count()) /
                  1000000.f);
  last_update_ = now;
  render_window_.clear();
  sfgui_->Display(render_window_);
  render_window_.display();
}

void SfguiWindow::AddWindow(sfg::Window::Ptr window) { desktop_.Add(window); }
