// This example shows how to use the TCP client. It connects to server, sends
// one message and receives one message.

#include <memory>

#include <iostream>
#include <glog/logging.h>
#include <gflags/gflags.h>
#include "c24/communication/stream.h"
#include "c24/communication/stream_tcp_client.h"
#include "c24/communication/stream_backend_interface.h"

using c24::communication::StreamBackendInterface;
using c24::communication::StreamTcpClient;
using c24::communication::Stream;

DEFINE_string(host, "127.0.0.1",
              "Define hostname to which do you want to connect.");
DEFINE_int32(port, 5500, "Define port number to which do you want to connect.");

int main(int argc, char** argv) {
  google::InitGoogleLogging(*argv);
  google::ParseCommandLineFlags(&argc, &argv, true);
  Stream stream = Stream(std::unique_ptr<StreamBackendInterface>(
      new StreamTcpClient(FLAGS_host, FLAGS_port)));
  stream.SendMessage("HELLO SERVER");
  std::cout << stream.GetMessage() << std::endl;

  return 0;
}
