//
// Created by Dmytro Klishch on 5/17/22.
//

#ifndef MYSPARK_TEXTDATASOURCE_H
#define MYSPARK_TEXTDATASOURCE_H


#include <map>
#include <fstream>
#include <vector>
#include "DataSource.h"
#include "../Types/Object.h"
#include "../Types/String.h"
#include <iostream>

class TextDataSource : DataSource {
public:
    Object *next() override;

    bool hasNext() override;


    DataSource *copy() override;

    DataSource *instantiate(std::map<std::string, std::string> &options) override;

    std::vector<DataSource *> split(int times) override;


protected:
    TextDataSource();

private:
    int fetch_size = 1000;
    std::vector<std::string> read;
    bool _empty;
    int _currentLine = 0;
    int _totalLines;
    std::string _filepath;
    std::fstream _file;

    int lines(const std::string &filepath);

    explicit TextDataSource(std::map<std::string, std::string> &options);

    explicit TextDataSource(const std::string &filepath, bool empty = false);

    TextDataSource(const std::string &filepath, int currentLine, int totalLines, DataSource *nextSource,
                   bool empty = false);

    TextDataSource(const std::string &filepath, int currentLine, int totalLines, bool empty = false);

    friend class Session;

};

#include "../../sources/DataSources/TextDataSource.inc"

#endif //MYSPARK_TEXTDATASOURCE_H
