#ifndef COMMUNICATION_SERVER_STREAM_H_
#define COMMUNICATION_SERVER_STREAM_H_

#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <string>

#include "c24/communication/stream.h"
#include "c24/communication/stream_backend_interface.h"

namespace c24 {
namespace communication {

// This class wraps Stream. It is meant for streams that also manage their
// connection. It runs the constructor of stream backend in different thread so
// that it doesn't block the execution if we have to wait, for example for
// client to connect.
//
// There are two methods that check if connection is established:
// 1) Connected()
//   returns true if we are currently connected, so if we are able to send and
//   receive messagges.
// 2) Disconnected()
//   returns true if Connected() is false and we are not currently waiting for
//   connection to establish.
//
// You should only try to connect again if Disconnected() is true or if you want
// to use different backend (e.g. change the port).
//
// EXAMPLE USAGE:
// =============
//
// int port = 5500;
// player_stream = c24::communication::ServerStream([port] {
//   return unique_ptr<StreamBackendInterface>(new StreamTcpServer(port));
// });
//
// while (true) {
//   if (player_stream.Disconnected()) {
//     player_stream.ConnectAgain();
//   }
//   if (player_stream.Connected()) {
//     if (player_stream.MsgAvailable()) {
//       std::string msg = player_stream.GetMsg();
//       player_stream.SendOk();
//       player_stream.SendMsg(ReplyToMsg(msg));
//     }
//   }
// }
class ServerStream {
 public:
  // You have to provide a function that returns the stream backend that should
  // be used. This allows to call the constructor of stream backend in different
  // thread so it doesn't block the execution if we have to wait for the
  // connection to establish.
  ServerStream(std::function<std::unique_ptr<StreamBackendInterface>()>
                   get_stream_backend);

  // Connect again using the same function to construct stream backend.
  void ConnectAgain();

  // Connect again but using different function.
  void Connect(std::function<std::unique_ptr<StreamBackendInterface>()>
                   get_stream_backend);

  // Check if the connection is ok, i.e. we are able to send and receive
  // messages.
  bool Connected();

  // Check if we are not connected and also not waiting for connection to
  // establish.
  bool Disconnected();

  // You should use rather these methods then using GetStream. They only do the
  // requested operation if Connected() is true.
  // Returns true if there is a message available. This is a non-blocking call.
  bool MsgAvailable();
  // Blocks until the message is received. If not connected, returns empty string.
  std::string GetMsg();
  // Wait for the message in a new thread and return the future to recognize
  // when the message was received. Store the message into *msg and notify the
  // condition variable after message is received.
  std::future<void> GetFutureMsg(std::condition_variable& cv, std::string* msg);

  // If connected, sends message over stream and returns if it was sent
  // succesfully. Otherwise returns false.
  bool SendMsg(const std::string& msg);
  void ReplyWithOk() { SendMsg("OK"); }
  void ReplyWithError(int error_code, const std::string& error_msg) {
    SendMsg("ERROR " + std::to_string(error_code) + " " + error_msg);
  }
  void ReplyWithError(const std::pair<int, std::string>& error) {
    ReplyWithError(error.first, error.second);
  }

  // Returns the underlying stream or, if not connected, returns nullptr.
  Stream* GetStream();

 private:
  // Retrieve constructed stream from future_stream_ to stream_.
  void SetStreamFromFuture();

  // Underlying stream.
  std::unique_ptr<Stream> stream_;
  // Last function used to start the connection.
  std::function<std::unique_ptr<StreamBackendInterface>()>
      last_get_stream_backend_;
  // Holds the result of construction of underlying stream.
  std::future<Stream> future_stream_;
  // True if we are currently waiting for stream to be constructed.
  bool waiting_for_future_stream_;
};

}  // namespace communication
}  // namespace c24
#endif  // COMMUNICATION_SERVER_STREAM_H_
