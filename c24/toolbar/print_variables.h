#ifndef C24_TOOLBAR_PRINT_VARIABLES_H_
#define C24_TOOLBAR_PRINT_VARIABLES_H_

// Widget "ToolPrintVariables" prints values of chosen variables. For details on
// how to use it, see below the description of class ToolPrintVariables.

#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "SFGUI/SFGUI.hpp"
#include "SFGUI/Widgets.hpp"

namespace c24 {
namespace toolbar {

// Custom widget that prints current value of specified variable. It holds raw
// pointer to the variable (of arbitrary type) and pointer to the function that
// takes variable of this type and returns std::string. Text is updated
// regularly but at least update_after_seconds seconds after the previous
// update. If you set update_after_seconds to negative value this restriction
// doesn't apply.
//
// Example usage:
//
// int x = 5;
// auto widget_ptr = VariableLabel<int>::Create(&x, &std::to_string, 1.5);
// add widget_ptr to desktop;
// // Now it shows text "5"
// x = 4;
// // It shows "5" but after 1.5s it shows "4".
template <class T>
class VariableLabel : public sfg::Label {
 public:
  typedef std::shared_ptr<VariableLabel> Ptr;
  typedef std::shared_ptr<const VariableLabel> PtrConst;

  VariableLabel(T* observed_variable, std::string (*print)(T),
                float update_after_seconds);
  static Ptr Create(T* observed_variable, std::string (*print)(T),
                    float update_after_seconds);

 protected:
  void HandleUpdate(float seconds) override;

 private:
  T* observed_variable_;
  float update_after_seconds_;
  float from_last_update_;
  std::string (*print_)(T);
};

template <class T>
VariableLabel<T>::VariableLabel(T* observed_variable, std::string (*print)(T),
                                float update_after_seconds)
    : Label((*print)(*observed_variable)),
      print_(print),
      observed_variable_(observed_variable),
      update_after_seconds_(update_after_seconds),
      from_last_update_(0) {}

template <class T>
typename VariableLabel<T>::Ptr VariableLabel<T>::Create(
    T* observed_variable, std::string (*print)(T), float update_after_seconds) {
  Ptr label(new VariableLabel(observed_variable, print, update_after_seconds));
  label->RequestResize();
  return label;
}

template <class T>
void VariableLabel<T>::HandleUpdate(float seconds) {
  from_last_update_ += seconds;
  if (from_last_update_ >= update_after_seconds_) {
    SetText((*print_)(*observed_variable_));
    from_last_update_ = 0;
  }
}

// This widget lets you observe variables. It contains table with their names
// and pointers to their values. It can look like this:
//
// +----------------------+----------------------------+
// |variable1:             10                          |
// |variable2:             3.5                         |
// |some_string_variable:  abcdefgh                    |
// |player:                player<pos<2,3>, score: 5>  |
// +----------------------+----------------------------+
//
// For each variable you can specify function that should be used to print its
// value. If it isn't specified, std::to_string is used.
//
// Example usage:
//
// std::string print_player(Player p) { ... }
//    .
//    .
//    .
// sfg::Desktop desktop;
//
// int var1 = 10;
// double var2 = 3.5;
// std::string str = "abcdefgh";
// Player player(Pos(2, 3), 5);
//
// ToolPrintVariables tool_print_variables;
// tool_print_variables.AddVariable("variable1", &var1, 0.01);
// tool_print_variables.AddVariable("variable2", &var2, 0.01);
// tool_print_variables.AddVariable("some_string_variables", &str, 0.05);
// tool_print_variables.AddVariableCustomPrint("player", &player, &print_player, 0.1);
//
// desktop.Add(tool_print_variables.WindowPtr());
class ToolPrintVariables {
 public:
  ToolPrintVariables();
  sfg::Window::Ptr WindowPtr();
  template <class T>
  void AddVariable(const std::string& name, T* x, float update_after_seconds);
  template <class T>
  void AddVariableCustomPrint(const std::string& name, T* x,
                              std::string (*print)(T),
                              float update_after_seconds);

 private:
  void AddRowToTable(const std::string& name, sfg::Widget::Ptr var_val);

  int next_row_num_;
  sfg::Window::Ptr window_;
  sfg::Table::Ptr table_;
};

template <class T>
void ToolPrintVariables::AddVariable(const std::string& name, T* x,
                                     float update_after_seconds) {
  AddRowToTable(
      name, VariableLabel<T>::Create(x, &std::to_string, update_after_seconds));
}
template <class T>
void ToolPrintVariables::AddVariableCustomPrint(const std::string& name, T* x,
                                                std::string (*print)(T),
                                                float update_after_seconds) {
  AddRowToTable(name, VariableLabel<T>::Create(x, print, update_after_seconds));
}

}  // namespace toolbar
}  // namespace c24

#endif  // C24_TOOLBAR_PRINT_VARIABLES_H_
