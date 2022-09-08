//
// Created by Dmytro Klishch on 5/14/22.
//

#ifndef MYSPARK_VECTORDATASOURCE_H
#define MYSPARK_VECTORDATASOURCE_H


#include <vector>
#include "DataSource.h"

class VectorDataSource : DataSource {
public:
    template<class T>
    explicit VectorDataSource(const std::vector<T> &data);

    VectorDataSource() = default;

    Object* next() override;

    bool hasNext() override;

    DataSource *copy() override;

    DataSource *instantiate(std::map<std::string, std::string> &options) override;

    std::vector<DataSource *> split(int times) override;


private:
    std::vector<Object *> _data;

    template<class T>
    explicit VectorDataSource(const std::vector<T> &data, DataSource *nextSource);

    int _currentPosition = 0;
};

#include "../../sources/DataSources/VectorDataSource.inc"


#endif //MYSPARK_VECTORDATASOURCE_H
