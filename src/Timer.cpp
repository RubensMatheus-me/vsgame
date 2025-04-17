#include "Timer.h"
#include "iostream"

Timer::Timer(float interval) : interval(interval), elapsedTime(0.0f) {}


void Timer::update(float deltaTime) {
	elapsedTime += deltaTime;

	//std::cout << "timer" << std::endl;
}

bool Timer::hasElapsed() const {
	return elapsedTime >= interval;
}

void Timer::reset() {
	elapsedTime = 0.0f;
}