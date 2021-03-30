#include <set>
#include "PacketManager.h"

map<string, set<string>> PacketManager::loadDependencies_(const string &fileName) {
    map<string, set<string>> graph;

    ifstream file;
    file.open(fileName, ios::in);

    string stringPacketDependencies;
    string line;

    while (getline(file, line)) {
        //Удаляем все пробелы из строки
        std::string::iterator end_pos = remove(line.begin(), line.end(), ' ');
        line.erase(end_pos, line.end());

        stringPacketDependencies += line;

        /*
         * Продолжаем считывать строки, пока не встртим
         * закрывающую скобку
         * */
        if (stringPacketDependencies[stringPacketDependencies.size() - 1] != ']')
            continue;

        string key = stringPacketDependencies.substr(0, stringPacketDependencies.find("->"));
        set<string> value;

        stringPacketDependencies.erase(0, stringPacketDependencies.find("->") + 3);
        stringPacketDependencies.erase(stringPacketDependencies.size() - 1, stringPacketDependencies.size());

        size_t pos;
        //Парсим содержимое скобок
        {
            while ((pos = stringPacketDependencies.find(',')) != std::string::npos) {
                value.insert(stringPacketDependencies.substr(0, pos));
                stringPacketDependencies.erase(0, pos + 1);
            }

            if (!stringPacketDependencies.empty())
                value.insert(stringPacketDependencies);
        }

        //Добавляем пакет с его зависимостями в map
        graph.insert(pair<string, set<string>>(key, value));

        stringPacketDependencies = "";
    }

    return graph;
}

PacketManager::PacketManager(const string &required, const string &current) {
    this->required = loadDependencies_(required);
    this->current = loadDependencies_(current);

    //Сразу сообщаем о наличии цикла в 'required' зависимостях
    fprintf(stderr, "%s", thereIsCycle().c_str());

    BFS();
}

void PacketManager::BFS() {
    queue<string> bfs_queue;
    set<string> visited;
    set<string> curPacketName = this->current.begin()->second;

    if (this->required.find(this->current.begin()->first) == this->required.end()) {
        fprintf(stderr, "There isn't such packet: %s", this->current.begin()->first.c_str());
        return;
    }

    bfs_queue.push(this->current.begin()->first);
    visited.insert(this->current.begin()->first);
    this->path_.insert({this->current.begin()->first, ""});


    while (!bfs_queue.empty()) {
        string first = bfs_queue.front();
        bfs_queue.pop();

        if (this->required.find(first) == this->required.end()) {
            visited.insert(first);
            continue;
        }

        set<string> tmp = this->required.find(first)->second;
        //Обход зависимостей пакета 'first'
        for (const string &i : tmp) {
            if (visited.find(i) != visited.end()) {
                continue;
            }

            this->path_.insert({i, first});
            visited.insert(i);
            bfs_queue.push(i);
            //Нахождение отсутвиющих зависимотей
            if (curPacketName.find(i) == curPacketName.end()) {
                this->missing.insert(i);
            }
        }
    }

    /*
     * Находим все зависимости из переданного пакета,
     * которые не были посещены при обходе => они лишние
     * */
    for (const string &i : this->current.begin()->second) {
        if (visited.find(i) == visited.end()) {
            this->excess.insert(i);
        }
    }

}

string PacketManager::getExcessDependencies() {
    string message = "Excess dependencies:\n";

    for (const string &i : this->excess) {
        message.append("-");
        message.append(i);
        message.append("\n");
    }

    return message;
}

string PacketManager::getDependenciesTree(const string &s) {
    string message = s;
    string parent;

    if (this->path_.find(s) == this->path_.end()) {
        fprintf(stderr, "There isn't such packet\n");
        return "";
    }

    parent = this->path_.find(s)->second;
    //Обход дерева path_
    while (!parent.empty()) {
        string tmp = parent;
        tmp.append(" -> ");
        tmp.append(message);
        message = tmp;
        parent = this->path_.find(parent)->second;
    }

    message.append("\n");

    return message;
}

string PacketManager::getMissingDependencies() {
    string message = "Missing Dependencies:\n";
    //Находим путь от корня до каждого пропущенного пакета
    for (const string &i : this->missing) {
        message.append(getDependenciesTree(i));
    }

    return message;
}

string PacketManager::thereIsCycle() {
    map<string, int> degreeIn;
    set<string> zeroDegree;

    /*
     * Подсчет полустепеней захода для кадого пакета
     * (количество пакетов, которые зависят от данного)
     * */
    for (const pair<string, set<string>> &i : this->required) {
        if (degreeIn.find(i.first) == degreeIn.end()) {
            degreeIn.insert({i.first, 0});
        }

        for (const string &j : i.second) {
            if (degreeIn.find(j) != degreeIn.end()) {
                degreeIn.find(j)->second += 1;
            } else {
                degreeIn.insert({j, 1});
            }
        }
    }

    //Нахождение пакетов, не зависящих ни от чего
    for (const pair<string, int> &i : degreeIn) {
        if (i.second == 0) {
            zeroDegree.insert(i.first);
        }
    }

    /*
     * BFS обход графа зависимостей и уделения пакетов с нулевой
     * полустепенью захода с его зависимостями
     * */
    while (!zeroDegree.empty()) {
        string first = *zeroDegree.begin();
        zeroDegree.erase(first);
        //Удаляем вершину, если в нее нет путей
        if (degreeIn.find(first)->second == 0)
            degreeIn.erase(first);
        //Если пакета нет в графе зависимотей => он не зависит ни от чего
        if (this->required.find(first) == this->required.end())
            continue;
        //Обход соседей 'first' и понижение их полустепени захода
        for (const string &i : this->required.find(first)->second) {
            degreeIn.find(i)->second -= 1;

            if (degreeIn.find(i)->second == 0) {
                zeroDegree.insert(i);
            }
        }
    }

    //Если были удалены все вершины - нет цикла, иначе - есть
    if (degreeIn.empty()) {
        return "There isn't cycle\n";
    }

    return "There is cycle\n";
}