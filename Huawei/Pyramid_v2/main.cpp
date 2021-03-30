#include <iostream>
#include <set>
#include <string>
#include <sstream>

using namespace std;

int findCountWall(string &data) {
    stringstream dataStream = stringstream(data);
    double x, y;
    int n;

    dataStream >> n;

    set<pair<int, int>> points;                         //Хранит точки пересечения внутренних стен со внешними
    set<pair<pair<int, int>, pair<int, int>>> walls;    //Хранит внутренние стены

    //Заполнение 'points' и 'walls'
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        dataStream >> x1 >> y1 >> x2 >> y2;

        walls.insert({{x1, y1},
                      {x2, y2}});
        points.insert({x1, y1});
        points.insert({x2, y2});
    }

    dataStream >> x >> y;

    if (points.empty()) {
        return 1;
    } else {
        int min = n;
        //Перебор всех вариантов, от какого куска стены идти к кладу
        for (const pair<int, int> &start : points) {
            int count = 0;
            double tx = start.first, ty = start.second;

            if (ty == 0 && tx < 100) {
                tx = tx + 0.5;
            }
            if (tx == 100 && ty < 100) {
                ty = ty + 0.5;
            }
            if (ty == 100 && tx > 0) {
                tx = tx - 0.5;
            }
            if (tx == 0 && ty > 0) {
                ty = ty - 0.5;
            }
            //Нахождение количество стен, которые нужно разрушить,
            //чтобы добраться от выбранной точки, до клада
            for (const pair<pair<int, int>, pair<int, int>> &l : walls) {
                double vx = l.second.first - l.first.first, vy = l.second.second - l.first.second;
                //Отрицательность произведения двух векторных произвидений
                //сигнализирует о том, что прямая 'i' разделила точку старта и клад
                //в две разные области => стену 'i' нужно разрушить
                if ((vx * (ty - l.first.second) - vy * (tx - l.first.first)) *
                    (vx * (y - l.first.second) - vy * (x - l.first.first)) < 0)
                    count++;

            }
            min = count < min ? count : min;
        }

        return min + 1;
    }
}

int main() {
    //Будет 6
    string randomWalls = "30\n"
                         "100 64 0 18\n"
                         "51 100 0 45\n"
                         "100 73 0 38\n"
                         "0 5 85 100\n"
                         "26 0 29 100\n"
                         "100 79 92 0\n"
                         "19 100 0 47\n"
                         "59 0 42 100\n"
                         "64 100 41 0\n"
                         "93 100 0 89\n"
                         "100 56 0 11\n"
                         "100 15 20 0\n"
                         "96 0 18 100\n"
                         "0 32 100 49\n"
                         "100 29 0 99\n"
                         "47 100 0 24\n"
                         "6 0 100 85\n"
                         "0 65 100 20\n"
                         "29 0 100 28\n"
                         "100 92 41 0\n"
                         "0 29 100 22\n"
                         "100 63 0 73\n"
                         "0 5 10 100\n"
                         "100 67 0 64\n"
                         "85 0 54 100\n"
                         "49 0 100 52\n"
                         "85 100 9 0\n"
                         "0 78 17 100\n"
                         "0 16 100 9\n"
                         "91 100 0 8\n"
                         "54.5 55.4";

    //Очевидный реультат, 1 стена
    string allWallsFromOnePoint = "30\n"
                                  "10 0 100 30\n"
                                  "10 0 100 40\n"
                                  "10 0 100 50\n"
                                  "10 0 100 60\n"
                                  "10 0 100 70\n"
                                  "10 0 100 80\n"
                                  "10 0 100 90\n"
                                  "10 0 100 100\n"
                                  "10 0 15 100\n"
                                  "10 0 17 100\n"
                                  "10 0 23 100\n"
                                  "10 0 26 100\n"
                                  "10 0 29 100\n"
                                  "10 0 30 100\n"
                                  "10 0 32 100\n"
                                  "10 0 34 100\n"
                                  "10 0 37 100\n"
                                  "10 0 41 100\n"
                                  "10 0 45 100\n"
                                  "10 0 57 100\n"
                                  "10 0 61 100\n"
                                  "10 0 65 100\n"
                                  "10 0 66 100\n"
                                  "10 0 67 100\n"
                                  "10 0 90 100\n"
                                  "10 0 87 100\n"
                                  "10 0 93 100\n"
                                  "10 0 92 100\n"
                                  "10 0 88 100\n"
                                  "10 0 83 100\n"
                                  "33.65456 54.67656";
    string parallelWalls = "19\n"
                           "11 0 11 100 \n"
                           "13 0 13 100\n"
                           "14 0 14 100\n"
                           "15 0 15 100\n"
                           "16 0 16 100\n"
                           "17 0 17 100\n"
                           "18 0 18 100\n"
                           "19 0 19 100\n"
                           "23 0 23 100\n"
                           "25 0 25 100\n"
                           "26 0 26 100\n"
                           "28 0 28 100\n"
                           "29 0 29 100\n"
                           "49 0 49 100\n"
                           "50 0 50 100\n"
                           "55 0 55 100\n"
                           "57 0 57 100\n"
                           "58 0 58 100\n"
                           "60 0 60 100\n"
                           "24.555 45.77";
    //Очевидный результат 3
    string squares25 = "8\n"
                       "20 0 20 100\n"
                       "40 0 40 100\n"
                       "60 0 60 100\n"
                       "80 0 80 100\n"
                       "0 20 100 20\n"
                       "0 40 100 40\n"
                       "0 60 100 60\n"
                       "0 80 100 80\n"
                       "50 50";

    //Очевидный результат, будет 1
    string zeroWalls = "0\n"
                       "50 50";

    cout << "Random walls: " << findCountWall(randomWalls) << endl;
    cout << "All walls from one point: " << findCountWall(allWallsFromOnePoint) << endl;
    cout << "Parallel walls: " << findCountWall(parallelWalls) << endl;
    cout << "25 squares: " << findCountWall(squares25) << endl;
    cout << "Zero walls: " << findCountWall(zeroWalls) << endl;

    //string yourTest = "";
    //cout << "Your test: " << findCountWall(yourTest) << endl;

    return 0;
}
