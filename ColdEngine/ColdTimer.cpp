#include "ColdTimer.h"

using namespace std::chrono;

ColdTimer::ColdTimer() noexcept
{
	last = steady_clock::now();
}

float ColdTimer::Set() noexcept
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

float ColdTimer::Peek() const noexcept
{
	return duration<float>(steady_clock::now() - last).count();
}