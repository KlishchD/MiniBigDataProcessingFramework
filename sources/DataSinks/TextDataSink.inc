//
// Created by Dmytro Klishch on 5/18/22.
//

TextDataSink::TextDataSink(std::map<std::string, std::string> &options) {
    _file = std::fstream(options["filepath"], std::ios::out);
}

void TextDataSink::write(Object *const &data) {
    _file << data->toString() << std::endl;
}

DataSink *TextDataSink::instantiate(std::map<std::string, std::string> &options) {
    return new TextDataSink(options);
}