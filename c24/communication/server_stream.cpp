#include "server_stream.h"

namespace c24 {
namespace communication {

ServerStream::ServerStream(std::function<
    std::unique_ptr<StreamBackendInterface>()> get_stream_backend) {
  Connect(get_stream_backend);
}

void ServerStream::ConnectAgain() { Connect(last_get_stream_backend_); }

void ServerStream::Connect(std::function<
    std::unique_ptr<StreamBackendInterface>()> get_stream_backend) {
  waiting_for_future_stream_ = true;
  last_get_stream_backend_ = get_stream_backend;
  // Construct the stream in different thread.
  future_stream_ = std::async(std::launch::async, [=] {
    return Stream(std::move(get_stream_backend()));
  });
}

bool ServerStream::Connected() {
  // If there is new connection ready, connect.
  if (waiting_for_future_stream_ &&
      future_stream_.wait_for(std::chrono::seconds(0)) ==
          std::future_status::ready) {
    SetStreamFromFuture();
  }
  return stream_ != nullptr && stream_->Connected();
}

bool ServerStream::Disconnected() {
  return !waiting_for_future_stream_ && !Connected();
}

bool ServerStream::MsgAvailable() {
  return Connected() && stream_->MsgAvailable();
}

std::string ServerStream::GetMsg() {
  if (Connected()) {
    return stream_->GetMsg();
  }
  return "";
}

// The message is returned through pointer to string rather than through
// std::future<std::string> to be sure that the whole message is copied when
// the condition variable is notified.
std::future<void> ServerStream::GetFutureMsg(std::condition_variable& cv,
                                             std::string* msg) {
  return std::async(std::launch::async, [&cv, this, msg] {
    *msg = GetMsg();
    cv.notify_one();
  });
}

bool ServerStream::SendMsg(const std::string& msg) {
  if (Connected()) {
    return stream_->SendMsg(msg);
  }
  return false;
}

Stream* ServerStream::GetStream() {
  if (Connected()) {
    return stream_.get();
  }
  return nullptr;
}

void ServerStream::SetStreamFromFuture() {
  stream_ = std::unique_ptr<Stream>(new Stream(future_stream_.get()));
  waiting_for_future_stream_ = false;
}

}  // namespace communication
}  // namespace c24
