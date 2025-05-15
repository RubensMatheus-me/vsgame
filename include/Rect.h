#pragma once
#include "Vector.h"

struct Rect {
    Vector pos;
	Vector size;

    bool intersects(const Rect& other) const;
};