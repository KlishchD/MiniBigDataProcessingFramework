//
// Created by Dmytro Klishch on 5/13/22.
//

#ifndef MYSPARK_STRING_H
#define MYSPARK_STRING_H


#include "Object.h"

class String : Object {
public:

    String(const std::string &value);

    ~String() override;

    std::string toString() override;

    std::string value();

    bool equals(Object *object) override;

    Object *copy() override;

private:
    std::string _value;
};

#include "../../sources/Types/String.inc"

#endif //MYSPARK_STRING_H
