#include <iostream>
#include <vector>
#include "include/Types/Int.h"
#include "include/Session.h"
#include "include/Types/Pair.h"

int main() {
    auto *session = new Session();

    std::vector<Int *> data;

    for (int i = 0; i < 21; ++i) {
        data.push_back(new Int(i));
    }

    DataSet<Int *> *dataSet = session->reader()->read(data, 3);

    auto func = [](Int *const &number) {
        return (bool) (number->value() % 2);
    };

    DataSet<Int *> *filtered = dataSet->filter(func);

    filtered->show();

    auto max = [](Int *const &a, Int *const &b) {
        return *a > *b ? a : b;
    };

    auto sum = [](Int *const &a, Int *const &b) {
        return a->add(b);
    };

    Int *maximum = (Int *) dataSet->reduce(max);

    std::cout << "Filtered maximum is: " << maximum->value() << std::endl;

    Int *countedSum = (Int *) dataSet->reduce(sum);

    std::cout << "Sum is: " << countedSum->value() << std::endl;

    filtered->writer()->option("filepath", "_data.txt")->write("text");

    auto read = session->reader()->option("format", "text")->option("filepath", "random.txt")->read<String *>();

    auto split = [](String *const &str) {
        std::vector<String *> split;

        std::string s = str->value();
        std::string tmp;

        for (char &i: s) {
            if (i == ' ') {
                if (tmp.empty()) continue;
                split.push_back(new String(tmp));
                tmp.clear();
                continue;
            }
            tmp += i;
        }
        return split;
    };

    auto splited = read->flatMap<String *>(split);
    std::function<Pair *(String *)> pairFunc = [](String *const &object) {
        return new Pair((Object *) object, (Object *) new Int(1));
    };

    DataSet<Pair *> *paired = splited->map(pairFunc);

    std::function<Pair *(Pair *, Pair *)> count = [](Pair *const &a, Pair *const &b) {
        return new Pair(a->first(), (Object *) ((Int *) a->second())->add((Int *) b->second()));
    };

    auto total = paired->reduceByKey(count);

    total->writer()->option("format", "text")->option("filepath", "result.txt")->write();

    return 0;
}