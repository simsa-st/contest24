#ifndef COMMUNICATION_STREAM_H_
#define COMMUNICATION_STREAM_H_

#include <memory>
#include <string>

#include "c24/communication/stream_backend_interface.h"

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
  bool Connected() const;

  // Non-blocking call that returns if there is a message available on the
  // stream.
  bool MessageAvailable() const;

  // Blocking call that receives a message without the newline character.
  std::string GetMessage() const;

  // Send a message and if 'newline' is true, append newline. Returns true if
  // the message was sent successfully.
  bool SendMessage(const std::string& msg, bool newline = true) const;

  // Send a message, then receive reply and check if it is equal to 'expected'.
  // Returns true if the message was sent succesfully and expected value
  // (without newline) was received.
  bool SendMessageWithCheck(const std::string& msg, bool newline = true,
                            const char* expected = "OK") const;
 private:
  std::unique_ptr<StreamBackendInterface> stream_backend_;
};

}  // namespace communication
}  // namespace c24
#endif //  COMMUNICATION_STREAM_H_
