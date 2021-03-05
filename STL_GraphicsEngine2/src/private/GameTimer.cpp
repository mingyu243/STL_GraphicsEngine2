#include "GameTimer.h"

#include "Window.h"
#include <string>

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

// 프레임 사이의 시간을 구하는 함수.
double GameTimer::DeltaTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	// 현재 진동 수 - 이전 진동 수
	// 이전 프레임과 현재 프레임의 차이 구하기.
	// 단위 : 진동 수.
	__int64 tickCount = currentTime.QuadPart - previousFrameTime;

	// 이전 프레임 시간 값 업데이트(갱신).
	previousFrameTime = currentTime.QuadPart;

	// 오류 확인. 당연히 양수이지만, 오류로 음수가 나올 수도 있기에 체크해준다.
	if (tickCount < 0)
	{
		tickCount = 0;
	}

	// 초 단위 프레임 시간 구하기.
	double deltaTime = (double)(tickCount / countsPerSecond);

	// 오류 확인.
	if (deltaTime < 0.0)
	{
		deltaTime = 0.0;
	}

	return deltaTime;
}

float GameTimer::DeltaTimef()
{
	return (float)DeltaTime();
}

void GameTimer::Update()
{
	frameCount++;

	if (GetTime() > 1.0)
	{
		Reset();
	}
}

// 타이머 초기화.
void GameTimer::Reset()
{
	// 1초 동안 구한 프레임 수 입력.
	fps = frameCount;

	// 프레임 수 계산을 위한 변수 초기화.
	frameCount = 0;

	// 타이머 재시작.
	Start();

	// 윈도우(창)의 제목 변경. (프레임 수 추가.)
	std::wstring title;
	title = Window::Title() +
		std::wstring(L"     FPS: ") + std::to_wstring(fps) +
		std::wstring(L"     DeltaTime: ") + std::to_wstring(DeltaTimef());

	// 변경된 창 제목 설정.
	SetWindowText(Window::WindowHandle(), title.c_str());
}

int GameTimer::FPS()
{
	return fps;
}
