#include "Unit.h"
#include <cstdlib>

Unit::Unit(const Health& health, const Armor& armor, const Attack& attack,
           int x, int y, int speed, int range)
    : health_(health), armor_(armor), attack_(attack),
      x_(x), y_(y), speed_(speed), range_(range) {}

bool Unit::move(int dx, int dy, int fieldWidth, int fieldHeight) {
    if (std::abs(dx) > speed_ || std::abs(dy) > speed_) return false;
    int nx = x_ + dx, ny = y_ + dy;
    if (nx < 0 || ny < 0 || nx >= fieldWidth || ny >= fieldHeight) return false;
    x_ = nx; y_ = ny;
    return true;
}

int Unit::attackUnit(Unit& target) const {
    int dmg = attack_.calculateDamage(target.armor_);
    target.health_.decrease(dmg);
    return dmg;
}
