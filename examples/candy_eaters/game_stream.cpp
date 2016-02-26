#include "game_stream.h"

#include <memory>

GameStream::GameStream(std::unique_ptr<StreamBackendInterface> stream_backend)
    : stream_(std::move(stream_backend)) {}

bool GameStream::Wait() {
  stream_.SendMessageWithCheck("WAIT");
  if (!stream_.LastStatus().Ok()) return false;
  if (!stream_.GetMessageWithCheck("WAITING")) return false;
  if (!stream_.LastStatus().Ok()) return false;
  return stream_.GetMessageWithCheck();
}

bool GameStream::GetInit(int *n) {
  stream_.SendMessageWithCheck("GET_INIT");
  if (!stream_.LastStatus().Ok()) return false;
  *n = stream_.GetVectorOf<int>(1)[0];
  return true;
}

bool GameStream::GetMyPos(Pos* pos) {
  stream_.SendMessageWithCheck("GET_MY_POS");
  if (!stream_.LastStatus().Ok()) return false;
  vector<int> raw_pos = stream_.GetVectorOf<int>(2);
  *pos = Pos(raw_pos[0], raw_pos[1]);
  return true;
}

bool GameStream::GetMyScore(int* score) {
  stream_.SendMessageWithCheck("GET_MY_SCORE");
  if (!stream_.LastStatus().Ok()) return false;
  *score = stream_.GetVectorOf<int>(1)[0];
  return true;
}

bool GameStream::GetCandyCount(int *candy_count) {
  stream_.SendMessageWithCheck("GET_CANDY_COUNT");
  if (!stream_.LastStatus().Ok()) return false;
  *candy_count = stream_.GetVectorOf<int>(1)[0];
  return true;
}

bool GameStream::EatCandy() {
  return stream_.SendMessageWithCheck("EAT_CANDY");
}

bool GameStream::Move(Pos pos) {
  return stream_.SendMessageWithCheck("MOVE " + to_string(pos.x()) + " " +
                                      to_string(pos.y()));
}
