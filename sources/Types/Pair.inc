//
// Created by Dmytro Klishch on 5/18/22.
//


#include "../../include/Types/Pair.h"

std::string Pair::toString() {
    return "(" + _first->toString() + ", " + _second->toString() + ")";
}

Pair::Pair(Object *const &first, Object *const &second) {
    _first = first;
    _second = second;

}

Object *Pair::first() {
    return _first;
}

Object *Pair::second() {
    return _second;
}

bool Pair::equals(Object *object) {
    if (auto casted = dynamic_cast<Pair *>(object))
        return _first->equals(casted->_first) && _second->equals(casted->_second);
    return false;
}

Pair::~Pair() {
    delete _first;
    delete _second;
}

Object *Pair::copy() {
    return new Pair(_first->copy(), _second->copy());
}
