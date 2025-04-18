#pragma once
#include <string>

class Timer {
	public:
		Timer(float timer);

		void update(float deltaTime);
		bool hasElapsed() const;

		void reset();

		std::pair<std::string, std::string> clock() const;

		float getElapsedTime() const {return this->elapsedTime;}


	private:
		float interval;
		float elapsedTime;
};