//
// Created by Dmytro Klishch on 5/14/22.
//

#include "../../include/DataSources/VectorDataSource.h"

Object *VectorDataSource::next() {
    if (_currentPosition >= _data.size()) return (_nextSource ? _nextSource->next() : nullptr);
    return _data[_currentPosition++];
}

bool VectorDataSource::hasNext() {
    return _currentPosition < _data.size() || (_nextSource && _nextSource->hasNext());
}

DataSource *VectorDataSource::copy() {
    return new VectorDataSource(_data, _nextSource);
}

DataSource *VectorDataSource::instantiate(std::map<std::string, std::string> &options) {
    return new VectorDataSource(std::vector<Object *>());
}

std::vector<Object *> extract(const std::vector<Object *> &vector, int l, int r) {
    std::vector<Object *> result;
    while (l < r) {
        result.push_back(vector[l]);
        ++l;
    }
    return result;
}

std::vector<DataSource *> VectorDataSource::split(int times) {
    int size = std::min(1, (int) _data.size() / times);
    std::vector<DataSource *> sources;
    for (int i = 0; i * size < times; ++i) {
        int left = i * size;
        int right = std::min((int) _data.size(), (i + 1) * size);
        sources.push_back(new VectorDataSource(extract(_data, left, right)));
    }
    while (sources.size() < times) sources.push_back(new VectorDataSource());

    if (_nextSource) {
        std::vector<DataSource *> splits = _nextSource->split(times);
        for (int i = 0; i < times; ++i) {
            sources[i]->unite(splits[i]);
        }
    }

    return sources;
}

template<class T>
std::vector<Object *> cast(const std::vector<T> &data) {
    std::vector<Object *> result;
    for (T value: data) {
        result.push_back((Object *) value);
    }
    return result;
}

template<class T>
VectorDataSource::VectorDataSource(const std::vector<T> &data) {
    _data = cast(data);
}

template<class T>
VectorDataSource::VectorDataSource(const std::vector<T> &data, DataSource *nextSource) {
    _data = cast(data);
    _nextSource = nextSource;
}
