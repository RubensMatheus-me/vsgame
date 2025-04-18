#include "Timer.h"
#include <iostream>
#include <sstream>

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

std::pair<std::string, std::string> Timer::clock() const {
	int total = static_cast<int>(elapsedTime);
	int mins = total / 60;
	int secs = total % 60;
	int millis = static_cast<int>((elapsedTime - total) * 1000);

	std::stringstream ssTime, ssMillis;
	ssTime << (mins < 10 ? "0" : "") << mins << ":"
	   << (secs < 10 ? "0" : "") << secs;
	
	ssMillis << ":" << (millis < 100 ? (millis < 10 ? "00" : "0") : "") << millis;
	
	return {ssTime.str(), ssMillis.str()};
}