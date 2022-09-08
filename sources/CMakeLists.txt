
add_library(MySpark
        DataSet/DataSet.inc DataSet/DataSetReader.inc DataSet/DataSetWriter.inc

        DataSources/VectorDataSource.inc

        Iterators/Iterator.inc

        Partitions/Partition.inc

        TasksProcessing/TasksExecutor.inc

        Types/Int.inc Types/Object.inc Types/String.inc Types/Pair.inc

        DataSinks/TextDataSink.inc DataSinks/DataSink.inc

        Session.inc

        tmp.cpp)

target_include_directories(MySpark PRIVATE ../include)