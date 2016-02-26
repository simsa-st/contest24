#ifndef COMMUNICATION_STATUS_H_
#define COMMUNICATION_STATUS_H_

#include <array>
#include <string>
#include <SFML/Network.hpp>

// Class that holds errors that occurred when receiving/sending a message. On
// one hand these are low-level errors such as the sf::Socket::Status status
// and on the other hand this can be an error code with error message received
// on a higher level.
// Special type of error is NO_DATA_RECEIVED that indicates no data was
// received even when trying to read in blocking mode.
//
// Status can be created either empty (=no error), from sf::Socket::Status or
// using custom error code and error message. Other types of errors can than be
// added.
//
// Example:
// sf::TcpSocket::Status socket_status = socket_.receive(...);
// c24::communication::Status status(socket_status);
// status.SetServerError(101, "Unexpected behaviour");
//
// ...
// if (status.ErrorOccurred(c24::communication::ErrorType::SERVER)) {
//   std::cout << "Error with code " << status.error_code << " and message "
//             << status.error_message;
// }

namespace c24 {
namespace communication {

enum ErrorType {
  NONE = 0,
  SOCKET,
  SERVER,
  NO_DATA_RECEIVED
};

struct Status { 
  sf::Socket::Status socket_status;
  int error_code;
  std::string error_message;

  // Default status, no problem occurred.
  Status();
  // Problem with socket_status.
  Status(sf::Socket::Status _socket_status);
  // Custom error code and message. Error code 0 means no error.
  Status(int _error_code, const std::string& _error_message);

  bool Ok() const;
  bool ErrorOccurred(ErrorType error_type) const;

  void SetSocketError(sf::Socket::Status _socket_status);
  void SetServerError(int _error_code, const std::string& _error_message);
  void SetNoDataReceivedError();

  std::string Print() const;

 private:
  // Every bit represents if the error of corresponding ErrorType occurred.
  int error_mask;
};

std::ostream& operator<<(std::ostream& out, const Status& status);

}  // namespace communication
}  // namespace c24
#endif  // COMMUNICATION_STATUS_H_
