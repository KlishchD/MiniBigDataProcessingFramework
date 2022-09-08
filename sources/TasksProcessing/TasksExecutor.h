//
// Created by Dmytro Klishch on 5/14/22.
//

#ifndef MYSPARK_TASKSEXECUTOR_H
#define MYSPARK_TASKSEXECUTOR_H


#include <functional>
#include <unordered_map>

class TasksExecutor {
public:
    std::vector<Object *> execute(Object *const &val, int i = 0);

    template<class P, class T>
    void addMapTask(const std::function<P(T)> &func);

    template<class P, class T>
    void addFlatMapTask(const std::function<std::vector<P>(T)> &func);

    template<class T>
    void addFilterTask(const std::function<bool(T)> &func);

    TasksExecutor *copy();

    TasksExecutor() = default;


private:
    std::unordered_map<int, std::function<Object *(Object *)>> mapTasks;
    std::unordered_map<int, std::function<std::vector<Object *>(Object *)>> flatMapTasks;
    std::unordered_map<int, std::function<bool(Object *)>> filterTasks;
    int _tasks = 0;

    int tasksNumber();

    explicit TasksExecutor(TasksExecutor *tasksExecutor);
};

#include "TasksExecutor.inc"

#endif //MYSPARK_TASKSEXECUTOR_H
