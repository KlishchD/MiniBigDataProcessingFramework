//
// Created by Dmytro Klishch on 5/17/22.
//

#ifndef MYSPARK_PAIR_H
#define MYSPARK_PAIR_H

#include "Object.h"

class Pair : Object {
public:
    Pair(Object *const &first, Object *const &second);

    ~Pair() override;

    std::string toString() override;

    Object *first();

    Object *second();

    bool equals(Object *object) override;

    Object *copy() override;

private:
    Object *_first;
    Object *_second;
};

#include "../../sources/Types/Pair.inc"

#endif //MYSPARK_PAIR_H
