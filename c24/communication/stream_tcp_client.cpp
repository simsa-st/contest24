#include "c24/communication/stream_tcp_client.h"

#include "easylogging++.h"

namespace c24 {
namespace communication {

StreamTcpClient::StreamTcpClient(const sf::IpAddress& ip_address,
                                 unsigned short port)
    : ip_address_(ip_address), port_(port) {
  sf::Socket::Status socket_status = socket_.connect(ip_address, port);
  status_ = Status(socket_status);
  if (socket_status == sf::Socket::Done) {
    connected_ = true;
  } else {
    connected_ = false;
    LOG(ERROR) << "Unable to connect to host. IP address: " << ip_address
               << ", port: " << port;
  }
}
StreamTcpClient::StreamTcpClient(const std::string& ip_address, unsigned short port)
    : StreamTcpClient(sf::IpAddress(ip_address), port) {}
StreamTcpClient::StreamTcpClient(const char* ip_address, unsigned short port)
      : StreamTcpClient(sf::IpAddress(ip_address), port) {}

void StreamTcpClient::Reconnect() {
  StreamTcpClient(ip_address_, port_);
}

}  // namespace communication
}  // namespace c24
