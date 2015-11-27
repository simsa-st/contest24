#include "print_variables.h"

namespace c24 {
namespace toolbar {

ToolPrintVariables::ToolPrintVariables()
    : next_row_num_(0),
      window_(sfg::Window::Create()),
      table_(sfg::Table::Create()) {
  window_->SetTitle("Observed variables");
  window_->Add(table_);
}
sfg::Window::Ptr ToolPrintVariables::WindowPtr() { return window_; }

void ToolPrintVariables::AddRowToTable(const std::string& name,
                                       sfg::Widget::Ptr var_val) {
  auto var_name = sfg::Label::Create(name.c_str());
  table_->Attach(var_name, sf::Rect<sf::Uint32>(0, next_row_num_, 1, 1),
                 sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL,
                 sf::Vector2f(10.f, 10.f));
  table_->Attach(var_val, sf::Rect<sf::Uint32>(1, next_row_num_, 1, 1),
                 sfg::Table::FILL | sfg::Table::EXPAND, sfg::Table::FILL,
                 sf::Vector2f(10.f, 10.f));
  ++next_row_num_;
}

}  // namespace toolbar
}  // namespace c24
