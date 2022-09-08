//
// Created by Dmytro Klishch on 5/12/22.
//

#ifndef MYSPARK_PARTITION_H
#define MYSPARK_PARTITION_H


#include <functional>
#include <iostream>
#include "../Iterators/Iterator.h"
#include "../../include/DataSinks/DataSink.h"


template<class T>
class Partition {
public:
    explicit Partition(Iterator<T> *iterator);

    template<class E>
    Partition<E> *map(const std::function<E(T)> &func);

    template<class E>
    Partition<E> *flatMap(const std::function<std::vector<E>(T)> &func);

    Partition<T> *filter(const std::function<bool(T)> &func);

    T reduce(std::function<T(T, T)> func);

    Partition<T> *reduceByKey(std::function<T(T, T)> func);

    Iterator<T> *iterator();

    void show();

    template<class E>
    void unite(Partition<E> *partition);

protected:
    void write(DataSink *sink);

private:
    Iterator<T> *iter;

    template<class E>
    friend
    class DataSet;
};

#include "Partition.inc"

#endif //MYSPARK_PARTITION_H
