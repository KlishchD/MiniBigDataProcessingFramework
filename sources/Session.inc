//
// Created by Dmytro Klishch on 5/16/22.
//


bool Session::_loaded = false;

void Session::setUp() {
    if (_loaded) return;
    DataSink::registerSink((DataSink *) new TextDataSink(), "text");
    DataSource::registerSource((DataSource *) new VectorDataSource(), "vector");
    DataSource::registerSource((DataSource *) new TextDataSource(), "text");
    _loaded = true;
}

DataSetReader *Session::reader() {
    return new DataSetReader();
}

Session::Session() {
    setUp();
}
