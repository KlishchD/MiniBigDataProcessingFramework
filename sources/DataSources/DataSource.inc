//
// Created by Dmytro Klishch on 5/17/22.
//

#include "../../include/DataSources/DataSource.h"

std::map<std::string, DataSource *> DataSource::_sources;


void DataSource::registerSource(DataSource *const &source, const std::string &format) {
    _sources[format] = source;
}

DataSource *DataSource::getSource(std::map<std::string, std::string> &options, const std::string &format) {
    return _sources[format]->instantiate(options);
}

void DataSource::unite(DataSource *source) {
    if (_nextSource) _nextSource->unite(source);
    else _nextSource = source;
}
