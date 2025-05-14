#pragma once

struct Rect {
    float x;
    float y;
    float w;
    float h;

    Rect(float x, float y, float w, float h);

    bool intersects(const Rect& other) const;
};