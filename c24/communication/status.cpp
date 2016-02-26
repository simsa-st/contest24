#include "c24/communication/status.h"

namespace c24 {
namespace communication {

Status::Status()
    : socket_status(sf::Socket::Done), error_code(0), error_mask(0) {}
Status::Status(sf::Socket::Status _socket_status) : Status() {
  SetSocketError(_socket_status);
}
Status::Status(int _error_code, const std::string& _error_message) : Status() {
  SetServerError(_error_code, _error_message);
}

bool Status::Ok() const { return error_mask == 0; }
bool Status::ErrorOccurred(ErrorType error_type) const {
  if (error_type == ErrorType::NONE) return error_mask == 0;
  return error_mask & (1 << error_type);
}

void Status::SetSocketError(sf::Socket::Status _socket_status) {
  if (_socket_status != sf::Socket::Done) {
    error_mask |= 1 << ErrorType::SOCKET;
    socket_status = _socket_status;
  }
}
void Status::SetServerError(int _error_code, const std::string& _error_message) {
  if (_error_code != 0) {
    error_mask |= 1 << ErrorType::SERVER;
    error_code = _error_code;
    error_message = _error_message;
  }
}
void Status::SetNoDataReceivedError() {
  error_mask |= 1 << ErrorType::NO_DATA_RECEIVED;
}

std::string Status::Print() const {
  std::string str = "Status<";
  if (ErrorOccurred(ErrorType::NONE)) {
    str += "OK";
  } else {
    str += "ERROR:";
    if (ErrorOccurred(ErrorType::SOCKET)) {
      str += " [in socket: " + std::to_string(socket_status) + "]";
    }
    if (ErrorOccurred(ErrorType::SERVER)) {
      str += " [server error code: " + std::to_string(error_code) +
             ", message: " + error_message + "]";
    }
    if (ErrorOccurred(ErrorType::NO_DATA_RECEIVED)) {
      str += " [no data received in blocking mode]";
    }
  }
  str.push_back('>');
  return str;
}

std::ostream& operator<<(std::ostream& out, const Status& status) {
  return out << status.Print();
}

}  // namespace communication
}  // namespace c24
