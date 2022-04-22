#pragma once
#include <chrono>

class ColdTimer
{
public:
	ColdTimer() noexcept;
	float Set() noexcept;
	float Peek() const noexcept;
private:
	std::chrono::steady_clock::time_point last;
};