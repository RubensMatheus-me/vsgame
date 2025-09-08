#pragma once

class Attack;

class ILifetime {
public:
    virtual ~ILifetime() = default;
    virtual void advance(float dt) {}
    virtual bool alive(Attack& h) = 0;
    virtual void reset() {}
};