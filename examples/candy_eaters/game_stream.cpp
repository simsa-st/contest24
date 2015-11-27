#include "game_stream.h"

#include <memory>

GameStream::GameStream(std::unique_ptr<StreamBackendInterface> stream_backend)
    : stream_(std::move(stream_backend)) {}

bool GameStream::Wait() { return stream_.SendMessageWithCheck("WAIT"); }

int GameStream::GetInit() {
  stream_.SendMessageWithCheck("GET_INIT");
  return stream_.GetVectorOf<int>(1)[0];
}

Pos GameStream::GetMyPos() {
  stream_.SendMessageWithCheck("GET_MY_POS");
  vector<int> pos = stream_.GetVectorOf<int>(2);
  return Pos(pos[0], pos[1]);
}

int GameStream::GetMyScore() {
  stream_.SendMessageWithCheck("GET_MY_SCORE");
  return stream_.GetVectorOf<int>(1)[0];
}

int GameStream::GetCandyCount() {
  stream_.SendMessageWithCheck("GET_CANDY_COUNT");
  return stream_.GetVectorOf<int>(1)[0];
}

void GameStream::EatCandy() { stream_.SendMessageWithCheck("EAT_CANDY"); }

void GameStream::Move(Pos pos) {
  stream_.SendMessageWithCheck("MOVE " + to_string(pos.x()) + " " +
                               to_string(pos.y()));
}
