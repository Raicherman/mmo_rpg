#pragma once
#include <memory>
#include "Health.h"
#include "Armor.h"
#include "Attack.h"
#include "UnitType.h"

// Абстрактный базовый класс всех юнитов.
class Unit {
public:
    Unit(const Health& health, const Armor& armor, const Attack& attack,
         int x, int y, int speed, int range);
    virtual ~Unit() = default;

    // Чисто виртуальный интерфейс
    virtual std::unique_ptr<Unit> clone() const = 0;   // полиморфное копирование
    virtual UnitType getType() const = 0;
    virtual char     getSymbol() const = 0;            // символ для отрисовки

    // Геттеры
    int getX() const { return x_; }
    int getY() const { return y_; }
    int getSpeed() const { return speed_; }
    int getRange() const { return range_; }
    Health&       getHealth()       { return health_; }
    const Health& getHealth() const { return health_; }
    const Armor&  getArmor()  const { return armor_; }
    const Attack& getAttack() const { return attack_; }
    bool isAlive() const { return !health_.isZero(); }

    void setPosition(int x, int y) { x_ = x; y_ = y; }

    // Перемещение в пределах поля [0,w)x[0,h) и не дальше speed по каждой оси.
    bool move(int dx, int dy, int fieldWidth, int fieldHeight);

    // Нанести удар по цели, возвращает фактический урон.
    int attackUnit(Unit& target) const;

private:
    Health health_;
    Armor  armor_;
    Attack attack_;
    int x_, y_;
    int speed_;
    int range_;
};
