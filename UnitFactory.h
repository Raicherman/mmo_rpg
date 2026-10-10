#pragma once
#include <memory>
#include <string>
#include "Unit.h"

// Создатель (Creator) в паттерне "Фабричный метод".
class UnitFactory {
public:
    virtual ~UnitFactory() = default;
    // Фабричный метод: создаёт юнита нужного вида в точке (x, y).
    virtual std::unique_ptr<Unit> createUnit(UnitType type, int x, int y) const = 0;
    virtual std::string name() const = 0;
};
