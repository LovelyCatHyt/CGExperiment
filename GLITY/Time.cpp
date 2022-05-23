#include "pch.h"
#include "Time.h"
#include <chrono>

using std::chrono::duration_cast;
using std::chrono::milliseconds;

long long MillisecondsSinceEpoch()
{
	return duration_cast<milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

long long Time::programStartTime_Ms = MillisecondsSinceEpoch();
float Time::deltaTime = 0;
float Time::time = 0;

void Time::UpdateTime()
{
	const auto now_ms = MillisecondsSinceEpoch();
	const auto temp = static_cast<float>(now_ms - programStartTime_Ms) / 1000.0f;
	deltaTime = temp - time;
	time = temp;
}
