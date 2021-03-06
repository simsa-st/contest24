#ifndef COMMUNICATION_STREAM_BACKEND_INTERFACE_H_
#define COMMUNICATION_STREAM_BACKEND_INTERFACE_H_

#include <string>
#include "c24/communication/status.h"

namespace c24 {
namespace communication {

// Interface for basic streams -- sending and receiving messages. Class that
// implements this interface is just backend for sending and receiving raw
// messages. It is then wrapped in Stream class that logs the communication.
// Avoid using StreamBackendInterface directly.
class StreamBackendInterface {
 public:
  virtual ~StreamBackendInterface() {}

  // Non-blocking call to check if there is a message available on the stream.
  virtual bool MsgAvailable() = 0;

  // Blocking call that receives one line. Returned string does not contain the
  // newline character.
  virtual std::string GetMsg() = 0;

  // Blocking call that sends a message (without newline). Returns true on
  // success.
  virtual bool SendMsg(const std::string& msg) = 0;

  // Returns if the connection is still valid.
  virtual bool Connected() const = 0;

  // Try to reconnect.
  virtual void Reconnect() = 0;

  // Returns the status of last operation.
  virtual Status LastStatus() const = 0;
};

}  // namespace communication
}  // namespace c24

#endif //  COMMUNICATION_STREAM_BACKEND_INTERFACE_H_
