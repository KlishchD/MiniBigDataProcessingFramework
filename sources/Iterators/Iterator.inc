//
// Created by Dmytro Klishch on 5/14/22.
//

#include "Iterator.h"

template<class T>
void Iterator<T>::updateSet() {
    currentSet = tasksExecutor->execute(dataSource->next());
    currentPosition = 0;
}

template<class T>
T Iterator<T>::next() {
    if (currentPosition < currentSet.size()) return (T) currentSet[currentPosition++];
    else updateSet();
    return next();
}

template<class T>
bool Iterator<T>::hasNext() {
    if (currentPosition < currentSet.size()) return true;
    if (!dataSource->hasNext()) return false;
    updateSet();
    return hasNext();
}

template<class T>
template<class P>
Iterator<P> *Iterator<T>::map(const std::function<P(T)> &func) {
    TasksExecutor *copy = tasksExecutor->copy();
    copy->addMapTask(func);
    return new Iterator<P>(this, copy);

}

template<class T>
Iterator<T> *Iterator<T>::filter(const std::function<bool(T)> &func) {
    TasksExecutor *copy = tasksExecutor->copy();
    copy->addFilterTask(func);
    return new Iterator<T>(this, copy);

}

template<class T>
Iterator<T> *Iterator<T>::copy() {
    return new Iterator<T>(this);
}

template<class T>
Iterator<T>::Iterator(DataSource *dataSource) {
    this->dataSource = dataSource->copy();
    this->tasksExecutor = new TasksExecutor();
}

template<class T>
template<class E>
Iterator<T>::Iterator(Iterator<E> *iterator) {
    this->dataSource = iterator->dataSource->copy();
    this->tasksExecutor = iterator->tasksExecutor->copy();
}

template<class T>
template<class E>
Iterator<T>::Iterator(Iterator<E> *iterator, TasksExecutor *tasksExecutor) {
    this->dataSource = iterator->dataSource->copy();
    this->tasksExecutor = tasksExecutor->copy();
}

template<class T>
template<class P>
Iterator<P> *Iterator<T>::flatMap(const std::function<std::vector<P>(T)> &func) {
    TasksExecutor *copy = tasksExecutor->copy();
    copy->addFlatMapTask(func);
    return new Iterator<T>(this, copy);
}

template<class T>
DataSource *Iterator<T>::source() {
    return dataSource->copy();
}

