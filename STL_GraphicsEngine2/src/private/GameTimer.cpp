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

	// �ϵ���� Ŭ�� ��.
	QueryPerformanceFrequency(&frequencyCount);

	// �ʴ� �ϵ���� Ÿ�̸��� ���� ��.
	countsPerSecond = (double)(frequencyCount.QuadPart); // ���� 1�ʴ� 100�� �����Ѵٰ� ĥ ��,

	// ���� ������ ������ ���� ��.
	QueryPerformanceCounter(&frequencyCount); // ���⼭ 50�� ��ϵǸ�, 0.5�� �����ٰ� �����Ѵ�.
	countStart = frequencyCount.QuadPart;
}

double GameTimer::GetTime()
{
	// ������ ���۵� �ķκ��� ���� �ð�.
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	double time = (double)(currentTime.QuadPart - countStart) / countsPerSecond;

	return time;
}

// ������ ������ �ð��� ���ϴ� �Լ�.
double GameTimer::DeltaTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	// ���� ���� �� - ���� ���� ��
	// ���� �����Ӱ� ���� �������� ���� ���ϱ�.
	// ���� : ���� ��.
	__int64 tickCount = currentTime.QuadPart - previousFrameTime;

	// ���� ������ �ð� �� ������Ʈ(����).
	previousFrameTime = currentTime.QuadPart;

	// ���� Ȯ��. �翬�� ���������, ������ ������ ���� ���� �ֱ⿡ üũ���ش�.
	if (tickCount < 0)
	{
		tickCount = 0;
	}

	// �� ���� ������ �ð� ���ϱ�.
	double deltaTime = (double)(tickCount / countsPerSecond);

	// ���� Ȯ��.
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

// Ÿ�̸� �ʱ�ȭ.
void GameTimer::Reset()
{
	// 1�� ���� ���� ������ �� �Է�.
	fps = frameCount;

	// ������ �� ����� ���� ���� �ʱ�ȭ.
	frameCount = 0;

	// Ÿ�̸� �����.
	Start();

	// ������(â)�� ���� ����. (������ �� �߰�.)
	std::wstring title;
	title = Window::Title() +
		std::wstring(L"     FPS: ") + std::to_wstring(fps) +
		std::wstring(L"     DeltaTime: ") + std::to_wstring(DeltaTimef());

	// ����� â ���� ����.
	SetWindowText(Window::WindowHandle(), title.c_str());
}

int GameTimer::FPS()
{
	return fps;
}
