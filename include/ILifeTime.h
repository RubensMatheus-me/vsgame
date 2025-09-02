#pragma once

class Attack;

class ILifetime {
public:
    virtual ~ILifetime() = default;
    virtual void advance(float dt) {}
    virtual bool alive(const Attack& h) = 0;
};