#include "timing.h"

Timing::Timing(){};

Timing::~Timing(){};

void Timing::Start()
{
  mStart = std::chrono::system_clock::now();
  mStartTimeout = std::chrono::system_clock::now();
}

void Timing::Stop()
{
  mDuration = std::chrono::system_clock::now() - mStart;
}

float Timing::GetDuration()
{
  mDuration = std::chrono::system_clock::now() - mStart;
  return mDuration.count();
}

void Timing::SetTimeout(float timeout)
{
  mTimeout = timeout;
}

void Timing::ResetTimeout()
{
  mStartTimeout = std::chrono::system_clock::now();
}

bool Timing::IsTimedOut()
{
  std::chrono::duration<float> duration;

  duration = std::chrono::system_clock::now() - mStartTimeout;

  return (duration.count() > mTimeout);
}

