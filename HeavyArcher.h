#pragma once
#include "Archer.h"

class HeavyArcher : public Archer {
public:
    HeavyArcher(int x, int y)
        : Archer(Health(80), Armor(3), Attack(18), x, y, 4) {}

    std::unique_ptr<Unit> clone() const override { return std::make_unique<HeavyArcher>(*this); }
    UnitType getType() const override { return UnitType::HeavyArcher; }
    char getSymbol() const override { return 'H'; }
};
