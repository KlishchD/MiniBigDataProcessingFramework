//
// Created by Dmytro Klishch on 5/2/22.
//
template<class T>
DataSetWriter<T>::DataSetWriter(DataSet<T> *data) {
    this->data = data;
}

template<class T>
void DataSetWriter<T>::write(const std::string &format) {
    data->write(DataSink::getSink(_options, format));
}

template<class T>
void DataSetWriter<T>::write() {
    data->write(DataSink::getSink(_options, _options["format"]));
}

template<class T>
DataSetWriter<T> *DataSetWriter<T>::option(const std::string &key, const std::string &value) {
    _options[key] = value;
    return this;
}

template<class T>
DataSetWriter<T> *DataSetWriter<T>::options(const std::map<std::string, std::string> &options) {
    for (auto &pair: options) {
        this->_options[pair.first] = pair.second;
    }
    return this;
}
