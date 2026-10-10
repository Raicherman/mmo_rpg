#pragma once
#include "Unit.h"
// Конница: высокая скорость.
class Cavalry : public Unit {
public:
    Cavalry(const Health& h, const Armor& a, const Attack& at, int x, int y, int range = 1)
        : Unit(h, a, at, x, y, 3, range) {}
};
