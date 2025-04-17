#pragma once

class Timer {
	public:
		Timer(float timer);

		void update(float deltaTime);
		bool hasElapsed() const;

		void reset();

	private:
		float interval;
		float elapsedTime;

};