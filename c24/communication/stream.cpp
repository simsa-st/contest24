#include "c24/communication/stream.h"

#include <chrono>
#include <string>
#include <thread>

#include "easylogging++.h"

namespace c24 {
namespace communication {

Stream::Stream(std::unique_ptr<StreamBackendInterface> stream_backend)
    : stream_backend_(std::move(stream_backend)) {}

bool Stream::Connected() {
  status_ = Status();
  if (stream_backend_ == nullptr) {
    return false;
  }
  return stream_backend_->Connected();
}

bool Stream::MsgAvailable() {
  CheckConnectionAndReconnect();
  status_ = Status();
  CHECK(stream_backend_ != nullptr);
  return stream_backend_->MsgAvailable();
}

std::string Stream::GetMsg() {
  CheckConnectionAndReconnect();
  status_ = Status();
  CHECK(stream_backend_ != nullptr);
  std::string msg = stream_backend_->GetMsg();
  LOG(INFO) << "Received: \"" << msg << "\"";
  return msg;
}

bool Stream::SendMsg(const std::string& msg, bool newline) {
  CheckConnectionAndReconnect();
  status_ = Status();
  CHECK(stream_backend_ != nullptr);
  // Put two spaces after Sending so it is lined up with messages after
  // Received.
  LOG(INFO) << "Sending:  \"" << msg << "\"";
  const std::string& msg_to_send = newline ? msg + '\n' : msg;
  return stream_backend_->SendMsg(msg_to_send);
}

Status Stream::LastStatus() const {
  if (!status_.Ok()) return status_;
  CHECK(stream_backend_ != nullptr);
  return stream_backend_->LastStatus();
}

bool Stream::GetMsgWithCheck(const char* expected) {
  std::string msg_ok = GetMsg();
  if (msg_ok != expected) {
    status_ = stream_backend_->LastStatus();
    std::stringstream ss(msg_ok);
    std::string first_word;
    ss >> first_word;
    int error_code;
    ss >> error_code;
    if (first_word == "ERROR") {
      status_.SetServerError(error_code, ss.str());
    }
    LOG(ERROR) << "Expected \"" << expected << "\" but received \"" << msg_ok
               << "\"";
    return false;
  }
  return true;
}

bool Stream::SendMsgWithCheck(const std::string& msg, bool newline,
                              const char* expected) {
  status_ = Status();
  bool success = SendMsg(msg, newline);
  if (success) {
    success = GetMsgWithCheck(expected);
  }
  return success;
}

void Stream::CheckConnectionAndReconnect() {
  if (Connected()) return;
  stream_backend_->Reconnect();
  while (!Connected()) {
    std::this_thread::sleep_for(
        std::chrono::milliseconds(TIME_BETWEEN_RECONNECT_TRIES_MILLISECONDS));
    stream_backend_->Reconnect();
  }
}

}  // namespace communication
}  // namespace c24
