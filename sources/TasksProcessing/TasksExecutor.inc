//
// Created by Dmytro Klishch on 5/14/22.
//

std::vector<Object *> TasksExecutor::execute(Object *const &val, int i) {
    if (!val) return {};
    if (i >= tasksNumber()) return {val};
    if (mapTasks.contains(i)) return {execute(mapTasks[i](val), i + 1)};
    if (flatMapTasks.contains(i)) {
        std::vector<Object *> results;
        std::vector<Object *> calculated = flatMapTasks[i](val);
        for (Object *const &obj: calculated) {
            for (auto &j: execute(obj, i + 1)) {
                results.push_back(j);
            }
        }
        return results;
    }
    if (filterTasks.contains(i) && !filterTasks[i](val)) return {};
    return execute(val, i + 1);
}


template<class P, class T>
void TasksExecutor::addMapTask(const std::function<P(T)> &func) {
    mapTasks[tasksNumber()] = [&func](Object *value) {
        return (Object *) func((T) value);
    };
    ++_tasks;
}

template<class T>
void TasksExecutor::addFilterTask(const std::function<bool(T)> &func) {
    filterTasks[tasksNumber()] = [&func](Object *value) {
        return func((T) value);
    };
    ++_tasks;
}

TasksExecutor *TasksExecutor::copy() {
    return new TasksExecutor(this);
}

TasksExecutor::TasksExecutor(TasksExecutor *tasksExecutor) {
    this->mapTasks = tasksExecutor->mapTasks;
    this->filterTasks = tasksExecutor->filterTasks;
    this->flatMapTasks = tasksExecutor->flatMapTasks;
    this->_tasks = tasksExecutor->_tasks;
}

int TasksExecutor::tasksNumber() {
    return _tasks;
}

template<class P, class T>
void TasksExecutor::addFlatMapTask(const std::function<std::vector<P>(T)> &func) {
    flatMapTasks[tasksNumber()] = [&func](Object *object) {
        std::vector<Object *> result;
        for (P val: func((T) object)) {
            result.push_back((Object *) val);
        }
        return result;
    };
    ++_tasks;
}
