//
// Created by Dmytro Klishch on 5/12/22.
//

#ifndef MYSPARK_INT_H
#define MYSPARK_INT_H


#include <string>
#include "Object.h"

class Int : Object {
public:
    [[nodiscard]] std::string toString() override;

    Int(const int &value);

    [[nodiscard]] Int *add(const int &val) const;

    [[nodiscard]] Int *add(Int *const &val) const;

    [[nodiscard]] Int *subtract(const int &val) const;

    [[nodiscard]] Int *subtract(Int *const &val) const;

    [[nodiscard]] Int *multiply(const int &val) const;

    [[nodiscard]] Int *multiply(Int *const &val) const;

    [[nodiscard]] Int *divide(const int &val) const;

    [[nodiscard]] Int *divide(Int *const &val) const;

    [[nodiscard]] int value() const;

    friend bool operator>(const Int &a, const Int &b);

    friend bool operator<(const Int &a, const Int &b);

    friend bool operator==(const Int &a, const Int &b);

    friend bool operator!=(const Int &a, const Int &b);

    friend bool operator>=(const Int &a, const Int &b);

    friend bool operator<=(const Int &a, const Int &b);

    bool equals(Object *object) override;

    ~Int() override;

    Object *copy() override;

private:
    int _value;

};

#include "../../sources/Types/Int.inc"

#endif //MYSPARK_INT_H
