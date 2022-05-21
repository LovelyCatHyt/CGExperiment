#pragma once

class Time
{
public:
	static long long programStartTime_Ms;
	/// <summary>
	/// 与上一帧相隔的时间, 按秒计算
	/// </summary>
	static float deltaTime;
	/// <summary>
	/// 运行总时间
	/// </summary>
	static float time;
	static void UpdateTime();
};