//
// Created by Dmytro Klishch on 5/12/22.
//

#include "Partition.h"
#include "../../include/DataSources/VectorDataSource.h"
#include "../../include/Types/Pair.h"

template<class T>
template<class E>
Partition<E> *Partition<T>::map(const std::function<E(T)> &func) {
    return new Partition<E>(iterator()->map(func));
}

template<class T>
Partition<T> *Partition<T>::filter(const std::function<bool(T)> &func) {
    return new Partition(iterator()->filter(func));
}

template<class T>
T Partition<T>::reduce(std::function<T(T, T)> func) {
    Iterator<T> *iterator = this->iterator();

    if (!iterator->hasNext()) return nullptr;

    T result = iterator->next();

    while (iterator->hasNext()) {
        result = func(result, iterator->next());
    }

    return result;
}

template<class T>
Iterator<T> *Partition<T>::iterator() {
    return iter->copy();
}

template<class T>
Partition<T>::Partition(Iterator<T> *iterator) {
    this->iter = iterator->copy();
}

template<class T>
void Partition<T>::show() {
    Iterator<T> *it = iterator();
    while (it->hasNext()) {
        std::cout << it->next()->toString() << std::endl;
    }
}

template<class T>
void Partition<T>::write(DataSink *sink) {
    Iterator<T> *it = iterator();

    while (it->hasNext()) {
        sink->write((Object *) it->next());
    }

}

template<class T>
template<class E>
Partition<E> *Partition<T>::flatMap(const std::function<std::vector<E>(T)> &func) {
    return new Partition(iterator()->flatMap(func));
}

template<class T>
Partition<T> *Partition<T>::reduceByKey(std::function<T(T, T)> func) {
    if (!iterator()->hasNext()) return new Partition<T>(iterator());
    std::unordered_map<std::string, Pair*> mapped;
    Iterator<T> *it = iterator();
    while (it->hasNext()) {
        T value = it->next();
        if (mapped.contains(value->first()->toString())) {
            mapped[value->first()->toString()] = func(mapped[value->first()->toString()], value);
        } else {
            mapped[value->first()->toString()] = value;
        }
    }
    std::vector<T> data;
    for (auto &i: mapped) {
        data.push_back(i.second);
    }
    return new Partition(new Iterator<T>((DataSource *) new VectorDataSource(data)));
}

template<class T>
template<class E>
void Partition<T>::unite(Partition<E> *partition) {
    iter->source()->unite(partition->iter->dataSource);
}
