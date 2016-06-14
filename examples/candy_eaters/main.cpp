#include "gflags/gflags.h"

#include "easylogging++.h"

#include "game.h"

INITIALIZE_EASYLOGGINGPP

DEFINE_string(host_server, "127.0.0.1", "Host for tcp communication.");
DEFINE_int32(port, 5500, "Port for tcp communication.");
DEFINE_bool(vis, false, "Start with visualizer.");
DEFINE_bool(toolbar, false, "Start with toolbar.");
DEFINE_int32(seed, -1,
             "Seed used in srand. If negative (default), time(NULL) is used.");

int main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  int seed = FLAGS_seed;
  if (seed < 0) seed = time(NULL);
  srand(seed);

  Game game(FLAGS_host_server, FLAGS_port);
  game.Run(FLAGS_vis, FLAGS_toolbar);
  return 0;
}
