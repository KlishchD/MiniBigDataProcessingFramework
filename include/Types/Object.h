//
// Created by Dmytro Klishch on 5/12/22.
//

#ifndef MYSPARK_OBJECT_INC
#define MYSPARK_OBJECT_INC


#include <string>

class Object {
public:
    virtual std::string toString();

    virtual bool equals(Object *object) = 0;

    virtual ~Object() = default;

    virtual Object *copy() = 0;

};

#include "../../sources/Types/Object.inc"

#endif //MYSPARK_OBJECT_INC
