#pragma once
#include "Cavalry.h"

class Cataphract : public Cavalry {
public:
    Cataphract(int x, int y)
        : Cavalry(Health(150), Armor(10), Attack(20), x, y, 1) {}

    std::unique_ptr<Unit> clone() const override { return std::make_unique<Cataphract>(*this); }
    UnitType getType() const override { return UnitType::Cataphract; }
    char getSymbol() const override { return 'C'; }
};
