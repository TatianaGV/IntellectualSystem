#include <iostream>
#include <ctime>
#include <map>
#include "Node.h"
#include "Search_algs.h"
#include "Heuristics.h"

#define TIME

using namespace std;

void showGrid1(Node* node){
    vector<size_t >& grid = node->grid;
    for (int i = 0; i < grid.size(); ++i){
        if (i%4 == 0)
            cout << endl;
        cout << grid[i] << ' ';
    }
    cout << endl;
}

int showPath(Node* node){
    int steps = 0;
    while (node != nullptr){
        //showGrid(node);
        node = node -> parent;
        steps++;
    }
    //cout << endl << "count steps is " << steps;
    return steps;
}


int main() {
    int prev_time = (double)clock() / CLOCKS_PER_SEC * 1e3;

    srand(time(0));
    //vector<size_t> startGrid = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};

    //vector<size_t> startGrid = {1, 4, 3, 2, 5, 6, 12, 8, 9, 10, 11, 7, 13, 14, 15, 0}; //24 +1
    //vector<size_t> startGrid = {1, 2, 3, 0, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 4}; //19 + 1
    //vector<size_t> startGrid = {2, 15, 0, 3, 7, 1, 6, 10, 5, 12, 13, 4, 9, 14, 8, 11}; //40 + 1
    //vector<size_t> startGrid = {3, 6, 5, 12, 10, 4, 8, 14, 13, 9, 15, 11, 0, 2, 1, 7}; //49 + 1
    vector<size_t> startGrid = {5, 1, 14, 10, 15, 13, 7, 11, 9, 4, 12, 8, 3, 2, 6, 0};
    map<int, int> times;
    map<int, int> times_cnts;

    cout << endl;
    cout << "Start..." << endl;

    Node *start = new Node(startGrid);
    showGrid1(start);
    start->parent = nullptr;
    //Node* answer = IDAStar(start, Conflicts);
    Node *answer = AStar(start, Conflicts);
    int steps = showPath(answer);
    showGrid1(answer);

    #ifdef TIME
            cout << "\n=========== ";
            int time = ((double)clock() / CLOCKS_PER_SEC * 1e3) - prev_time;
            times[steps] += time;
            times_cnts[steps] ++;
            cout << time;
    #endif

    cout << endl;
    for (auto vals: times){
        printf("steps = %d AVG time = %d\n", vals.first, vals.second/times_cnts[vals.first]);
    }
    return 0;
}