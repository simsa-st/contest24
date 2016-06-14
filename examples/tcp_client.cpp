// This example shows how to use the TCP client. It connects to server, sends
// one message and receives one message.

#include <memory>
#include <iostream>

#include "easylogging++.h"
#include "gflags/gflags.h"
#include "c24/communication/stream.h"
#include "c24/communication/stream_tcp_client.h"
#include "c24/communication/stream_backend_interface.h"

INITIALIZE_EASYLOGGINGPP

using c24::communication::StreamBackendInterface;
using c24::communication::StreamTcpClient;
using c24::communication::Stream;

DEFINE_string(host_server, "127.0.0.1",
              "Define hostname to which do you want to connect.");
DEFINE_int32(port, 5500, "Define port number to which do you want to connect.");

int main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  Stream stream(std::unique_ptr<StreamBackendInterface>(
      new StreamTcpClient(FLAGS_host_server, FLAGS_port)));
  stream.SendMsg("HELLO SERVER");
  std::cout << stream.GetMsg() << std::endl;

  return 0;
}
