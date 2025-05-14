#include "Rect.h"

Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h){}

bool Rect::intersects(const Rect& other) const {
    return !(x + w < other.x || other.x + other.w < x || y + h < other.y || other.y + other.h < y);
}