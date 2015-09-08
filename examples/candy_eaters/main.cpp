#include <glog/logging.h>
#include <gflags/gflags.h>

#include "game.h"

DEFINE_string(host, "127.0.0.1", "Host for tcp communication.");
DEFINE_int32(port, 5500, "Port for tcp communication.");
DEFINE_bool(vis, false, "Start with visualizer.");
DEFINE_int32(seed, -1,
             "Seed used in srand. If negative (default), time(NULL) is used.");

int main(int argc, char** argv) {
  google::InitGoogleLogging(*argv);
  google::ParseCommandLineFlags(&argc, &argv, true);

  int seed = FLAGS_seed;
  if (seed < 0) seed = time(NULL);
  srand(seed);

  Game game(FLAGS_host, FLAGS_port);
  if (!FLAGS_vis) {
    game.Run();
  } else {
    game.RunWithVisualizer();
  }
  return 0;
}
