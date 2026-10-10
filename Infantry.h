#pragma once
#include "Unit.h"
// Пехота: медленная, ближний бой.
class Infantry : public Unit {
public:
    Infantry(const Health& h, const Armor& a, const Attack& at, int x, int y, int range = 1)
        : Unit(h, a, at, x, y, 1, range) {}
};
