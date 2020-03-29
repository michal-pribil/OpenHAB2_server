#pragma once

#include <chrono>

class Timing
{
public:
  Timing();
  ~Timing();

  void Start();
  void Stop();
  float GetDuration();
  void SetTimeout(float timeout);
  void ResetTimeout();
  bool IsTimedOut();

private:
  std::chrono::time_point<std::chrono::system_clock> mStart;
  std::chrono::time_point<std::chrono::system_clock> mStartTimeout;
  std::chrono::duration<float> mDuration;
  float mTimeout;
};

