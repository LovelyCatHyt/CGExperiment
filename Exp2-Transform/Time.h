#pragma once

class Time
{
public:
	static long long programStartTime_Ms;
	/// <summary>
	/// ����һ֡�����ʱ��, �������
	/// </summary>
	static float deltaTime;
	/// <summary>
	/// ������ʱ��
	/// </summary>
	static float time;
	static void UpdateTime();
};