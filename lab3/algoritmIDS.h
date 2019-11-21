#pragma once
#include <QtMath>

const int ddepth = 3;
checkers* copyMe;
checkers* copyRival;

void step(vector<bool> & cur_board, checkers* cur, int num_check, int new_positions) {
    cur_board[cur->position[num_check]] = false;
    cur_board[new_positions] = true;
    cur->position[num_check] = new_positions;
}

int manhattan_dist(int curr_pos, int goal_pos){
    return abs(goal_pos - curr_pos) / 8 + abs(goal_pos - curr_pos) % 8;
}

//<Позиция, манхэттэнское расстояниe до goal_pos>
vector<pair<int, int>> get_manh_distances(list<int>& variants, int goal_pos)
{
    //Позиция, манх расстояние
    vector<pair<int, int>> manh_distances(variants.size());
    int i = 0;
    for (int curr_var_pos : variants) {
        manh_distances[i] = make_pair(curr_var_pos, manhattan_dist(curr_var_pos, goal_pos));
        ++i;
    }

    //Сортировка по расстояниям
    sort(manh_distances.begin(), manh_distances.end(),
        [](pair<int, int> p1, pair<int, int> p2) {return p1.second < p2.second; });

    return manh_distances;
}


long long heuristic(vector<bool> curr_board, checkers * curr_player)
{
    long long sum_cost = 1;
    long long cnt = cntInHouse(curr_player);

    for (int i = 0; i < 12; ++i) {
        long long cur;
        if (checker_in_contrary_home(curr_player, i))
            cur = h_in_contrary(curr_player->num_player, curr_player->position[i]);
        else
            cur = (manhattan_dist(curr_player->position[i], closest_to_goal_free_position(curr_board, curr_player->num_player, curr_player->position[i])) + 7);
        sum_cost *= cur;
    }

    return -sum_cost - pow(cnt + 1, 4); 
}

void algoritmDLS(vector<bool> cboard, checkers * player1, checkers * player2,
    int depth, bool comp, long long & firstHeuristic, long long & secondHeuristic)
{
    if (depth == 0)
    {
        firstHeuristic = heuristic(cboard, new checkers(player1->position, player1->num_player));
        secondHeuristic = heuristic(cboard, new checkers(player2->position, player2->num_player));
        return;
    }

    if (comp)//TRUE - компьютер
    {
        for (int x = 0; x < 12; ++x)
        {
            auto variantSteps = player1->variants_of_steps(player1->position[x]);
            for (auto& y : variantSteps)
            {
                checkers * pCheckersOne = new checkers(player1->position, player1->num_player);
                checkers * pCheckersSecond = new checkers(player2->position, player2->num_player);

                step(cboard, pCheckersOne, x, y);
                long long newFirstHeuristic = firstHeuristic;
                long long newScondHeuristic = secondHeuristic;
                algoritmDLS(cboard, pCheckersOne, pCheckersSecond, depth - 1, !comp, newFirstHeuristic, newScondHeuristic);

                delete pCheckersOne;
                delete pCheckersSecond;

                if (newFirstHeuristic > firstHeuristic)
                    firstHeuristic = newFirstHeuristic;
                if (newScondHeuristic > secondHeuristic)
                    secondHeuristic = newScondHeuristic;
            }

        }
    }
    else //me
    {
        for (int x = 0; x < 12; ++x)
        {
            auto variantSteps = player2->variants_of_steps(player2->position[x]);
            for (auto& y : variantSteps)
            {
                checkers * c1 = new checkers(player1->position, player1->num_player);
                checkers * c = new checkers(player2->position, player2->num_player);
                vector<bool> bcopy = cboard;

                step(cboard, c, x, y);
                long long newFirstHeuristic = firstHeuristic;
                long long newScondHeuristic = secondHeuristic;
                algoritmDLS(cboard, c1, c, depth - 1, !comp, newFirstHeuristic, newScondHeuristic);

                cboard = bcopy;
                delete c;
                delete c1;

                if (newFirstHeuristic > firstHeuristic)
                    firstHeuristic = newFirstHeuristic;
                if (newScondHeuristic > secondHeuristic)
                    secondHeuristic = newScondHeuristic;

            }
        }
    }
}

pair<int, int> algoritmIDDFS(checkers * player, vector<bool> curboard, long long firstHeuristic, long long secondHeuristic)
{
    pair<int, int> nanswer(-1, -1);

    for (int x = 0; x < 12; ++x) {
        checkers * c = new checkers(player->position, player->num_player);
        auto variants = player->variants_of_steps(player->position[x]);

        for (auto elem : variants){

            vector<bool> bcopy = curboard;
            step(curboard, c, x, elem);
            long long newFirstHeuristic = firstHeuristic;
            long long newScondHeuristic = secondHeuristic;

            checkers* newrival = new checkers(copyRival->position, copyRival->num_player);
            algoritmDLS(curboard, c, newrival, ddepth - 1, false, newFirstHeuristic, newScondHeuristic);

            curboard = bcopy;
            delete newrival;

            if (newFirstHeuristic > firstHeuristic){
                firstHeuristic = newFirstHeuristic;
                nanswer.first = x;
                nanswer.second = elem;
            }
            if (newScondHeuristic > secondHeuristic) {
                secondHeuristic = newScondHeuristic;
            }
        }
        delete c;
    }
    return nanswer;
}


void newstart() {
    copyMe = new checkers(*me);
    copyRival = new checkers(*rival);
    answer = algoritmIDDFS(copyMe, board, LLONG_MIN, LLONG_MIN);
}
