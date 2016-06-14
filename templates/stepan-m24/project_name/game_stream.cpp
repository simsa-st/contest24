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
bool GameStream::GetTime(int *round, int *turn, int *turns_in_round) {
  if (!stream_.SendMsgWithCheck("GET_TIME")) return false;
  vector<int> nums = stream_.GetVectorOf<int>(3);
  *round = nums[0];
  *turn = nums[1];
  *turns_in_round = nums[2];
  return LastStatus().Ok();
}
bool GameStream::GetMyScore(int *n) {
  if (!stream_.SendMsgWithCheck("GET_MY_SCORE")) return false;
  *n = stream_.GetVectorOf<int>(1)[0];
  return LastStatus().Ok();
}
bool GameStream::GetAllScores(vector<int>* all_scores) {
  if (!stream_.SendMsgWithCheck("GET_ALL_SCORES")) return false;
  int size = stream_.GetVectorOf<int>(1)[0];
  if (!LastStatus().Ok()) return false;
  *all_scores = stream_.GetVectorOf<int>(size);
  return LastStatus().Ok();
}
bool GameStream::GetInit(int *n) {
  if (!stream_.SendMsgWithCheck("GET_INIT")) return false;
  *n = stream_.GetVectorOf<int>(1)[0];
  return LastStatus().Ok();
}
bool GameStream::Move(const Pos& pos) {
  return stream_.SendMsgWithCheck("MOVE " + to_string(pos.x()) + " " +
                                  to_string(pos.y()));
}
