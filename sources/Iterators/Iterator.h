//
// Created by Dmytro Klishch on 5/12/22.
//

#ifndef MYSPARK_ITERATOR_H
#define MYSPARK_ITERATOR_H


#include <functional>
#include <vector>
#include "../../include/DataSources/DataSource.h"
#include "../TasksProcessing/TasksExecutor.h"

template<class T>
class Iterator {
public:
    explicit Iterator(DataSource *dataSource);

    template<class E>
    explicit Iterator(Iterator<E> *iterator);

    template<class E>
    Iterator(Iterator<E> *iterator, TasksExecutor *tasksExecutor1);

    T next();

    bool hasNext();

    template<class P>
    Iterator<P> *map(const std::function<P(T)> &func);

    template<class P>
    Iterator<P> *flatMap(const std::function<std::vector<P>(T)> &func);

    Iterator<T> *filter(const std::function<bool(T)> &func);

    Iterator<T> *copy();

protected:

    DataSource* source();

    template<class E>
    friend class Partition;
    template<class E>
    friend class Iterator;

private:
    TasksExecutor *tasksExecutor{};
    std::vector<Object *> currentSet;
    DataSource *dataSource;
    int currentPosition;

    void updateSet();
};

#include "Iterator.inc"

#endif //MYSPARK_ITERATOR_H
