#pragma once
#include "Vector.h"

struct Rect {
    Vector pos;
	Vector size;

    Rect() = default;
    Rect(const Vector& pos, const Vector& size);

    bool intersects(const Rect& other) const;
};