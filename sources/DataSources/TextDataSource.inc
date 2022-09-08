//
// Created by Dmytro Klishch on 5/17/22.
//


#include "../../include/DataSources/TextDataSource.h"

Object *TextDataSource::next() {
    if (_empty) return nullptr;
    if (!_empty && _currentLine >= _totalLines) {
        return _nextSource ? _nextSource->next() : nullptr;
    }
    std::string tmp;
    std::getline(_file, tmp);
    ++_currentLine;
    return (Object *) new String(tmp);
}

bool TextDataSource::hasNext() {
    return !_empty && _currentLine < _totalLines || (_nextSource && _nextSource->hasNext());
}

DataSource *TextDataSource::copy() {
    return new TextDataSource(_filepath, 0, _totalLines, _nextSource);
}

DataSource *TextDataSource::instantiate(std::map<std::string, std::string> &options) {
    return new TextDataSource(options);
}

std::vector<DataSource *> TextDataSource::split(int times) {
    std::vector<DataSource *> sources;

    int split = std::max(1, _totalLines / times);

    for (int i = 0; i < times && split * i < _totalLines; ++i) {
        sources.push_back(new TextDataSource(_filepath, i * split, _totalLines));
    }

    while (sources.size() < times) sources.push_back(new TextDataSource(_filepath, true));

    if (_nextSource) {
        std::vector<DataSource *> splits = _nextSource->split(times);
        for (int i = 0; i < times; ++i) {
            sources[i]->unite(splits[i]);
        }
    }

    return sources;
}

TextDataSource::TextDataSource() {
    _empty = true;
}

int TextDataSource::lines(const std::string &filepath) {
    int result = 0;
    std::fstream f(filepath, std::ios::in);
    std::string tmp;
    while (std::getline(f, tmp)) ++result;
    f.close();
    return result;
}

TextDataSource::TextDataSource(std::map<std::string, std::string> &options) {
    _empty = false;
    _currentLine = 0;
    _filepath = options["filepath"];
    _totalLines = lines(_filepath);
    _file = std::fstream(_filepath, std::ios::in);
}

TextDataSource::TextDataSource(const std::string &filepath, bool empty) {
    _empty = empty;
    _currentLine = 0;
    _totalLines = lines(filepath);
    _filepath = filepath;
    _file = std::fstream(filepath, std::ios::in);
}

TextDataSource::TextDataSource(const std::string &filepath, int currentLine, int totalLines, DataSource *nextSource,
                               bool empty) {
    _empty = empty;
    _filepath = filepath;
    _nextSource = nextSource;
    _totalLines = totalLines;
    if (!_empty) {
        _file = std::fstream(filepath, std::ios::in);
        std::string tmp;
        while (_currentLine++ < currentLine && std::getline(_file, tmp));
    }
}

TextDataSource::TextDataSource(const std::string &filepath, int currentLine, int totalLines, bool empty) {
    _empty = empty;
    _filepath = filepath;
    _totalLines = totalLines;
    if (!_empty) {
        _file = std::fstream(filepath, std::ios::in);
        std::string tmp;
        while (_currentLine++ < currentLine && std::getline(_file, tmp));
    }
}