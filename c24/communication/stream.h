#ifndef COMMUNICATION_STREAM_H_
#define COMMUNICATION_STREAM_H_

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "c24/communication/status.h"
#include "c24/communication/stream_backend_interface.h"

#define TIME_BETWEEN_RECONNECT_TRIES_MILLISECONDS 500

namespace c24 {
namespace communication {

// Class for data exchange. It wraps some implementation of
// StreamBackendInterface, logs the communication and provides some useful
// methods for convenience.
class Stream {
 public:
  Stream() {}

  // TODO(simsa.st): Add an argument to the constructor that specifies where to
  // log the communication.
  Stream(std::unique_ptr<StreamBackendInterface> stream_backend);

  // Return if the other side of the stream is still connected.
  bool Connected();

  // Non-blocking call that returns if there is a message available on the
  // stream.
  bool MsgAvailable();

  // Blocking call that receives a message without the newline character.
  std::string GetMsg();

  // Send a message and if 'newline' is true, append newline. Returns true if
  // the message was sent successfully.
  bool SendMsg(const std::string& msg, bool newline = true);

  // Return the status of the last operation.
  Status LastStatus() const;

  // Get message and check it has the value "expected".
  // Also, if the received message is not correct, try to extract error from
  // the message. Error is expected to be in the format:
  // ERROR number error_message
  bool GetMsgWithCheck(const char* expected = "OK");

  // Send a message, then receive reply and check if it is equal to 'expected'.
  // Returns true if the message was sent succesfully and expected value
  // (without newline) was received.
  bool SendMsgWithCheck(const std::string& msg, bool newline = true,
                        const char* expected = "OK");

  // Receive a message and extract "cnt" variables of type T from it using
  // stringstream. Also return rest of the message in the second argument if it
  // is not nullptr.
  template <typename T>
  std::vector<T> GetVectorOf(int cnt, std::string* rest_of_msg);

  // When you don't need the rest of the message.
  template <typename T>
  std::vector<T> GetVectorOf(int cnt) {
    return GetVectorOf<T>(cnt, nullptr);
  }

 private:
  // If not connected, try to reconnect until successful.
  void CheckConnectionAndReconnect();

  Status status_;
  std::unique_ptr<StreamBackendInterface> stream_backend_;
};

// Implementation needs to be in the header file because of the template.
template <typename T>
std::vector<T> Stream::GetVectorOf(int cnt, std::string* rest_of_msg) {
  std::string msg = GetMsg();
  std::stringstream sstream(msg);
  std::vector<T> vector_of;
  for (int i = 0; i < cnt; ++i) {
    T val;
    sstream >> val;
    vector_of.push_back(val);
  }
  if (rest_of_msg != nullptr) {
    *rest_of_msg = sstream.str();
  }
  return vector_of;
}

}  // namespace communication
}  // namespace c24
#endif //  COMMUNICATION_STREAM_H_
