#include "easylogging++.h"
#include <gflags/gflags.h>

#include "game.h"
INITIALIZE_EASYLOGGINGPP

#define PORT_FIRST_SERVER 5500
#define PORT_SECOND_SERVER 5510

DEFINE_string(host, "127.0.0.1", "Host for tcp communication.");
DEFINE_int32(port, 5500, "Port for tcp communication.");
DEFINE_bool(vis, false, "Start with visualizer.");
DEFINE_bool(toolbar, false, "Start with toolbar.");
DEFINE_int32(seed, -1,
             "Seed used in srand. If negative (default), time(NULL) is used.");
DEFINE_int32(server, -1, "On which server we play.");

int main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  int seed = FLAGS_seed;
  if (seed < 0) seed = time(NULL);
  srand(seed);
  if (FLAGS_server == 0) {
    FLAGS_port = PORT_FIRST_SERVER;
  } else if (FLAGS_server == 1) {
    FLAGS_port = PORT_SECOND_SERVER;
  }

  Game game(FLAGS_host, FLAGS_port);
  game.Run(FLAGS_vis, FLAGS_toolbar);
  return 0;
}
