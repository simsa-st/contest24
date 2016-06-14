#include "game_stream.h"

GameStream::GameStream(std::unique_ptr<StreamBackendInterface> stream_backend)
    : stream_(std::move(stream_backend)) {}

bool GameStream::Authenticate(const string& login, const string& password) {
  if (!stream_.GetMsgWithCheck("LOGIN")) return false;
  if (!stream_.SendMsg(login)) return false;
  if (!stream_.GetMsgWithCheck("PASSWORD")) return false;
  return stream_.SendMsgWithCheck(password);
}

bool GameStream::Wait() {
  if (!stream_.SendMsgWithCheck("WAIT")) return false;
  if (!stream_.GetMsgWithCheck("WAITING")) return false;
  return stream_.GetMsgWithCheck();
}

bool GameStream::GetInit(int *n) {
  if (!stream_.SendMsgWithCheck("GET_INIT")) return false;
  *n = stream_.GetVectorOf<int>(1)[0];
  return LastStatus().Ok();
}

bool GameStream::GetMyPos(Pos* pos) {
  if (!stream_.SendMsgWithCheck("GET_MY_POS")) return false;
  vector<int> raw_pos = stream_.GetVectorOf<int>(2);
  *pos = Pos(raw_pos[0], raw_pos[1]);
  return LastStatus().Ok();
}

bool GameStream::GetMyScore(int* score) {
  if (!stream_.SendMsgWithCheck("GET_MY_SCORE")) return false;
  *score = stream_.GetVectorOf<int>(1)[0];
  return LastStatus().Ok();
}

bool GameStream::GetCandyCount(int *candy_count) {
  if (!stream_.SendMsgWithCheck("GET_CANDY_COUNT")) return false;
  *candy_count = stream_.GetVectorOf<int>(1)[0];
  return LastStatus().Ok();
}

bool GameStream::EatCandy() {
  return stream_.SendMsgWithCheck("EAT_CANDY");
}

bool GameStream::Move(Pos pos) {
  return stream_.SendMsgWithCheck("MOVE " + to_string(pos.x()) + " " +
                                  to_string(pos.y()));
}
