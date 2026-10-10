#pragma once

// Здоровье: значение всегда в диапазоне [0, max].
class Health {
public:
    explicit Health(int value = 100);          // max = value
    Health(int value, int maxValue);

    void decrease(int amount);                 // не уходит ниже 0
    void increase(int amount);                 // не поднимается выше max
    bool isZero() const;
    int  value() const;
    int  max() const;

private:
    int value_;
    int max_;
};
