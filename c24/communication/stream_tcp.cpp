#include "c24/communication/stream_tcp.h"

#include <chrono>
#include <thread>

#include "easylogging++.h"

namespace c24 {
namespace communication {

bool StreamTcp::MsgAvailable() {
  // Check if there is some message in the queue already.
  if (!complete_messages_.empty()) {
    status_ = Status();
    return true;
  }
  if (socket_.isBlocking()) {
    socket_.setBlocking(false);
  }
  std::size_t received;
  sf::TcpSocket::Status socket_status = GetData(&received);
  status_ = Status(socket_status);
  if (socket_status == sf::TcpSocket::Error ||
      socket_status == sf::TcpSocket::Disconnected) {
    LOG(ERROR) << "TcpSocket error. Status code: " << socket_status;
  }
  // if status == sf::TcpSocket::NotReady no message is yet available.
  return socket_status == sf::TcpSocket::Done;
}

std::string StreamTcp::GetMsg() {
  status_ = Status();
  if (complete_messages_.empty()) {
    if (!socket_.isBlocking()) {
      socket_.setBlocking(true);
    }
    int not_ready_count = 0;
    // More than one read may be necessary if the message is longer than
    // _TCP_BUFFER_SIZE.
    while (complete_messages_.empty()) {
      std::size_t received;
      sf::TcpSocket::Status socket_status = GetData(&received);
      status_ = Status(socket_status);
      if (socket_status == sf::TcpSocket::NotReady ||
          socket_status == sf::TcpSocket::Error ||
          socket_status == sf::TcpSocket::Disconnected) {
        LOG(ERROR)
            << "TcpSocket error when trying to receive data. Status code: "
            << socket_status;
        if (socket_status == sf::TcpSocket::NotReady) {
          ++not_ready_count;
          if (not_ready_count == NOT_READY_COUNT_THRESHOLD) {
            LOG(ERROR) << "Socket still not ready, threshold for the number of "
                          "retries (" << NOT_READY_COUNT_THRESHOLD
                       << ") hit. Returning empty string";
            status_.SetNoDataReceivedError();
            return "";
          }
          std::this_thread::sleep_for(std::chrono::microseconds(
              TIME_TO_WAIT_WHEN_SOCKET_NOT_READY_MICROS));
          continue;
        }
        status_.SetNoDataReceivedError();
        return "";
      }
      if (received == 0) {
        LOG(ERROR) << "Trying to read in blocking mode but no data received";
        status_.SetNoDataReceivedError();
        return "";
      }
    }
  }
  std::string msg = complete_messages_.front();
  complete_messages_.pop();
  return msg;
}

bool StreamTcp::SendMsg(const std::string& msg) {
  // Set the socket to blocking mode to guarantee the whole message is sent.
  if (!socket_.isBlocking()) {
    socket_.setBlocking(true);
  }
  sf::TcpSocket::Status socket_status = socket_.send(msg.c_str(), msg.length());
  // Reinitialize the current status.
  status_ = Status(socket_status);
  if (socket_status != sf::TcpSocket::Done) {
    if (socket_status == sf::TcpSocket::Disconnected) {
      connected_ = false;
    }
    LOG(ERROR) << "TcpSocket error. Status code: " << socket_status;
  }
  return socket_status == sf::TcpSocket::Done;
}

bool StreamTcp::Connected() const {
  return connected_;
}

// Internally the class remembers queue of received messages. Every time some
// data is received it is stored in buffer_[] and the received data is
// processed. When newline character is found, message is saved to queue
// complete_messages_. Last not complete message (not yet terminated by newline)
// is saved in not_complete_message_.
sf::TcpSocket::Status StreamTcp::GetData(std::size_t* received) {
  sf::TcpSocket::Status status =
      socket_.receive(buffer_, _TCP_BUFFER_SIZE, *received);
  if (status == sf::TcpSocket::Disconnected) {
    connected_ = false;
  }
  if (status == sf::TcpSocket::Done) {
    for (std::size_t i = 0; i < *received; ++i) {
      if (buffer_[i] == '\n') {
        complete_messages_.push(not_complete_message_);
        not_complete_message_ = "";
      } else {
        not_complete_message_.push_back(buffer_[i]);
      }
    }
  }
  return status;
}

}  // namespace communication
}  // namespace c24
