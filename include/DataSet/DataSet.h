//
// Created by Dmytro Klishch on 5/2/22.
//

#ifndef MYSPARK_DATASET_H
#define MYSPARK_DATASET_H

#include <utility>
#include <vector>
#include <functional>
#include "../Types/Object.h"
#include "../../sources/Partitions/Partition.h"
#include "DataSetReader.h"

template<typename T>
class DataSetWriter;

template<class T>
class DataSet {
public:

    template<class E>
    DataSet<E> *map(const std::function<E(T)> &func);

    template<class E>
    DataSet<E> *flatMap(const std::function<std::vector<E>(T)> &func);

    DataSet<T> *filter(const std::function<bool(T)> &func);

    T reduce(const std::function<T(T, T)> &func);

    DataSet<T> *reduceByKey(const std::function<T(T, T)> &func);

    void show();

    DataSetWriter<T> *writer();

    explicit DataSet(const std::vector<Partition<T> *> &partitions);

    explicit DataSet(Partition<T> *partition);

protected:

    void write(DataSink *sink);

private:
    std::vector<Partition<T> *> partitions;

    friend class DataSetWriter<T>;

    friend class DataSetReader;


};


#include "../../sources/DataSet/DataSet.inc"

#endif //MYSPARK_DATASET_H
