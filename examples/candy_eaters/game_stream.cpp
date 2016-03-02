#include "game_stream.h"

GameStream::GameStream(std::unique_ptr<StreamBackendInterface> stream_backend)
    : stream_(std::move(stream_backend)) {}

bool GameStream::Authenticate(const string& login, const string& password) {
  if (!stream_.GetMessageWithCheck("LOGIN")) return false;
  if (!stream_.SendMessage(login)) return false;
  if (!stream_.GetMessageWithCheck("PASSWORD")) return false;
  return stream_.SendMessageWithCheck(password);
}

bool GameStream::Wait() {
  if (!stream_.SendMessageWithCheck("WAIT")) return false;
  if (!stream_.GetMessageWithCheck("WAITING")) return false;
  return stream_.GetMessageWithCheck();
}

bool GameStream::GetInit(int *n) {
  if (!stream_.SendMessageWithCheck("GET_INIT")) return false;
  *n = stream_.GetVectorOf<int>(1)[0];
  return LastStatus().Ok();
}

bool GameStream::GetMyPos(Pos* pos) {
  if (!stream_.SendMessageWithCheck("GET_MY_POS")) return false;
  vector<int> raw_pos = stream_.GetVectorOf<int>(2);
  *pos = Pos(raw_pos[0], raw_pos[1]);
  return LastStatus().Ok();
}

bool GameStream::GetMyScore(int* score) {
  if (!stream_.SendMessageWithCheck("GET_MY_SCORE")) return false;
  *score = stream_.GetVectorOf<int>(1)[0];
  return LastStatus().Ok();
}

bool GameStream::GetCandyCount(int *candy_count) {
  if (!stream_.SendMessageWithCheck("GET_CANDY_COUNT")) return false;
  *candy_count = stream_.GetVectorOf<int>(1)[0];
  return LastStatus().Ok();
}

bool GameStream::EatCandy() {
  return stream_.SendMessageWithCheck("EAT_CANDY");
}

bool GameStream::Move(Pos pos) {
  return stream_.SendMessageWithCheck("MOVE " + to_string(pos.x()) + " " +
                                      to_string(pos.y()));
}
