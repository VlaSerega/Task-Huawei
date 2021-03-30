//
// Created by sergo on 08.02.2021.
//

#ifndef TASK_5_PACKETMANAGER_H
#define TASK_5_PACKETMANAGER_H

#include <cstring>
#include <map>
#include <list>
#include <queue>
#include <fstream>
#include <algorithm>
#include <set>
#include <iostream>

using namespace std;

class PacketManager {
public:
    //Необходимые зависимости
    map<string, set<string>> required;
    //Текущие (переданные зависимости)
    map<string, set<string>> current;
    //Пропущенные зависимости
    set<string> missing;
    //Лишние зависимости
    set<string> excess;

    /**
     * @brief Загружает необходимые зависимости из файла и текущего из пакета, инициализирует атрибуты
     * @param required - имя файла с необходимыми зависимостями
     * @param current - имя пакета
     * */
    PacketManager(const string &required, const string &current);

    /**
     * @brief Получение пропущенных зависимостей
     * @return Строка, содержащая все лишние зависимости
     * */
    string getMissingDependencies();

    /**
     * @brief Получение лишних зависимостей
     * @return Строка, содержащая лишние зависимости
     * */
    string getExcessDependencies();

    /**
     * @brief Отображение ветки с зависимостью
     * @param Имя пакет, для которого нужно вывести ветку
     * @return Строка, содержащая ветку с зависимостью
     * */
    string getDependenciesTree(const string &s);

    /**
     * @brief Поиск цикла в графе зависимостей 'required'
     * @return Строка информирующая о наличии цикла
     * */
    string thereIsCycle();

private:
    //Хранит пути
    map<string, string> path_;

    /**
     * @brief Метод, инициализирающий атрибуты, для дальнейшего использования в методах
     * */
    void BFS();

    /**
     * @brief Загружает зависимости из файла
     * @param Имя файла
     * @return Граф зависимостей
     * */
    map<string, set<string>> loadDependencies_(const string &fileName);
};


#endif //TASK_5_PACKETMANAGER_H
