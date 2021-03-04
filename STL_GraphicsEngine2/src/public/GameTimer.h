#pragma once

// 타이머 구현하는 방법.
// 1. 윈도우즈 API. // 나는 이걸로 구현할 예정.
// 2. std::chrono // 리눅스에서도 쓸 수 있다고 들었는데, 일단은 모르겠음.

#include <Windows.h>

class GameTimer
{
public:
	static void Start();
	static double GetTime();
	static double DeltaTime();
	static float DeltaTimef();

	static void Update();

	static void Reset();
	static int FPS();

private:
	static double countsPerSecond;
	static __int64 countStart;
	static int frameCount;
	static int fps;
	static __int64 previousFrameTime;

};

