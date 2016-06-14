// This example shows how to use the TCP server. It listens at given port,
// receives one message and sends one message.

#include <memory>
#include <iostream>

#include "easylogging++.h"
#include "gflags/gflags.h"
#include "c24/communication/stream.h"
#include "c24/communication/stream_tcp_server.h"
#include "c24/communication/stream_backend_interface.h"

INITIALIZE_EASYLOGGINGPP

using c24::communication::StreamBackendInterface;
using c24::communication::StreamTcpServer;
using c24::communication::Stream;

DEFINE_int32(port, 5500,
             "Define port number where do you want to listen for connection.");

int main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  Stream stream(
      std::unique_ptr<StreamBackendInterface>(new StreamTcpServer(FLAGS_port)));
  std::cout << stream.GetMsg() << std::endl;
  stream.SendMsg("HELLO CLIENT");

  return 0;
}
