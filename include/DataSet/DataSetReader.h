//
// Created by Dmytro Klishch on 5/2/22.
//

#ifndef MYSPARK_DATASETREADER_H
#define MYSPARK_DATASETREADER_H


#include <map>
#include <string>
#include "DataSet.h"
#include "../../include/DataSources/VectorDataSource.h"

class DataSetReader {
public:
    DataSetReader() = default;

    template<class T>
    static DataSet<T> *read(const std::vector<T> &data, int partitionsNumber = 1);

    DataSetReader *option(const std::string &key, const std::string &value);

    DataSetReader *options(const std::map<std::string, std::string> &map);

    template<class T>
    DataSet<T> *read(int partitionsNumber = 1);

    template<class T>
    DataSet<T> *read(const std::string &format, int partitionsNumber = 1);


private:
    std::map<std::string, std::string> _options;

    template<class T>
    static Partition<T> *buildPartition(const std::vector<T> &data, int l, int r);

};

#include "../../sources/DataSet/DataSetReader.inc"

#endif //MYSPARK_DATASETREADER_H
