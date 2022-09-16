#include "Timer.h"

Timer* Timer::sInstance = NULL;

//* inicjalizacja zegara
Timer* Timer::Instance() {
	if (sInstance == NULL)
	{
		sInstance = new Timer();
	}
	return sInstance;
}

//* funkcja zerujaca inicjalizacje
void Timer::Release() {
	delete sInstance;
	sInstance = NULL;
}

//* konstruktor bazowy
Timer::Timer()
{
	Reset();
	mTimeScale = 1.0f;
}

Timer::~Timer() {}

//* funkcja zerujaca odmierzanie
void Timer::Reset() {
	mStartTicks = SDL_GetTicks();
	mLastTicks = 0;
	mDeltaTime = 0;
}

//* funkcja zerujaca minuty
void Timer::ResetMin() {
	mMinute = 0;
}

//* funkcja zwracjaca tikniecie
int Timer::deltaTime() {
	return mDeltaTime;
}

//* funkcja pozaujaca "skale"
void Timer::TimeScale(float t) {
	mTimeScale = t;
}
int Timer::TimeScale() {
	return mTimeScale;
}

//* funkcja odswierzajaca
void Timer::Update() {
	mLastTicks = SDL_GetTicks() - mStartTicks;
	mDeltaTime = mLastTicks * 0.001f;
}

//* funkcja ustawiajaca godiny
unsigned int Timer::Hour() {
	return mHour;
}

//* funkcja ustawiajaca minuty
unsigned int Timer::Minute() {
	return mMinute;
}

//* funkcja dodajaca godziny
void Timer::AddHour() {
	mHour = mHour + 1;
}

//* funkcja dodajaca minuty
void Timer::AddMinute() {
	mMinute = mMinute + 1;
}