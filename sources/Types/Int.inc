//
// Created by Dmytro Klishch on 5/12/22.
//


#include "../../include/Types/Int.h"

std::string Int::toString() {
    return std::to_string(_value);
}

Int *Int::add(const int &val) const {
    return new Int(_value + val);
}

Int *Int::subtract(const int &val) const {
    return new Int(_value - val);
}

Int *Int::multiply(const int &val) const {
    return new Int(_value * val);
}

Int *Int::divide(const int &val) const {
    return new Int(_value / val);
}

Int *Int::add(Int *const &val) const {
    return new Int(_value + val->value());
}

Int *Int::subtract(Int *const &val) const {
    return new Int(_value - val->value());
}

Int *Int::multiply(Int *const &val) const {
    return new Int(_value * val->value());
}

Int *Int::divide(Int *const &val) const {
    return new Int(_value / val->value());
}

int Int::value() const {
    return _value;
}

bool operator>(const Int &a, const Int &b) {
    return a.value() > b.value();
}

bool operator<(const Int &a, const Int &b) {
    return a.value() < b.value();
}

bool operator==(const Int &a, const Int &b) {
    return a.value() == b.value();
}

bool operator!=(const Int &a, const Int &b) {
    return a.value() != b.value();
}

bool operator>=(const Int &a, const Int &b) {
    return a.value() >= b.value();
}

bool operator<=(const Int &a, const Int &b) {
    return a.value() <= b.value();
}

Int::Int(const int &value) {
    this->_value = value;
}

bool Int::equals(Object *object) {
    if (auto casted = dynamic_cast<Int *>(object)) return casted->_value == _value;
    return false;
}

Object *Int::copy() {
    return new Int(_value);
}

Int::~Int() = default;
