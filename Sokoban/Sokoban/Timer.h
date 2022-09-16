#pragma once
#include "SDL.h"







//* klasa tworzaca zegar
class Timer
{
public:
	
	//* inicjalizacja zegara
	static Timer* Instance();

	//* funkcja zerujaca inicjalizacje
	static void Release();

	//* funkcja zerujaca odmierzanie
	void Reset();

	//* funkcja zerujaca minuty
	void ResetMin();

	//* funkcja zwracjaca tikniecie
	int deltaTime();

	//* funkcja pozaujaca "skale"
	void TimeScale(float t);
	int TimeScale();

	//* funkcja odswierzajaca
	void Update();

	//* funkcja ustawiajaca godiny
	unsigned int Hour();

	//* funkcja ustawiajaca minuty
	unsigned int Minute();

	//* funkcja dodajaca godziny
	void AddHour();

	//* funkcja dodajaca minuty
	void AddMinute();

private:

	//* inicjalizacja zmiennych dot. czasu
	static Timer* sInstance;

	unsigned int mStartTicks;
	unsigned int mLastTicks;
	unsigned int mMinute = 0;
	unsigned int mHour = 0;
	int mDeltaTime;
	float mTimeScale;

	Timer();
	~Timer();
};