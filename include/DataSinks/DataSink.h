//
// Created by Dmytro Klishch on 5/16/22.
//

#ifndef MYSPARK_DATASINK_H
#define MYSPARK_DATASINK_H

#include "../Types/Object.h"
#include <map>
#include <string>

class DataSink {
public:
    virtual void write(Object *const &data) = 0;

    virtual DataSink *instantiate(std::map<std::string, std::string> &options) = 0;

protected:
    static void registerSink(DataSink *sink, const std::string &format);

    static DataSink *getSink(std::map<std::string, std::string> &options, const std::string &format);

private:
    static std::map<std::string, DataSink *> sinks;

    template<class T>
    friend
    class DataSetWriter;

    friend class Session;
};

#include "../../sources/DataSinks/DataSink.inc"


#endif //MYSPARK_DATASINK_H
