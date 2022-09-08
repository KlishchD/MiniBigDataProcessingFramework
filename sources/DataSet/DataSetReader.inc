//
// Created by Dmytro Klishch on 5/2/22.
//

#include "../../include/DataSet/DataSetReader.h"

template<class T>
DataSet<T> *DataSetReader::read(const std::vector<T> &data, int partitionsNumber) {
    partitionsNumber = std::min(partitionsNumber, (int) data.size());
    int sliceSize = data.size() / partitionsNumber;

    std::vector<Partition<T> *> partitions;
    for (int i = 0; i < partitionsNumber - 1; ++i) {
        partitions.push_back(buildPartition(data, i * sliceSize, (i + 1) * sliceSize));
    }
    partitions.push_back(buildPartition(data, (partitionsNumber - 1) * sliceSize, data.size()));

    return new DataSet(partitions);
}

template<class T>
Partition<T> *DataSetReader::buildPartition(const std::vector<T> &data, int l, int r) {
    std::vector<T> slice;
    while (l < r) {
        slice.push_back(data[l++]);
    }
    return new Partition<T>(new Iterator<T>((DataSource *) new VectorDataSource(slice)));
}

DataSetReader *DataSetReader::option(const std::string &key, const std::string &value) {
    _options[key] = value;
    return this;
}

DataSetReader *DataSetReader::options(const std::map<std::string, std::string> &map) {
    for (auto &pair: map) {
        _options[pair.first] = pair.second;
    }
    return this;
}

template<class T>
DataSet<T> *DataSetReader::read(int partitionsNumber) {
    DataSource *source = DataSource::getSource(_options, _options["format"]);
    std::vector<DataSource *> sources = source->split(partitionsNumber);

    std::vector<Partition<T> *> partitions;
    for (auto &s: sources) {
        partitions.push_back(new Partition(new Iterator<T>(s)));
    }

    return new DataSet<T>(partitions);
}

template<class T>
DataSet<T> *DataSetReader::read(const std::string &format, int partitionsNumber) {
    _options["format"] = format;
    return read < T > (partitionsNumber);
}
