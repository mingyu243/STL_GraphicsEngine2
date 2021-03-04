#include "GameTimer.h"

double GameTimer::countsPerSecond;
__int64 GameTimer::countStart;
int GameTimer::frameCount;
int GameTimer::fps;
__int64 GameTimer::previousFrameTime;

void GameTimer::Start()
{
	LARGE_INTEGER frequencyCount;

	// 하드웨어 클럭 수.
	QueryPerformanceFrequency(&frequencyCount);

	// 초당 하드웨어 타이머의 진동 수.
	countsPerSecond = (double)(frequencyCount.QuadPart); // 만약 1초당 100번 진동한다고 칠 때,

	// 일정 시점에 진동한 진동 수.
	QueryPerformanceCounter(&frequencyCount); // 여기서 50이 기록되면, 0.5초 지났다고 생각한다.
	countStart = frequencyCount.QuadPart;
}

double GameTimer::GetTime()
{
	// 엔진이 시작된 후로부터 지난 시간.
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	double time = (double)(currentTime.QuadPart - countStart) / countsPerSecond;

	return time;
}

double GameTimer::DeltaTime()
{
	return 0.0;
}

float GameTimer::DeltaTimef()
{
	return 0.0f;
}

void GameTimer::Update()
{
}

void GameTimer::Reset()
{
}

int GameTimer::FPS()
{
	return 0;
}
