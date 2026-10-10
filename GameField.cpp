#include "GameField.h"
#include <algorithm>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>

GameField::GameField(int width, int height, std::size_t maxUnits)
    : width_(width), height_(height), maxUnits_(maxUnits) {
    if (width <= 0 || height <= 0) throw std::invalid_argument("GameField: bad size");
    units_.reserve(maxUnits);
}

GameField::~GameField() = default;   // unique_ptr освободит юнитов

GameField::GameField(const GameField& other)
    : width_(other.width_), height_(other.height_), maxUnits_(other.maxUnits_) {
    units_.reserve(other.units_.size());
    for (const auto& u : other.units_) units_.push_back(u->clone());
}

GameField& GameField::operator=(const GameField& other) {
    if (this != &other) {
        GameField tmp(other);   // copy-and-swap
        swap(tmp);
    }
    return *this;
}

GameField::GameField(GameField&& other) noexcept
    : width_(other.width_), height_(other.height_), maxUnits_(other.maxUnits_),
      units_(std::move(other.units_)) {
    other.units_.clear();
}

GameField& GameField::operator=(GameField&& other) noexcept {
    if (this != &other) {
        width_ = other.width_;
        height_ = other.height_;
        maxUnits_ = other.maxUnits_;
        units_ = std::move(other.units_);
        other.units_.clear();
    }
    return *this;
}

void GameField::swap(GameField& o) noexcept {
    std::swap(width_, o.width_);
    std::swap(height_, o.height_);
    std::swap(maxUnits_, o.maxUnits_);
    units_.swap(o.units_);
}

bool GameField::inBounds(int x, int y) const {
    return x >= 0 && y >= 0 && x < width_ && y < height_;
}

void GameField::addUnit(std::unique_ptr<Unit> unit) {
    if (!unit) throw std::invalid_argument("addUnit: null unit");
    if (!inBounds(unit->getX(), unit->getY())) throw std::out_of_range("addUnit: position out of field");
    if (units_.size() >= maxUnits_) throw std::length_error("addUnit: unit limit reached");
    if (getUnit(unit->getX(), unit->getY())) throw std::invalid_argument("addUnit: cell is occupied");
    units_.push_back(std::move(unit));
}

void GameField::addUnit(const UnitFactory& factory, UnitType type, int x, int y) {
    addUnit(factory.createUnit(type, x, y));
}

bool GameField::removeUnit(int x, int y) {
    auto it = std::find_if(units_.begin(), units_.end(),
        [&](const std::unique_ptr<Unit>& u) { return u->getX() == x && u->getY() == y; });
    if (it == units_.end()) return false;
    units_.erase(it);
    return true;
}

bool GameField::removeUnit(std::size_t index) {
    if (index >= units_.size()) return false;
    units_.erase(units_.begin() + static_cast<std::ptrdiff_t>(index));
    return true;
}

void GameField::clear() { units_.clear(); }

Unit* GameField::getUnit(int x, int y) {
    for (auto& u : units_) if (u->getX() == x && u->getY() == y) return u.get();
    return nullptr;
}
const Unit* GameField::getUnit(int x, int y) const {
    for (const auto& u : units_) if (u->getX() == x && u->getY() == y) return u.get();
    return nullptr;
}
Unit& GameField::getUnit(std::size_t index) {
    if (index >= units_.size()) throw std::out_of_range("getUnit: bad index");
    return *units_[index];
}
const Unit& GameField::getUnit(std::size_t index) const {
    if (index >= units_.size()) throw std::out_of_range("getUnit: bad index");
    return *units_[index];
}

bool GameField::moveUnit(int x, int y, int dx, int dy) {
    Unit* u = getUnit(x, y);
    if (!u) return false;
    if (getUnit(x + dx, y + dy)) return false;          // клетка занята
    return u->move(dx, dy, width_, height_);
}

GameField::iterator GameField::erase(iterator pos) {
    return iterator(units_.erase(pos.base()));
}

void GameField::render(std::ostream& os) const {
    std::vector<std::string> grid(static_cast<size_t>(height_ + 2),
                                  std::string(static_cast<size_t>(width_ + 2), ' '));
    for (int x = 0; x < width_ + 2; ++x) { grid[0][x] = 'X'; grid[height_ + 1][x] = 'X'; }
    for (int y = 0; y < height_ + 2; ++y) { grid[y][0] = 'X'; grid[y][width_ + 1] = 'X'; }
    for (const auto& u : units_) grid[u->getY() + 1][u->getX() + 1] = u->getSymbol();
    for (const auto& row : grid) {
        for (char c : row) os << c << ' ';
        os << '\n';
    }
}

std::ostream& operator<<(std::ostream& os, const GameField& f) {
    f.render(os);
    return os;
}
