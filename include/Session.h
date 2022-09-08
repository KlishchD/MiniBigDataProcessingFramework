//
// Created by Dmytro Klishch on 5/16/22.
//

#ifndef MYSPARK_SESSION_H
#define MYSPARK_SESSION_H


#include "DataSet/DataSetReader.h"
#include "DataSinks/TextDataSink.h"
#include "DataSet/DataSetWriter.h"
#include "DataSources/TextDataSource.h"
#include "DataSources/DataSource.h"


class Session {
public:
    Session();

    DataSetReader *reader();

private:
    static bool _loaded;

    static void setUp();
};

#include "../sources/Session.inc"

#endif //MYSPARK_SESSION_H
