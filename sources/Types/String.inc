//
// Created by Dmytro Klishch on 5/13/22.
//

#include "../../include/Types/String.h"

std::string String::toString() {
    return _value;
}

std::string String::value() {
    return _value;
}

String::String(const std::string &value) {
    _value = value;
}

bool String::equals(Object *object) {
    if (auto *casted = dynamic_cast<String *>(object)) return casted->_value == _value;
    return false;
}

Object *String::copy() {
    return new String(_value);
}

String::~String() = default;

