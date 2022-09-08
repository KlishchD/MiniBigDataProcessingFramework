//
// Created by Dmytro Klishch on 5/16/22.
//

std::map<std::string, DataSink *> DataSink::sinks;

void DataSink::registerSink(DataSink *sink, const std::string &format) {
    sinks[format] = sink;
}

DataSink *DataSink::getSink(std::map<std::string, std::string> &options, const std::string &format) {
    return sinks[format]->instantiate(options);
}