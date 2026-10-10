#pragma once
#include "Infantry.h"

class Spearman : public Infantry {
public:
    Spearman(int x, int y)
        : Infantry(Health(90), Armor(4), Attack(14), x, y, 2) {}

    std::unique_ptr<Unit> clone() const override { return std::make_unique<Spearman>(*this); }
    UnitType getType() const override { return UnitType::Spearman; }
    char getSymbol() const override { return 'P'; }
};
