//
// Created by Dmytro Klishch on 5/13/22.
//

#include "../../include/DataSet/DataSet.h"

template<class T>
DataSet<T>::DataSet(const std::vector<Partition<T> *> &partitions) {
    this->partitions = partitions;
}

template<class T>
DataSet<T>::DataSet(Partition<T> *partition) {
    partitions.push_back(partition);
}

template<class T>
template<class E>
DataSet<E> *DataSet<T>::map(const std::function<E(T)> &func) {
    std::vector<Partition<E> *> newPartitions;
    for (Partition<T> *&partition: partitions) {
        newPartitions.push_back(partition->map(func));
    }
    return new DataSet<E>(newPartitions);
}

template<class T>
DataSet<T> *DataSet<T>::filter(const std::function<bool(T)> &func) {
    std::vector<Partition<T> *> newPartitions;
    for (Partition<T> *&partition: partitions) {
        newPartitions.push_back(partition->filter(func));
    }
    return new DataSet<T>(newPartitions);
}

template<class T>
T DataSet<T>::reduce(const std::function<T(T, T)> &func) {
    T result = partitions[0]->reduce(func);
    for (int i = 1; i < partitions.size(); ++i) {
        result = func(result, partitions[i]->reduce(func));
    }
    return result;
}

template<class T>
void DataSet<T>::show() {
    for (auto &partition: partitions) {
        partition->show();
    }
}

template<class T>
template<class E>
DataSet<E> *DataSet<T>::flatMap(const std::function<std::vector<E>(T)> &func) {
    std::vector<Partition<E> *> newPartitions;
    for (Partition<T> *&partition: partitions) {
        newPartitions.push_back(partition->flatMap(func));
    }
    return new DataSet<E>(newPartitions);
}

template<class T>
DataSet<T> *DataSet<T>::reduceByKey(const std::function<T(T, T)> &func) {
    Partition<T> *partition = nullptr;
    for (auto p: partitions) {
        if (!partition) partition = p;
        else partition->unite(p->reduceByKey(func));
    }
    return new DataSet(partition->reduceByKey(func));
}

template<class T>
DataSetWriter<T> *DataSet<T>::writer() {
    return new DataSetWriter<T>(this);
}

template<class T>
void DataSet<T>::write(DataSink *sink) {
    for (auto &partition: partitions) {
        partition->write(sink);
    }
}
