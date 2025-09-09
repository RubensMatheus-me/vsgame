#include "WaveMotion.h"
#include "Attack.h"

WaveMotion::WaveMotion(Vector direction, float speed, float frequency, float amplitude)
    : dir(direction), speed(speed), freq(frequency), amplitude(amplitude), time(0.0f) {
        direction.normalize();
    }

Vector WaveMotion::computeDelta(const Attack&, float dt) {
    time += dt;
    Vector forward = dir * speed * dt;
    Vector wave(0, std::sin(time * freq) * amplitude);
    return forward + wave;
}