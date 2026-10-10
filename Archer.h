#pragma once
#include "Unit.h"
// Лучники: средняя скорость, дальний бой.
class Archer : public Unit {
public:
    Archer(const Health& h, const Armor& a, const Attack& at, int x, int y, int range)
        : Unit(h, a, at, x, y, 1, range) {}
};
