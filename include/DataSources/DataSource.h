//
// Created by Dmytro Klishch on 5/14/22.
//

#ifndef MYSPARK_DATASOURCE_H
#define MYSPARK_DATASOURCE_H

#include "../Types/Object.h"

class DataSource {
public:
    virtual Object *next() = 0;

    virtual bool hasNext() = 0;

    virtual DataSource *copy() = 0;

    virtual DataSource *instantiate(std::map<std::string, std::string> &options) = 0;

    virtual std::vector<DataSource *> split(int times) = 0;

    void unite(DataSource *source);

protected:
    DataSource *_nextSource = nullptr;

    static void registerSource(DataSource *const &source, const std::string &format);

    static DataSource *getSource(std::map<std::string, std::string> &options, const std::string &format);

private:
    static std::map<std::string, DataSource *> _sources;

    friend class DataSetReader;

    friend class Session;
};

#include "../../sources/DataSources/DataSource.inc"


#endif //MYSPARK_DATASOURCE_H
