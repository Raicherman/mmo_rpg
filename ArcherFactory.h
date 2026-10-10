#pragma once
#include "UnitFactory.h"

class ArcherFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(UnitType type, int x, int y) const override;
    std::string name() const override { return "ArcherFactory"; }
};
