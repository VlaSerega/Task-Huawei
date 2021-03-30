#include <iostream>
#include <set>
#include <queue>

using namespace std;

#define X 15
#define Y 10

void init(int (&grid)[Y][X]) {
    char element;

    for (int i = Y - 1; i >= 0; --i) {
        for (int j = 0; j < X; ++j) {
            cin >> element;
            grid[i][j] = element;
        }
    }
}
//Field shift function, after cluster removal
void shift(int (&grid)[Y][X]) {
    set<int> emptyColumns;
    //Shift columns down
    for (int j = 0; j < X; ++j) {
        int i = 0;
        int k;

        for (; i < Y && grid[i][j] != -1; ++i) {}
        for (k = i; k < Y && grid[k][j] == -1; ++k) {}

        if (i == 0 && k == Y) {
            //Adding an empty column to the collection
            emptyColumns.insert(j);
        } else {

            for (; k < Y;) {
                if (grid[k][j] == -1) {
                    ++k;
                } else {
                    grid[i][j] = grid[k][j];
                    ++i;
                    ++k;
                }
            }

            for (; i < Y; ++i)
                grid[i][j] = -1;
        }
    }
    //Removing leftmost empty columns from the list
    auto z = emptyColumns.rbegin();
    for (int j = X - 1; z != emptyColumns.rend() && *z != j && j >= 0; --j, ++z) {
        emptyColumns.erase(j);
    }
    //Shift columns to the left
    for (auto j = emptyColumns.rbegin(); j != emptyColumns.rend(); j++) {
        for (auto &y : grid) {
            for (int x = *j; x < X - 1; ++x) {
                y[x] = y[x + 1];
            }
            y[X - 1] = -1;
        }
    }
}
//The function of finding a cluster including a point (x, y)
//Function uses BFS field traversal
set<pair<int, int>> BFS(int x, int y, int (&grid)[Y][X], set<pair<int, int>> &allPoints) {
    set<pair<int, int>> newCluster;     //Collection for new cluster points
    queue<pair<int, int>> bfsQueue;     //BFS queue

    bfsQueue.push({x, y});
    newCluster.insert({x, y});
    allPoints.insert({x, y});

    while (!bfsQueue.empty()) {
        pair<int, int> cur = bfsQueue.front();
        int xx = cur.first, yy = cur.second;
        vector<pair<int, int>> neighbor = {{xx - 1, yy},
                                           {xx + 1, yy},
                                           {xx,     yy - 1},
                                           {xx,     yy + 1}};
        bfsQueue.pop();
        //Traversing the neighbors of 'cur'
        for (const pair<int, int> &i : neighbor) {
            int xn = i.first, yn = i.second;
            if (xn >= 0 && xn < X && yn >= 0 && yn < Y && grid[yn][xn] == grid[yy][xx] &&
                allPoints.find({xn, yn}) == allPoints.end()) {
                allPoints.insert({xn, yn});
                newCluster.insert({xn, yn});
                bfsQueue.push({xn, yn});
            }
        }
    }

    return newCluster;
}


// Function for finding all clusters
set<set<pair<int, int>>> findAllClusters(int (&grid)[Y][X], set<pair<int, int>> &allPoints) {
    set<set<pair<int, int>>> clusters;

    for (int i = 0; i < Y; ++i) {
        for (int j = 0; j < X; ++j) {
            if (grid[i][j] != -1 && allPoints.find({j, i}) == allPoints.end()) {
                set<pair<int, int>> newCluster = BFS(j, i, grid, allPoints);
                // Add a new cluster if its size is 2 or more
                if (newCluster.size() > 1) {
                    clusters.insert(newCluster);
                }
            }
        }
    }

    return clusters;
}
// The main function of the game
pair<int, int>  play(int (&grid)[Y][X]) {
    unsigned int score = 0;
    int move = 1;

    while (true) {
        //'allPoints' stores all visited peaks
        set<pair<int, int>> allPoints;
        pair<int, int> minPoint = {100, 100};
        set<pair<int, int>> maxCluster;
        set<set<pair<int, int>>> clusters = findAllClusters(grid, allPoints);

        if (!clusters.empty()) {
            char color;
            // Find the largest cluster by size
            // having the leftmost and lowest point among equals
            for (const set<pair<int, int>> &i : clusters) {
                if (i.size() == maxCluster.size() && *i.begin() < minPoint || i.size() > maxCluster.size()) {
                    minPoint = *i.begin();
                    maxCluster = i;
                }
            }

            color = (char) grid[minPoint.second][minPoint.first];

            cout << "Move " << move << " at (" << minPoint.second + 1 << "," << minPoint.first + 1 << "): removed "
                 << maxCluster.size() << " balls of color " << color << ", got "
                 << (maxCluster.size() - 2) * (maxCluster.size() - 2) << " points.\n";

            move++;
            score += (maxCluster.size() - 2) * (maxCluster.size() - 2);
            //Deleting a Selected Cluster
            for (const pair<int, int> &i : maxCluster) {
                grid[i.second][i.first] = -1;
            }
            //Field shift
            shift(grid);
        } else {
            if (allPoints.empty())
                score += 1000;
            cout << "Final score: " << score << " with " << allPoints.size() << " remaining." << endl;

            return {score, allPoints.size()};
        }
    }
}

int main() {
//Main loop for playing and inputting data from stdin
    int grid[Y][X];
    int n;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cout << "Game: " << i + 1 << endl;
        init(grid);

        play(grid);
        cout << endl;
    }
//Examples from the assignment cover all possible options
//Test
    {
        int grid[Y][X] = {{'R','R','R','R','R','R','R','R','R','R','R','R','R','R','R'},
                          {'R','G','G','G','G','G','G','G','G','G','G','G','G','G','R'},
                          {'R','G','B','B','B','B','B','B','B','B','B','B','B','G','R'},
                          {'R','G','B','R','R','R','R','R','R','R','R','R','B','G','R'},
                          {'R','G','B','R','G','G','G','G','G','G','G','R','B','G','R'},
                          {'R','G','B','R','G','G','G','G','G','G','G','R','B','G','R'},
                          {'R','G','B','R','R','R','R','R','R','R','R','R','B','G','R'},
                          {'R','G','B','B','B','B','B','B','B','B','B','B','B','G','R'},
                          {'R','G','G','G','G','G','G','G','G','G','G','G','G','G','R'},
                          {'R','R','R','R','R','R','R','R','R','R','R','R','R','R','R'}
        };
        if (play(grid) != pair<int, int>(5560, 0)) {
            cout << "Bad result" << endl;
            exit(-1);
        } else {
            cout << "Test ok" << endl;
        }
    }
    return 0;
}