#include <string>
#include <sstream>

#include "easylogging++.h"
#include <gflags/gflags.h>
#include "server_game.h"

INITIALIZE_EASYLOGGINGPP

using namespace std;

DEFINE_string(ports, "",
              "Ports where to listen for players. Communication happens over "
              "tcp. List the ports separated by commas, e.g. "
              "--ports=5500,6000,6500");
DEFINE_int32(seed, -1,
             "Seed used in srand. If negative (default), time(NULL) is used.");
DEFINE_bool(vis, false, "Start with visualizer.");

int main(int argc, char** argv) {
  google::ParseCommandLineFlags(&argc, &argv, true);

  int seed = FLAGS_seed;
  if (seed < 0) seed = time(NULL);
  srand(seed);
  
  vector<int> ports;
  stringstream sstream(FLAGS_ports);
  string token;

  while (getline(sstream, token, ',')) {
    ports.push_back(atoi(token.c_str()));
  }

  ServerGame game(ports);
  if (!FLAGS_vis) {
    game.Run();
  } else {
    game.RunWithVisualizer();
  }
  return 0;
}
