//
// Created by Dmytro Klishch on 5/16/22.
//

#ifndef MYSPARK_DATASETWRITER_H
#define MYSPARK_DATASETWRITER_H

#include <map>
#include "../DataSinks/DataSink.h"
#include "DataSet.h"

template<class T>
class DataSetWriter {
public:

    explicit DataSetWriter(DataSet<T> *data);

    void write(const std::string &format);

    void write();

    DataSetWriter<T> *option(const std::string &key, const std::string &value);

    DataSetWriter<T> *options(const std::map<std::string, std::string> &options);

private:
    std::map<std::string, std::string> _options;
    DataSet<T> *data;
};

#include "../../sources/DataSet/DataSetWriter.inc"

#endif //MYSPARK_DATASETWRITER_H
