#include "Rect.h"

Rect::Rect(const Vector& pos, const Vector& size) : pos(pos), size(size) {}

bool Rect::intersects(const Rect& other) const {
    return !(pos.x + size.x < other.pos.x || other.pos.x + other.size.x < pos.x || pos.y + size.y < other.pos.y || other.pos.y + other.size.y < pos.y);
}