#pragma once
#include <cstddef>
#include <iosfwd>
#include <memory>
#include <vector>
#include "Unit.h"
#include "UnitFactory.h"
#include "GameFieldIterator.h"

// Прямоугольное игровое поле. Владеет юнитами (unique_ptr), не более maxUnits.
class GameField {
public:
    using iterator       = GameFieldIterator;
    using const_iterator = ConstGameFieldIterator;

    GameField(int width, int height, std::size_t maxUnits);

    // Правило пяти (написано явно)
    ~GameField();
    GameField(const GameField& other);                 // глубокое копирование
    GameField& operator=(const GameField& other);
    GameField(GameField&& other) noexcept;
    GameField& operator=(GameField&& other) noexcept;

    // Добавление / удаление
    void addUnit(std::unique_ptr<Unit> unit);          // позиция берётся из юнита
    void addUnit(const UnitFactory& factory, UnitType type, int x, int y);
    bool removeUnit(int x, int y);
    bool removeUnit(std::size_t index);
    void clear();

    // Доступ
    Unit*       getUnit(int x, int y);                 // nullptr, если пусто
    const Unit* getUnit(int x, int y) const;
    Unit&       getUnit(std::size_t index);            // out_of_range при ошибке
    const Unit& getUnit(std::size_t index) const;

    bool moveUnit(int x, int y, int dx, int dy);       // двигает юнита из клетки (x,y)

    std::size_t size() const { return units_.size(); }
    bool empty() const { return units_.empty(); }
    std::size_t maxUnits() const { return maxUnits_; }
    int width() const { return width_; }
    int height() const { return height_; }

    // Итерация (только по существующим юнитам)
    iterator begin() { return iterator(units_.begin()); }
    iterator end()   { return iterator(units_.end()); }
    const_iterator begin() const { return const_iterator(units_.begin()); }
    const_iterator end()   const { return const_iterator(units_.end()); }
    const_iterator cbegin() const { return begin(); }
    const_iterator cend()   const { return end(); }

    // Безопасное удаление во время итерации: возвращает итератор на следующий элемент.
    iterator erase(iterator pos);

    // Отрисовка: рамка из X, юниты — символами.
    void render(std::ostream& os) const;

private:
    bool inBounds(int x, int y) const;
    void swap(GameField& other) noexcept;

    int width_, height_;
    std::size_t maxUnits_;
    std::vector<std::unique_ptr<Unit>> units_;
};

std::ostream& operator<<(std::ostream& os, const GameField& f);
