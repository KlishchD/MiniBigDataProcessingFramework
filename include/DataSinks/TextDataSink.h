//
// Created by Dmytro Klishch on 5/16/22.
//

#ifndef MYSPARK_TEXTDATASINK_H
#define MYSPARK_TEXTDATASINK_H

#include <fstream>
#include "../Types/Object.h"
#include "DataSink.h"

class TextDataSink : DataSink {
private:

    TextDataSink(std::map<std::string, std::string> &options);

public:
    TextDataSink() = default;

    void write(Object *const &data) override;

    DataSink *instantiate(std::map<std::string, std::string> &options) override;

private:
    std::fstream _file;
};

#include "../../sources/DataSinks/TextDataSink.inc"

#endif //MYSPARK_TEXTDATASINK_H
